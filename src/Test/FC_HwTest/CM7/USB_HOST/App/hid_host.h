// host_hid.h
//


#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include "usbh_hid.h"

enum _HID_AppState {
  HID_APP_IDLE = 0,
  HID_APP_WAIT,
  HID_APP_START,
  HID_APP_MOUSE,
  HID_APP_KEYBOARD,
  HID_APP_REENUMERATE,
};

typedef enum _HID_AppState HID_AppState;


enum _HID_MouseState {
  HID_MOUSE_IDLE = 0,
  HID_MOUSE_WAIT,
  HID_MOUSE_START,
};

typedef enum _HID_MouseState HID_MouseState;


enum _HID_KeyboardState {
  HID_KEYBOARD_IDLE = 0,
  HID_KEYBOARD_WAIT,
  HID_KEYBOARD_START,
};

typedef enum _HID_KeyboardState HID_KeyboardState;

/*
enum _HID_ApplicationTypeDef {
  APPLICATION_IDLE = 0,
  APPLICATION_DISCONNECT,
  APPLICATION_START,
  APPLICATION_READY,
  APPLICATION_RUNNING,
};

typedef enum _HID_ApplicationTypeDef HID_ApplicationTypeDef;
*/

typedef struct _HID_StateMachine {
  __IO HID_AppState     	state;
  __IO HID_MouseState    	mouse_state;
  __IO HID_KeyboardState 	keyboard_state;
  __IO uint8_t            	select;
  __IO uint8_t            	lock;
} HID_StateMachine;




void HID_InitApplication(void);
void HID_HOST_Start(void);
void HID_HOST_Process(void);


#include "hid_keyboard.h"
#include "hid_mouse.h"
