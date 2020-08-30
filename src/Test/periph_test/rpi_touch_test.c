/* User-mode multi-touch driver for
 * usb 6-2: New USB device found, idVendor=0eef, idProduct=0005
 * usb 6-2: New USB device strings: Mfr=1, Product=2, SerialNumber=3
 * usb 6-2: Product: By ZH851
 * usb 6-2: Manufacturer: RPI_TOUCH
 *
 * Touch events consists of 25 bytes, one example is
 * aa 01 03 1b 01 d2 bb 03 01 68 02 cc 00 5d 01 ef 01 5f 01 fe 00 fb 02 37 cc
 * Offset:
 *     0 : Start byte (aa)
 *     1 : Any touch (0=off,1=on)
 *   2-3 : First touch X
 *   4-5 : First touch Y
 *     6 : Multi-touch start (bb)
 *     7 : Bitmask for all touches (bit 0-4 (first-fifth), 0=off, 1=on)
 *   8-9 : Second touch X
 * 10-11 : Second touch Y
 * 12-13 : Third touch X
 * 14-15 : Third touch Y
 * 16-17 : Fourth touch X
 * 18-19 : Fourth touch Y
 * 20-21 : Fifth touch X
 * 22-23 : Fifth touch Y
 *    24 : End byte (cc or 00)
 *
 * This user mode driver decodes the touch events and injects them back into the
 * kernel using uinput.
 *
 * Copyright (c) 2015 Bjarne Steinsbo
 *
 * Code and inspiration from http://thiemonge.org/getting-started-with-uinput
 * and the CyanogenMod userspace touchscreen driver for cypress ctma395.
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <libudev.h>
#include <locale.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>


#define Syslog(x, f, ...)	printf(f, ##__VA_ARGS__)


#define die(str, ...) do { \
        perror(str); \
        exit(EXIT_FAILURE); \
    } while(0)

#define croak(str, ...) do { \
        perror(str); \
    } while(0)

int uinput_fd;
int usbraw_fd;
int fifo_fd;

#define EVENT_DEBUG 0

int send_uevent(int fd, __u16 type, __u16 code, __s32 value)
{
	struct input_event event;

#if EVENT_DEBUG
	char ctype[20], ccode[20];
	switch (type) {
		case EV_ABS:
			strcpy(ctype, "EV_ABS");
			break;
		case EV_KEY:
			strcpy(ctype, "EV_KEY");
			break;
		case EV_SYN:
			strcpy(ctype, "EV_SYN");
			break;
	}
	switch (code) {
		case ABS_MT_SLOT:
			strcpy(ccode, "ABS_MT_SLOT");
			break;
		case ABS_MT_TRACKING_ID:
			strcpy(ccode, "ABS_MT_TRACKING_ID");
			break;
		case ABS_MT_TOUCH_MAJOR:
			strcpy(ccode, "ABS_MT_TOUCH_MAJOR");
			break;
		case ABS_X:
			strcpy(ccode, "ABS_X");
			break;
		case ABS_MT_POSITION_X:
			strcpy(ccode, "ABS_MT_POSITION_X");
			break;
		case ABS_Y:
			strcpy(ccode, "ABS_Y");
			break;
		case ABS_MT_POSITION_Y:
			strcpy(ccode, "ABS_MT_POSITION_Y");
			break;
		case SYN_MT_REPORT:
			strcpy(ccode, "SYN_MT_REPORT");
			break;
		case SYN_REPORT:
			strcpy(ccode, "SYN_REPORT");
			break;
		case BTN_TOUCH:
			strcpy(ccode, "BTN_TOUCH");
			break;
	}
	printf("event type: '%s' code: '%s' value: %i \n", ctype, ccode, value);
#endif

	memset(&event, 0, sizeof(event));
	event.type = type;
	event.code = code;
	event.value = value;

	if (write(fd, &event, sizeof(event)) != sizeof(event)) {
		fprintf(stderr, "Error on send_event %lu", sizeof(event));
		return -1;
	}

	return 0;
}

#define BTN_COUNT 4

int cal_data[] = 
{
	14167,
	261,
	-2551324,
	141,
	8760,
	-1621164,
	65536,
	800,
	480,
	0
};

void calibrate_coord(int* x, int* y)
{
	int* c = &cal_data[0];
	
    double dx = ( c[2] + c[0] * x[0] + c[1] * y[0] ) / c[6];
    double dy = ( c[5] + c[3] * x[0] + c[4] * y[0] ) / c[6];
	
	x[0] = (int)dx;
	y[0] = (int)dy;
}

/* Open hidraw device and translate events until failure */
void handle_hidraw_device(char *path)
{
	struct uinput_user_dev device;
	unsigned char data[22];
	int prev_state[BTN_COUNT];

	/* Open usbraw-device, communicated from udev through the fifo */
	usbraw_fd = open(path, O_RDONLY);
	if (usbraw_fd < 0) {
		croak("error: open usbraw device : %s", path);
		return;
	}
	//Syslog(LOG_INFO, "Starting : %s", path);
	printf("Starting : %s\n", path);

	/* Iniialize uinput */
	memset(&device, 0, sizeof(device));
	strcpy(device.name, "virtual mouse");
	device.id.bustype = BUS_VIRTUAL;
	device.id.vendor = 1;
	device.id.product = 1;
	device.id.version = 1;
	device.absmax[ABS_X] = 800;
	device.absmax[ABS_Y] = 480;

	uinput_fd = open("/dev/input/uinput", O_WRONLY | O_NONBLOCK);
	if (uinput_fd < 0) {
		uinput_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
		if (uinput_fd < 0)
			die("error: open uinput device");
	}
	
	int ver;
	if (ioctl(uinput_fd, UI_GET_VERSION, &ver) == 0)
		printf("uinput version: %d\n", ver);
	
	if (ver >= 5 )
	{
		struct uinput_setup usetup;
		
		memset(&usetup, 0, sizeof(usetup));
		usetup.id.bustype = BUS_USB;
		usetup.id.vendor = 0xDEAD; /* sample vendor */
		usetup.id.product = 0xBEAF; /* sample product */
		strcpy(usetup.name, "Example device");
		
		ioctl(uinput_fd, UI_DEV_SETUP, &usetup);
	}
	else
	{
		if (write(uinput_fd, &device, sizeof(device)) != sizeof(device))
			die("error: setup device");
	}

	if (ioctl(uinput_fd, UI_SET_EVBIT, EV_KEY) < 0)
		die("error: evbit key\n");

	if (ioctl(uinput_fd, UI_SET_KEYBIT, BTN_LEFT) < 0)
		die("error: evbit left button\n");

	if (ioctl(uinput_fd, UI_SET_KEYBIT, BTN_RIGHT) < 0)
		die("error: evbit right button\n");

	if (ioctl(uinput_fd, UI_SET_EVBIT, EV_ABS) < 0)
		die("error: evbit abs\n");

	if (ioctl(uinput_fd, UI_SET_ABSBIT, ABS_X) < 0)
		die("error: abs x\n");

	if (ioctl(uinput_fd, UI_SET_ABSBIT, ABS_Y) < 0)
		die("error: abs y\n");

	if (ioctl(uinput_fd, UI_SET_EVBIT, EV_SYN) < 0)
		die("error: evbit syn\n");

	if (ioctl(uinput_fd, UI_DEV_CREATE) < 0)
		die("error: create\n");
	
	sleep(1);
	
	//
	int leftClicked = 0;
	int rightClicked = 0;
	int lastX = 0;
	int lastY = 0;
	time_t startTime = time(NULL);

	/* Enter input loop */
	while (1) {
		int state[BTN_COUNT];
		int x[BTN_COUNT];
		int y[BTN_COUNT];
		int i;
		int n = read(usbraw_fd, data, sizeof(data));
		if (n < 0)
			break; /* Unplug? */
		if (n != sizeof(data)) {
			#if 0
			printf("Short input : %d\n", n);
			for (int i = 0; i < n; i++)
				printf("%02X ", data[i]);
			printf("\n");
			#else
			if (n >= 6)
			{
				int x = data[2] * 256 + data[3];
				int y = data[4] * 256 + data[5];
				
				printf("%s: %d, %d\n", data[1] ? "Press" : "Release", x, y);
			}
			#endif
			continue;
		}
		else
		{
			#if 0
			for (int i = 0; i < n; i++)
				printf("%02X ", data[i]);
			printf("\n");
			#endif
		}

		/* Decode raw data */
		state[0] = (data[1] & 1) != 0;
		x[0] = data[2] * 256 + data[3];
		y[0] = data[4] * 256 + data[5];
		for (i = 1; i < BTN_COUNT; i++) {
			state[i] = (data[7] & (1 << i)) != 0;
			x[i] = data[i * 2 + 8] * 256 + data[i * 2 + 9];
			y[i] = data[i * 2 + 10] * 256 + data[i * 2 + 11];
		}
		
		calibrate_coord(&x[0], &y[0]);
		//printf("%s %d, %d\n", state[0] ? "[Pressed]" : "[Released]", x[0], y[0]);
		
		if (state[0]) // if pressed
		{
			printf("Pos: %d, %d\n", x[0], y[0]);
			send_uevent(uinput_fd, EV_ABS, ABS_X, x[0]);
			send_uevent(uinput_fd, EV_ABS, ABS_Y, y[0]);
			
			if (! leftClicked)
			{
				printf("Left click\n");
				send_uevent(uinput_fd, EV_KEY, BTN_LEFT, 1);
				
				leftClicked = 1;
				startTime = time(NULL);
				lastX = x[0];
				lastY = y[0];
			}
			
			time_t duration = time(NULL) - startTime;
			double movement = sqrt(pow(x[0] - lastX, 2) + pow(y[0] - lastY, 2));
			
			if (leftClicked && ! rightClicked && duration > 1 && movement < 30)
			{
				printf("Right click\n");
				send_uevent(uinput_fd, EV_KEY, BTN_RIGHT, 1);
				send_uevent(uinput_fd, EV_KEY, BTN_RIGHT, 0);
				
				rightClicked = 1;
			}
		}
		else
		{
			if (leftClicked)
			{
				printf("Released\n");
				send_uevent(uinput_fd, EV_KEY, BTN_LEFT, 0);
				
				leftClicked = 0;
				rightClicked = 0;
			}
		}
		
		send_uevent(uinput_fd, EV_SYN, SYN_REPORT, 0);
		usleep(100);
	}
	if (usbraw_fd >= 0)
		close(usbraw_fd);
	if (uinput_fd >= 0) {
		ioctl(uinput_fd, UI_DEV_DESTROY);
		close(uinput_fd);
	}
}

char rpi_dev[64];
char *find_rpi_touch()
{
	struct udev *udev;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices, *dev_list_entry;
	struct udev_device *dev;

	/* Create the udev object */
	udev = udev_new();
	if (!udev)
		die("Can't create udev");

	/* Create a list of the devices in the 'hidraw' subsystem. */
	enumerate = udev_enumerate_new(udev);
	udev_enumerate_add_match_subsystem(enumerate, "hidraw");
	udev_enumerate_scan_devices(enumerate);
	devices = udev_enumerate_get_list_entry(enumerate);
	/* For each item enumerated, print out its information.
	   udev_list_entry_foreach is a macro which expands to
	   a loop. The loop will be executed for each member in
	   devices, setting dev_list_entry to a list entry
	   which contains the device's path in /sys. */
	udev_list_entry_foreach(dev_list_entry, devices) {
		const char *path;

		/* Get the filename of the /sys entry for the device
		   and create a udev_device object (dev) representing it */
		path = udev_list_entry_get_name(dev_list_entry);
		dev = udev_device_new_from_syspath(udev, path);
		strncpy(rpi_dev, udev_device_get_devnode(dev), 64);

		/* The device pointed to by dev contains information about
		   the hidraw device. In order to get information about the
		   USB device, get the parent device with the
		   subsystem/devtype pair of "usb"/"usb_device". This will
		   be several levels up the tree, but the function will find
		   it.*/
		dev = udev_device_get_parent_with_subsystem_devtype(
		       dev, "usb", "usb_device");
		if (!dev)
			die("Unable to find parent usb device.");

		if (strcmp(udev_device_get_sysattr_value(dev, "idVendor"), "0eef")
		 || strcmp(udev_device_get_sysattr_value(dev, "idProduct"), "0005")) {
			rpi_dev[0] = 0;
		}
		udev_device_unref(dev);
		if (rpi_dev[0] != 0)
			break;
	}
	/* Free the enumerator object */
	udev_enumerate_unref(enumerate);

	udev_unref(udev);

	return rpi_dev[0] == 0 ? NULL : rpi_dev;
}

int main(int argc, char **argv)
{
	int numc;
	struct udev *udev;
	struct udev_device *dev;
	struct udev_monitor *mon;
	char *devname;

	/* Syslog */
	//openlog("rpi_touch_driver", LOG_NOWAIT, LOG_DAEMON);
	/* Deamonize? */
	/*
	if (!(argc > 1 && strlen(argv[1]) > 1 && !strcmp(argv[1], "-d"))) {
		if (daemon(0, 0))
			die("error: daemonize\n");
	}
	*/

	/* Create the udev object */
	udev = udev_new();
	if (!udev)
		die("Can't create udev");

	mon = udev_monitor_new_from_netlink(udev, "udev");
	udev_monitor_filter_add_match_subsystem_devtype(mon, "hidraw", NULL);
	udev_monitor_enable_receiving(mon);

	devname = find_rpi_touch();
	printf("find rpi_touch: %s\n", devname);
	if (devname != NULL)
		handle_hidraw_device(devname);

	while (1)
	{
		/* Block waiting for an event */
		dev = udev_monitor_receive_device(mon);
		/* Release immediately */
		udev_device_unref(dev);
		devname = find_rpi_touch();
		if (devname != NULL)
			handle_hidraw_device(devname);
	}
	
	udev_unref(udev);
	return 0;
}
