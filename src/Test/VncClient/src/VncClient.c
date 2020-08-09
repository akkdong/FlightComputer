// VncClient.c
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <rfb/rfbclient.h>

#include "EPD_Worker.h"

typedef unsigned char pixel;

volatile int runLoop = 1;
pthread_mutex_t lock;


unsigned char bwFrame[400 / 8 * 300];
unsigned char bwDisplay[400 / 8 * 300];
int updateCount = 0;


void* updateDisplay(void* arg)
{
	while (runLoop)
	{
		pthread_mutex_lock(&lock);
		{
			// copy from frame to display buffer
			memcpy(bwDisplay, bwFrame, sizeof(bwFrame));
		}
		pthread_mutex_unlock(&lock);
		
		//
		if (updateCount == 0)
			EPD_4IN2_Ex_Display(bwDisplay);
		else
			EPD_4IN2_Ex_PartialDisplay(0, 0, 400, 300, bwDisplay);
		
		updateCount = (updateCount + 1) % 50;
		printf("update count: %d\n", updateCount);
	}
	
	return 0;
}

static const int BAYER_PATTERN_2X2[2][2] = 
{
	// 2x2 Bayer Dithering Matrix. Color levels: 5
	{  51, 206 },
	{ 153, 102 }
};

static void makeDitherBayer2(unsigned char* pixels, int width, int height)
{
	int	col	= 0;
	int	row	= 0;

	for( int y = 0; y < height; y++ )
	{
		row	= y & 1;	//	y % 2

		for( int x = 0; x < width; x++ )
		{
			col	= x & 1;	//	x % 2

			const pixel	blue	= pixels[x * 3 + 0];
			const pixel	green	= pixels[x * 3 + 1];
			const pixel	red		= pixels[x * 3 + 2];

			pixel	color	= ((red + green + blue)/3 < BAYER_PATTERN_2X2[col][row] ? 0 : 255);

			pixels[x * 3 + 0]	= color;	//	blue
			pixels[x * 3 + 1]	= color;	//	green
			pixels[x * 3 + 2]	= color;	//	red
		}

		pixels	+= width * 3;
	}
}


static void update(rfbClient* client, int x, int y, int w, int h) 
{
	rfbPixelFormat* pf = &client->format;
	int bpp = pf->bitsPerPixel / 8;
	int row_stride = client->width * bpp;
	unsigned char* frame = client->frameBuffer;
	unsigned char* line = frame;
	int	col	= 0;
	int	row	= 0;
	
	pthread_mutex_lock(&lock);
	{
		// dither to monochrome
		for (int y = 0; y < client->height; y++)
		{
			unsigned char* pixels = line;
			row	= y & 1; // y % 2
			
			for (int x = 0; x < client->width; x++)
			{
				unsigned char r = pixels[0];
				unsigned char g = pixels[1];
				unsigned char b = pixels[2];
			
				col	= x & 1; // x % 2
				unsigned char color = ((r + g + b) / 3 < BAYER_PATTERN_2X2[col][row] ? 0 : 255);
				
				int index = y * (400 / 8) + (x / 8);
				int shift = x % 8;
				unsigned char mask = (1 << (7 - shift));
				
				if (color)
					bwFrame[index] = bwFrame[index] | mask;
				else 
					bwFrame[index] = bwFrame[index] & ~mask;
				
				pixels += bpp;
			}
			
			line += row_stride;
		}
	}
	pthread_mutex_unlock(&lock);
	
	rfbClientLog("Received an update for %d,%d,%d,%d.\n",x,y,w,h);	
}

static void SaveFramebufferAsPPM(rfbClient* client, int x, int y, int w, int h) {
	static time_t t=0,t1;
	FILE* f;
	int i,j;
	rfbPixelFormat* pf=&client->format;
	int bpp=pf->bitsPerPixel/8;
	int row_stride=client->width*bpp;

	/* save one picture only if the last is older than 2 seconds */
	t1=time(NULL);
	if(t1-t>2)
		t=t1;
	else
		return;

	/* assert bpp=4 */
	if(bpp!=4 && bpp!=2) {
		rfbClientLog("bpp = %d (!=4)\n",bpp);
		return;
	}

	f=fopen("framebuffer.ppm","wb");
	if(!f) {
		rfbClientErr("Could not open framebuffer.ppm\n");
		return;
	}

	fprintf(f,"P6\n# %s\n%d %d\n255\n",client->desktopName,client->width,client->height);
	for(j=0;j<client->height*row_stride;j+=row_stride)
		for(i=0;i<client->width*bpp;i+=bpp) {
			unsigned char* p=client->frameBuffer+j+i;
			unsigned int v;
			if(bpp==4)
				v=*(unsigned int*)p;
			else if(bpp==2)
				v=*(unsigned short*)p;
			else
				v=*(unsigned char*)p;
			fputc((v>>pf->redShift)*256/(pf->redMax+1),f);
			fputc((v>>pf->greenShift)*256/(pf->greenMax+1),f);
			fputc((v>>pf->blueShift)*256/(pf->blueMax+1),f);
		}
	fclose(f);
}

char * getuser(rfbClient *client)
{
return strdup("pi");
}

char * getpassword(rfbClient *client)
{
return strdup("jupiter89");
}


void signalHandler(int signum)
{
	printf("Interrupt signal %d received.\n", signum);
	
	if (signum == SIGINT)
		runLoop = 0;
	else
		exit(signum);
}


int main(int argc, char **argv)
{
	printf("VncClient...\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }	
	
    printf("e-Paper Init and Clear...\r\n");
    EPD_4IN2_Ex_Init();
    EPD_4IN2_Ex_Clear();
    DEV_Delay_ms(500);
	
	memset(bwFrame, 0, sizeof(bwFrame));
	memset(bwDisplay, 0, sizeof(bwDisplay));
	
	pthread_mutex_init(&lock, NULL);
	
	pthread_t tid;
	pthread_create(&tid, NULL, updateDisplay, 0);
	
	rfbClient* client = rfbGetClient(8,3,4);
	//time_t t=time(NULL);

	client->GetPassword = getpassword;
	client->GotFrameBufferUpdate = update;

	/* The -listen option is used to make us a daemon process which listens for
	   incoming connections from servers, rather than actively connecting to a
	   given server. The -tunnel and -via options are useful to create
	   connections tunneled via SSH port forwarding. We must test for the
	   -listen option before invoking any Xt functions - this is because we use
	   forking, and Xt doesn't seem to cope with forking very well. For -listen
	   option, when a successful incoming connection has been accepted,
	   listenForIncomingConnections() returns, setting the listenSpecified
	   flag. */

	if (!rfbInitClient(client,&argc,argv))
		return 1;
	
	//
	signal(SIGINT, signalHandler);
	signal(SIGABRT, signalHandler);
	signal(SIGFPE, signalHandler);
	signal(SIGTERM, signalHandler);

	//
	while (runLoop) 
	{
		int wait = WaitForMessage(client, 100);
		if (wait < 0)
		{
			// ...
			break;
		}
		
		if(wait > 0)
		{
			if(!HandleRFBServerMessage(client))
			{
				// ...
				break;
			}
		}
		// else timeout
	}

	rfbClientCleanup(client);
	
	pthread_join(tid, NULL);
	pthread_mutex_destroy(&lock);

	return 0;
}
