// host_hid.c
//

#include "hid_host.h"
#include "usb_host.h"


extern USBH_HandleTypeDef hUsbHostHS;
extern ApplicationTypeDef Appli_state;

HID_MOUSE_Info_TypeDef mouse_info;


static void USBH_MouseDemo(USBH_HandleTypeDef * phost);
static void USBH_KeyboardDemo(USBH_HandleTypeDef * phost);


HID_StateMachine hid_sm;



void HID_InitApplication(void)
{
	// state = ready;
	hid_sm.state = HID_APP_IDLE;
}

void HID_HOST_Start(void)
{
	hid_sm.state = HID_APP_START;
}


void HID_HOST_Process(void)
{
	switch (hid_sm.state)
	{
	case HID_APP_IDLE:
		break;
	case HID_APP_WAIT:
		break;
	case HID_APP_START:
		if(Appli_state == APPLICATION_READY)
		{
			if(USBH_HID_GetDeviceType(&hUsbHostHS) == HID_KEYBOARD)
			{
				hid_sm.state = HID_APP_KEYBOARD;
				HID_KEYBOARD_Init();
				printf("KEYBOARD READY\n");
			}
			else if(USBH_HID_GetDeviceType(&hUsbHostHS) == HID_MOUSE)
			{
				hid_sm.state = HID_APP_MOUSE;
				HID_MOUSE_Init();
				printf("MOUSE READY\n");
			}
		}
		break;
	case HID_APP_MOUSE:
		if(Appli_state == APPLICATION_READY)
		{
			USBH_MouseDemo(&hUsbHostHS);
		}
		break;
	case HID_APP_KEYBOARD:
		if(Appli_state == APPLICATION_READY)
		{
			USBH_KeyboardDemo(&hUsbHostHS);
		}
		break;
	case HID_APP_REENUMERATE:
		break;
		
	default:
		break;
	}
}


/**
  * @brief  Main routine for Mouse application
  * @param  phost: Host handle
  * @retval None
  */
static void USBH_MouseDemo(USBH_HandleTypeDef * phost)
{
  HID_MOUSE_Info_TypeDef *m_pinfo;

  m_pinfo = USBH_HID_GetMouseInfo(phost);
  if (m_pinfo != NULL)
  {
    /* Handle Mouse data position */
    HID_MOUSE_ProcessData(&mouse_info);
    printf("Mouse (%d,%d)\n", mouse_info.x, mouse_info.y);

    if (m_pinfo->buttons[0])
    {
      HID_MOUSE_ButtonPressed(0);
    }
    else
    {
      HID_MOUSE_ButtonReleased(0);
    }

    if (m_pinfo->buttons[1])
    {
      HID_MOUSE_ButtonPressed(2);
    }
    else
    {
      HID_MOUSE_ButtonReleased(2);
    }

    if (m_pinfo->buttons[2])
    {
      HID_MOUSE_ButtonPressed(1);
    }
    else
    {
      HID_MOUSE_ButtonReleased(1);
    }
  }
}

/**
  * @brief  Main routine for Keyboard application
  * @param  phost: Host handle
  * @retval None
  */
static void USBH_KeyboardDemo(USBH_HandleTypeDef * phost)
{
  HID_KEYBD_Info_TypeDef *k_pinfo;
  char c;
  k_pinfo = USBH_HID_GetKeybdInfo(phost);

  if (k_pinfo != NULL)
  {
    c = USBH_HID_GetASCIICode(k_pinfo);
    if (c != 0)
    {
      HID_KEYBOARD_ProcessData(c);
      printf("%c", c);
    }
  }
}

