// EPD_4in2_Ex.cpp
//

#include "EPD_4in2_Ex.h"

// COMMAND
#define PANEL_SETTING                       0x00
#define POWER_SETTING                       0x01
#define POWER_OFF                           0x02
#define POWER_OFF_SEQUENCE_SETTING          0x03
#define POWER_ON                            0x04
#define POWER_ON_MEASURE                    0x05
#define BOOSTER_SOFT_START                  0x06
#define DEEP_SLEEP                          0x07
#define DATA_START_TRANSMISSION_1           0x10
#define DATA_STOP                           0x11
#define DISPLAY_REFRESH                     0x12
#define DATA_START_TRANSMISSION_2           0x13
#define LUT_FOR_VCOM                        0x20
#define LUT_WHITE_TO_WHITE                  0x21
#define LUT_BLACK_TO_WHITE                  0x22
#define LUT_WHITE_TO_BLACK                  0x23
#define LUT_BLACK_TO_BLACK                  0x24
#define PLL_CONTROL                         0x30
#define TEMPERATURE_SENSOR_COMMAND       	0x40
#define TEMPERATURE_SENSOR_SELECTION    	0x41
#define TEMPERATURE_SENSOR_WRITE        	0x42
#define TEMPERATURE_SENSOR_READ         	0x43
#define VCOM_AND_DATA_INTERVAL_SETTING		0x50
#define LOW_POWER_DETECTION                 0x51
#define TCON_SETTING                        0x60
#define RESOLUTION_SETTING                  0x61
#define GSST_SETTING                        0x65
#define GET_STATUS                          0x71
#define AUTO_MEASUREMENT_VCOM               0x80
#define READ_VCOM_VALUE                     0x81
#define VCM_DC_SETTING                      0x82
#define PARTIAL_WINDOW                      0x90
#define PARTIAL_IN                          0x91
#define PARTIAL_OUT                         0x92
#define PROGRAM_MODE                        0xA0
#define ACTIVE_PROGRAMMING                  0xA1
#define READ_OTP                            0xA2
#define POWER_SAVING                        0xE3

#define PROGMEM

////////////////////////////////////////////////////////////////////////////////////////////////////////
//

const uint8_t lut_20_vcom0_full[] PROGMEM =
{
  0x00, 0x08, 0x00, 0x00, 0x00, 0x02,
  0x60, 0x28, 0x28, 0x00, 0x00, 0x01,
  0x00, 0x14, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x12, 0x12, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00
};
const uint8_t* EPD_4IN2_lut_vcom0 = lut_20_vcom0_full;

const uint8_t lut_21_ww_full[] PROGMEM =
{
  0x40, 0x08, 0x00, 0x00, 0x00, 0x02,
  0x90, 0x28, 0x28, 0x00, 0x00, 0x01,
  0x40, 0x14, 0x00, 0x00, 0x00, 0x01,
  0xA0, 0x12, 0x12, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t* EPD_4IN2_lut_ww = lut_21_ww_full;

const uint8_t lut_22_bw_full[] PROGMEM =
{
  0x40, 0x08, 0x00, 0x00, 0x00, 0x02,
  0x90, 0x28, 0x28, 0x00, 0x00, 0x01,
  0x40, 0x14, 0x00, 0x00, 0x00, 0x01,
  0xA0, 0x12, 0x12, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t* EPD_4IN2_lut_bw = lut_22_bw_full;

const uint8_t lut_23_wb_full[] PROGMEM =
{
  0x80, 0x08, 0x00, 0x00, 0x00, 0x02,
  0x90, 0x28, 0x28, 0x00, 0x00, 0x01,
  0x80, 0x14, 0x00, 0x00, 0x00, 0x01,
  0x50, 0x12, 0x12, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t* EPD_4IN2_lut_wb = lut_23_wb_full;

const uint8_t lut_24_bb_full[] PROGMEM =
{
  0x80, 0x08, 0x00, 0x00, 0x00, 0x02,
  0x90, 0x28, 0x28, 0x00, 0x00, 0x01,
  0x80, 0x14, 0x00, 0x00, 0x00, 0x01,
  0x50, 0x12, 0x12, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t* EPD_4IN2_lut_bb = lut_24_bb_full;

// original wavetable from GxEPD, optimized for the display I have (modified Ben Krasnow version)
#define TP0A  2 // sustain phase for bb and ww, change phase for bw and wb
#define TP0B 45 // change phase for bw and wb

// same waveform as demo wavetable from Good Display:
//#define TP0A  0   // sustain phase for bb and ww, change phase for bw and wb
//#define TP0B 0x19 // change phase for bw and wb

const uint8_t lut_20_vcom0_partial[] PROGMEM =
{
  0x00, TP0A, TP0B, 0x01, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t* EPD_4IN2_Partial_lut_vcom1 = lut_20_vcom0_partial;

const uint8_t lut_21_ww_partial[] PROGMEM =
{
  0x80, // 10 00 00 00
  TP0A, TP0B, 0x01, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t* EPD_4IN2_Partial_lut_ww1 = lut_21_ww_partial;

const uint8_t lut_22_bw_partial[] PROGMEM =
{
  0xA0, // 10 10 00 00
  TP0A, TP0B, 0x01, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t* EPD_4IN2_Partial_lut_bw1 = lut_22_bw_partial;

const uint8_t lut_23_wb_partial[] PROGMEM =
{
  0x50, // 01 01 00 00
  TP0A, TP0B, 0x01, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t* EPD_4IN2_Partial_lut_wb1 = lut_23_wb_partial;

const uint8_t lut_24_bb_partial[] PROGMEM =
{
  0x40, // 01 00 00 00
  TP0A, TP0B, 0x01, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t* EPD_4IN2_Partial_lut_bb1 = lut_24_bb_partial;


////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#define WAVESHARE_420_WIDTH		EPD_4IN2_WIDTH
#define WAVESHARE_420_HEIGHT	EPD_4IN2_HEIGHT

enum _State
{
	_UNDEFINED	 = 0,
	
	_INITIALIZED = 0x01,
	_DEEP_SLEEP = 0x02,
	_POWER_ON = 0x04,
	_FAST_MODE = 0x08
};

static const uint16_t 	power_on_time = 40; // ms, e.g. 36996us
static const uint16_t 	power_off_time = 42; // ms, e.g. 40026us
static const uint16_t 	full_refresh_time = 4200; // ms, e.g. 4108541us
static const uint16_t 	partial_refresh_time = 2000; // ms, e.g. 995320us

unsigned char* buffer;

uint8_t _state = _UNDEFINED;

void _writeCommand(unsigned char Reg)
{
	DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

void _writeData(unsigned char data) 
{
	DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(data);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

void _writeData(const uint8_t * data, uint16_t n) 
{
	DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
	
	while (n--)
		DEV_SPI_WriteByte(*data++);
	
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

inline void _writeDataP(const uint8_t * data, uint16_t n) { _writeData(data, n); }

inline void _delay(int msec) 
{
	DEV_Delay_ms(msec);
}


void _waitWhileBusy(uint16_t timeout) 
{
	int remain = timeout;
	
	Debug("e-Paper busy\n");
	while (1)
	{
		DEV_Delay_ms(2);

		if (DEV_Digital_Read(EPD_BUSY_PIN) == 0)
		{
			Debug("e-Paper busy release\n");
			break;
		}
		
		remain -= 2;
		if (remain <= 0)
		{
			Debug("e-Paper waitBusy TIMEDOUT!!\n");
			break;
		}
	}	
}

void _reset() 
{
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
    DEV_Digital_Write(EPD_RST_PIN, 0);
    DEV_Delay_ms(200);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);	
}



////////////////////////////////////////////////////////////////////////////////////////////////////////
//

void _initDisplay();
void _powerOn();
void _powerOff();
void _setLUTFull();
void _setLUTPartial();
void _setPartialWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void _updatePartialWindow(const uint8_t * buffer, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void _updateFullWindow(const uint8_t * buffer);
void _transfer(uint8_t command, const uint8_t * buffer);


////////////////////////////////////////////////////////////////////////////////////////////////////////
//

void _initDisplay()
{
	_writeCommand(BOOSTER_SOFT_START); // 0x06
	_writeData(0x17);
	_writeData(0x17);
	_writeData(0x17);
	
	#if 1
	_writeCommand(POWER_SETTING); // 0x01
	_writeData(0x03);
	_writeData(0x00);
	_writeData(0x2B);
	_writeData(0x2B);
	_writeData(0x09);
	#endif
	
	_writeCommand(PANEL_SETTING); // 0x00
	_writeData(0x3F); // 300x400 B/W mode
	
	#if 1
	_writeCommand(PLL_CONTROL);
	_writeData(0x3A);
	
	_writeCommand(RESOLUTION_SETTING);
	_writeData(0x01);
	_writeData(0x90);
	_writeData(0x01);
	_writeData(0x2C);
	
	_writeCommand(VCM_DC_SETTING);
	_writeData(0x12);
	
	_writeCommand(VCOM_AND_DATA_INTERVAL_SETTING);
	_writeData(0x87);
	#endif
	
	_setLUTFull();
	_powerOn();	
}
	
void _powerOn()
{
	if (! (_state & _POWER_ON))
	{
		_writeCommand(POWER_ON); // 0x04
		_waitWhileBusy(power_on_time);
		
		_state |= _POWER_ON;
	}
}

void _powerOff()
{
	if (_state & _POWER_ON)
	{
		_writeCommand(POWER_OFF); // 0x02
		_waitWhileBusy(power_off_time);
		
		_state &= ~_POWER_ON;
	}
}

void _setLUTFull()
{
	_writeCommand(LUT_FOR_VCOM); // 0x20
	_writeDataP(lut_20_vcom0_full, sizeof(lut_20_vcom0_full));
		
	_writeCommand(LUT_WHITE_TO_WHITE); // 0x21
	_writeDataP(lut_21_ww_full, sizeof(lut_21_ww_full));
	
	_writeCommand(LUT_BLACK_TO_WHITE); // 0x22
	_writeDataP(lut_22_bw_full, sizeof(lut_22_bw_full));
	
	_writeCommand(LUT_WHITE_TO_BLACK); // 0x23
	_writeDataP(lut_23_wb_full, sizeof(lut_23_wb_full));
	
	_writeCommand(LUT_BLACK_TO_BLACK); // 0x24
	_writeDataP(lut_24_bb_full, sizeof(lut_24_bb_full));
	
	_state &= ~_FAST_MODE;
}

void _setLUTPartial()
{
	_writeCommand(LUT_FOR_VCOM); // 0x20
	_writeDataP(lut_20_vcom0_partial, sizeof(lut_20_vcom0_partial));
		
	_writeCommand(LUT_WHITE_TO_WHITE); // 0x21
	_writeDataP(lut_21_ww_partial, sizeof(lut_21_ww_partial));
	
	_writeCommand(LUT_BLACK_TO_WHITE); // 0x22
	_writeDataP(lut_22_bw_partial, sizeof(lut_22_bw_partial));
	
	_writeCommand(LUT_WHITE_TO_BLACK); // 0x23
	_writeDataP(lut_23_wb_partial, sizeof(lut_23_wb_partial));
	
	_writeCommand(LUT_BLACK_TO_BLACK); // 0x24
	_writeDataP(lut_24_bb_partial, sizeof(lut_24_bb_partial));
	
	_state |= _FAST_MODE;
}

void  _setPartialWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	uint16_t xe = (x + w - 1) | 0x07;
	uint16_t ye = y + h - 1;
	
	x = x & ~(0x07);
	
	_writeCommand(PARTIAL_WINDOW); // 0x90
	_writeData(x / 256);
	_writeData(x % 256);
	_writeData(xe / 256);
	_writeData(xe % 256);
	_writeData(y / 256);
	_writeData(y % 256);
	_writeData(ye / 256);
	_writeData(ye % 256);
	_writeData(0x01); // don't see any difference
}

void  _updatePartialWindow(const uint8_t * buffer, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	_writeCommand(PARTIAL_IN); // 0x91	
	_setPartialWindow(x, y, w, h);
	_writeCommand(DATA_START_TRANSMISSION_2); // 0x13
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w / 8 ; j++)
		{
			_writeData(buffer[i * w / 8 + j]);
			//Serial.print(".");
		}
	}
	_writeCommand(PARTIAL_OUT); // 0x92
	_delay(1);
	
	
#if 0
	_writeCommand(0x12);
	_waitWhileBusy(partial_refresh_time);
	
	
	_writeCommand(PARTIAL_IN); // 0x91	
	//_setPartialWindow(x, y, w, h);
	_writeCommand(DATA_START_TRANSMISSION_2); // 0x13
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w / 8 ; j++)
		{
			_writeData(buffer[i * w / 8 + j]);
			//Serial.print(".");
		}
	}
	_writeCommand(PARTIAL_OUT); // 0x92
	_delay(1);
#endif
}

void  _updateFullWindow(const uint8_t * buffer)
{
	_writeCommand(DATA_START_TRANSMISSION_2); // 0x13
	for (int i = 0; i < WAVESHARE_420_WIDTH / 8 * WAVESHARE_420_HEIGHT; i++)
		_writeData(buffer[i]);
	_delay(1);
}

void _transfer(uint8_t command, const uint8_t * buffer)
{
	_writeCommand(command);
	
	for (int i = 0; i < WAVESHARE_420_WIDTH / 8 * WAVESHARE_420_HEIGHT; i++)
		_writeData(buffer[i]);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
//

void init()
{
	_reset();
	
	_initDisplay();
}

void refresh(bool fast_mode)
{
	if (! (_state & _FAST_MODE))
	{
		if (fast_mode)
			_setLUTPartial();
	}
	else
	{
		if (! fast_mode)
			_setLUTFull();
	}
	//_powerOn();
	
	if (fast_mode)
	{
		_writeCommand(PARTIAL_IN); // 0x91	
		_setPartialWindow(0, 0, WAVESHARE_420_WIDTH, WAVESHARE_420_HEIGHT);
	}
	
	_transfer(DATA_START_TRANSMISSION_2, buffer); // 0x13
	
	if (fast_mode)
	{
		_writeCommand(PARTIAL_OUT); // 0x92
	}
	_delay(1);
	
	_writeCommand(0x12);
	_waitWhileBusy(fast_mode ? partial_refresh_time : full_refresh_time);	
	//_powerOff();
	
	//_transfer(DATA_START_TRANSMISSION_1, buffer);	
}

void powerOff()
{
	_powerOff();
}

void deepSleep()
{
	//
	_powerOff();
	
	//
	_writeCommand(DEEP_SLEEP);
	_writeData(0xA5);
	
	_state = _DEEP_SLEEP;
}

void transfer()
{
	//_transfer(DATA_START_TRANSMISSION_1, buffer);
	//_transfer(DATA_START_TRANSMISSION_2, buffer);
	//_delay(1);
}








/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
static void EPD_4IN2_Reset(void)
{
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
    DEV_Digital_Write(EPD_RST_PIN, 0);
    DEV_Delay_ms(200);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static void EPD_4IN2_SendCommand(UBYTE Reg)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void EPD_4IN2_SendData(UBYTE Data)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Data);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
static void EPD_4IN2_ReadBusy(void)
{
    Debug("e-Paper busy\r\n");
	EPD_4IN2_SendCommand(0x71);
    while(DEV_Digital_Read(EPD_BUSY_PIN) == 0) {      //LOW: idle, HIGH: busy
		EPD_4IN2_SendCommand(0x71);
        DEV_Delay_ms(100);
    }
    Debug("e-Paper busy release\r\n");
}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
static void EPD_4IN2_TurnOnDisplay(void)
{
    EPD_4IN2_SendCommand(0x12);
    DEV_Delay_ms(100);
    EPD_4IN2_ReadBusy();
}

/******************************************************************************
function :	set the look-up tables
parameter:
******************************************************************************/
static void EPD_4IN2_SetLut(void)
{
    UWORD count;
    EPD_4IN2_SendCommand(0x20);         //g vcom
    for(count=0; count<44; count++) {
        EPD_4IN2_SendData(EPD_4IN2_lut_vcom0[count]);
    }

    EPD_4IN2_SendCommand(0x21);
    for(count=0; count<42; count++) {
        EPD_4IN2_SendData(EPD_4IN2_lut_ww[count]);
    }

    EPD_4IN2_SendCommand(0x22);
    for(count=0; count<42; count++) {
        EPD_4IN2_SendData(EPD_4IN2_lut_bw[count]);
    }

    EPD_4IN2_SendCommand(0x23);
    for(count=0; count<42; count++) {
        EPD_4IN2_SendData(EPD_4IN2_lut_wb[count]);
    }

    EPD_4IN2_SendCommand(0x24);
    for(count=0; count<42; count++) {
        EPD_4IN2_SendData(EPD_4IN2_lut_bb[count]);
	}
}

static void EPD_4IN2_Partial_SetLut(void)
{
	unsigned int count;
	EPD_4IN2_SendCommand(0x20);
	for(count=0;count<44;count++)	     
		{EPD_4IN2_SendData(EPD_4IN2_Partial_lut_vcom1[count]);}

	EPD_4IN2_SendCommand(0x21);
	for(count=0;count<42;count++)	     
		{EPD_4IN2_SendData(EPD_4IN2_Partial_lut_ww1[count]);}   
	
	EPD_4IN2_SendCommand(0x22);
	for(count=0;count<42;count++)	     
		{EPD_4IN2_SendData(EPD_4IN2_Partial_lut_bw1[count]);} 

	EPD_4IN2_SendCommand(0x23);
	for(count=0;count<42;count++)	     
		{EPD_4IN2_SendData(EPD_4IN2_Partial_lut_wb1[count]);} 

	EPD_4IN2_SendCommand(0x24);
	for(count=0;count<42;count++)	     
		{EPD_4IN2_SendData(EPD_4IN2_Partial_lut_bb1[count]);}   
}




/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
void EPD_4IN2_Ex_Init(void)
{
#if 0
	EPD_4IN2_Reset();

    EPD_4IN2_SendCommand(0x01); // POWER SETTING
    EPD_4IN2_SendData(0x03);
    EPD_4IN2_SendData(0x00);
    EPD_4IN2_SendData(0x2b);
    EPD_4IN2_SendData(0x2b);

    EPD_4IN2_SendCommand(0x06); // boost soft start
    EPD_4IN2_SendData(0x17);		//A
    EPD_4IN2_SendData(0x17);		//B
    EPD_4IN2_SendData(0x17);		//C

    EPD_4IN2_SendCommand(0x04); // POWER_ON
    EPD_4IN2_ReadBusy();

    EPD_4IN2_SendCommand(0x00); // panel setting
    EPD_4IN2_SendData(0xbf); // KW-BF   KWR-AF	BWROTP 0f	BWOTP 1f
    EPD_4IN2_SendData(0x0d);

    EPD_4IN2_SendCommand(0x30); // PLL setting
    EPD_4IN2_SendData(0x3C); // 3A 100HZ   29 150Hz 39 200HZ	31 171HZ

    EPD_4IN2_SendCommand(0x61); // resolution setting
    EPD_4IN2_SendData(0x01);
    EPD_4IN2_SendData(0x90); //128
    EPD_4IN2_SendData(0x01); //
    EPD_4IN2_SendData(0x2c);

    EPD_4IN2_SendCommand(0x82); // vcom_DC setting
    EPD_4IN2_SendData(0x28);

    EPD_4IN2_SendCommand(0X50); // VCOM AND DATA INTERVAL SETTING
    EPD_4IN2_SendData(0x97); // 97white border 77black border		VBDF 17|D7 VBDW 97 VBDB 57		VBDF F7 VBDW 77 VBDB 37  VBDR B7

    EPD_4IN2_SetLut();
#else
	init();
#endif	
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_4IN2_Ex_Clear(void)
{
	#if 0
	UWORD Width, Height;
    Width = (EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1);
    Height = EPD_4IN2_HEIGHT;

    EPD_4IN2_SendCommand(0x10);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_4IN2_SendData(0xFF);
        }
    }

    EPD_4IN2_SendCommand(0x13);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_4IN2_SendData(0xFF);
        }
    }
	EPD_4IN2_SendCommand(0x12);		 //DISPLAY REFRESH 		
	DEV_Delay_ms(10);	
    EPD_4IN2_TurnOnDisplay();
	#else
	#endif
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_4IN2_Ex_Display(UBYTE *Image)
{
	#if 0
	UWORD Width, Height;
    Width = (EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1);
    Height = EPD_4IN2_HEIGHT;

    EPD_4IN2_SendCommand(0x13);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_4IN2_SendData(Image[i + j * Width]);
        }
    }
		
    EPD_4IN2_TurnOnDisplay();
	#else
	buffer = Image;
	refresh(0);	
	#endif
}

void EPD_4IN2_Ex_PartialDisplay(UWORD X_start,UWORD Y_start,UWORD X_end,UWORD Y_end, UBYTE *Image)
{
	#if 0
	UWORD Width, Height;
    Width = (EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1);
    Height = EPD_4IN2_HEIGHT;
	
	X_start = (X_start % 8 == 0)? (X_start): (X_start/8*8+8);
	X_end = (X_end % 8 == 0)? (X_end): (X_end/8*8+8);
	
	EPD_4IN2_SendCommand(0X50);
	EPD_4IN2_SendData(0xf7);
	DEV_Delay_ms(100);
	
	EPD_4IN2_SendCommand(0x82);			//vcom_DC setting  	
	EPD_4IN2_SendData (0x08);	
	EPD_4IN2_SendCommand(0X50);
	EPD_4IN2_SendData(0x47);		
	EPD_4IN2_Partial_SetLut();
	EPD_4IN2_SendCommand(0x91);		//This command makes the display enter partial mode
	EPD_4IN2_SendCommand(0x90);		//resolution setting
	EPD_4IN2_SendData ((X_start)/256);
	EPD_4IN2_SendData ((X_start)%256);   //x-start    

	EPD_4IN2_SendData ((X_end )/256);		
	EPD_4IN2_SendData ((X_end )%256-1);  //x-end

	EPD_4IN2_SendData (Y_start/256);
	EPD_4IN2_SendData (Y_start%256);   //y-start    

	EPD_4IN2_SendData (Y_end/256);		
	EPD_4IN2_SendData (Y_end%256-1);  //y-end
	EPD_4IN2_SendData (0x28);	

	EPD_4IN2_SendCommand(0x10);	       //writes Old data to SRAM for programming
    for (UWORD j = 0; j < Y_end - Y_start; j++) {
        for (UWORD i = 0; i < (X_end - X_start)/8; i++) {
            EPD_4IN2_SendData(Image[(Y_start + j)*Width + X_start/8 + i]);
        }
    }
	EPD_4IN2_SendCommand(0x13);				 //writes New data to SRAM.
    for (UWORD j = 0; j < Y_end - Y_start; j++) {
        for (UWORD i = 0; i < (X_end - X_start)/8; i++) {
            EPD_4IN2_SendData(~Image[(Y_start + j)*Width + X_start/8 + i]);
        }
    }

	EPD_4IN2_SendCommand(0x12);		 //DISPLAY REFRESH 		             
	DEV_Delay_ms(10);     //The delay here is necessary, 200uS at least!!!     
	EPD_4IN2_TurnOnDisplay();
	#else
	buffer = Image;
	refresh(1);	
	#endif
}


/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_4IN2_Ex_Sleep(void)
{
    EPD_4IN2_SendCommand(0x02); // POWER_OFF
    EPD_4IN2_ReadBusy();
	
    EPD_4IN2_SendCommand(0x07); // DEEP_SLEEP
    EPD_4IN2_SendData(0xA5);
}