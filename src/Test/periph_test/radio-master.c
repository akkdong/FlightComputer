#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, const char* argv[])
{
	unsigned char frequencyH = 0;
	unsigned char frequencyL = 0;

	unsigned int frequencyB;
	double frequency = 89.1;
	
	frequencyB = 4 * (frequency * 1000000 + 225000) / 32768;
	frequencyH = frequencyB >> 8;
	frequencyL = frequencyB & 0XFF;		
	
	printf("radio-master [write {frequency}]\n\n");
	
	int file_i2c;
	int length;
	unsigned char buffer[60] = {0};

	
	//----- OPEN THE I2C BUS -----
	char *filename = (char*)"/dev/i2c-1";
	printf("open %s\n", filename);
	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return -1;
	}
	
	int addr = 0x60;          //<<<<<The I2C address of the slave
	printf("set i2c address to 0x60\n");
	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return -1;
	}
	
	if (argc == 3 && (argv[1][0] == 'w' || argv[1][0] == 'W'))
	{
		frequency = atof(argv[2]);
		
		frequencyB = 4 * (frequency * 1000000 + 225000) / 32768;
		frequencyH = frequencyB >> 8;
		frequencyL = frequencyB & 0XFF;		
		
		//----- WRITE BYTES -----
		buffer[0] = frequencyH;
		buffer[1] = frequencyL;
		buffer[2] = 0xB0;
		buffer[3] = 0x10;
		buffer[4] = 0x00;
		length = 5;			//<<< Number of bytes to write
		if (write(file_i2c, buffer, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
		{
			/* ERROR HANDLING: i2c transaction failed */
			printf("Failed to write to the i2c bus.\n");
		}
		else
		{
			printf("Write data: %02X %02X %02X %02X %02X\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
		}		
	}
	else
	{
		//----- READ BYTES -----
		length = 5;			//<<< Number of bytes to read
		if (read(file_i2c, buffer, length) != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
		{
			//ERROR HANDLING: i2c transaction failed
			printf("Failed to read from the i2c bus.\n");
		}
		else
		{
			printf("Data read: %02X %02X %02X %02X %02X\n", 
				buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
		}
	}
	
	
	close(file_i2c);
	
	return 0;
}

