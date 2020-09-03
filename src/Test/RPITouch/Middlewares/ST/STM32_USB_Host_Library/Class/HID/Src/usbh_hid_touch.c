/**
  ******************************************************************************
  * @file    usbh_hid_touch.h
  * @author  Kangwoo Cheon
  * @version V0.1.0
  * @date    08-August-2020
  * @brief   This file contains all the prototypes for the usbh_hid_touch.c
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usbh_hid_touch.h"
#include "usbh_hid_parser.h"


/** @addtogroup USBH_LIB
  * @{
  */

/** @addtogroup USBH_CLASS
  * @{
  */

/** @addtogroup USBH_HID_CLASS
  * @{
  */

/** @defgroup USBH_HID_TOUCH
  * @brief    This file includes HID Layer Handlers for USB Host HID class.
  * @{
  */

/** @defgroup USBH_HID_TOUCH_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup USBH_HID_TOUCH_Private_Defines
  * @{
  */
/**
  * @}
  */


/** @defgroup USBH_HID_TOUCH_Private_Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup USBH_HID_TOUCH_Private_FunctionPrototypes
  * @{
  */
static USBH_StatusTypeDef USBH_HID_TouchDecode(USBH_HandleTypeDef *phost);

/**
  * @}
  */


/** @defgroup USBH_HID_TOUCH_Private_Variables
  * @{
  */
HID_TOUCH_Info_TypeDef    touch_info;
uint8_t                   touch_report_data[22];


/* Structures defining how to access items in a HID touch report */
/* Access button state. */
static const HID_Report_ItemTypedef prop_state={
  (uint8_t *)touch_report_data+0, /*data*/
  1,     /*size*/
  0,     /*shift*/
  0,     /*count (only for array items)*/
  0,     /*signed?*/
  0,     /*min value read can return*/
  1,     /*max value read can return*/
  0,     /*min value device can report*/
  1,     /*max value device can report*/
  1      /*resolution*/
};

/* Access x coordinate change. */
static const HID_Report_ItemTypedef prop_x={
  (uint8_t *)touch_report_data+1, /*data*/
  16,     /*size*/
  0,     /*shift*/
  0,     /*count (only for array items)*/
  0,     /*signed?*/
  0,     /*min value read can return*/
  0xFFFF,/*max value read can return*/
  0,     /*min vale device can report*/
  0xFFFF,/*max value device can report*/
  1      /*resolution*/
};

/* Access y coordinate change. */
static const HID_Report_ItemTypedef prop_y={
  (uint8_t *)touch_report_data+3, /*data*/
  16,     /*size*/
  0,     /*shift*/
  0,     /*count (only for array items)*/
  0,     /*signed?*/
  0,     /*min value read can return*/
  0xFFFF,/*max value read can return*/
  0,     /*min vale device can report*/
  0xFFFF,/*max value device can report*/
  1      /*resolution*/
};


/**
  * @}
  */


/** @defgroup USBH_HID_TOUCH_Private_Functions
  * @{
  */

/**
  * @brief  USBH_HID_TouchInit
  *         The function init the HID touch.
  * @param  phost: Host handle
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_HID_TouchInit(USBH_HandleTypeDef *phost)
{
  HID_HandleTypeDef *HID_Handle =  (HID_HandleTypeDef *) phost->pActiveClass->pData;

  touch_info.x = 0;
  touch_info.y = 0;
  touch_info.state = 0;

  for (int i = 0; i < sizeof(touch_report_data); i++)
	  touch_report_data[i]=0;

  if(HID_Handle->length > sizeof(touch_report_data))
    HID_Handle->length = sizeof(touch_report_data);

  HID_Handle->pData = (uint8_t *)touch_report_data;
  USBH_HID_FifoInit(&HID_Handle->fifo, phost->device.Data, HID_QUEUE_SIZE * sizeof(touch_report_data));

  return USBH_OK;
}

/**
  * @brief  USBH_HID_GetTouchInfo
  *         The function return touch information.
  * @param  phost: Host handle
  * @retval touch information
  */
HID_TOUCH_Info_TypeDef *USBH_HID_GetTouchInfo(USBH_HandleTypeDef *phost)
{
	USBH_StatusTypeDef status = USBH_HID_TouchDecode(phost);
	if(status == USBH_OK)
	{
		return &touch_info;
	}
	else
	{
		return NULL;
	}
}

/**
  * @brief  USBH_HID_TouchDecode
  *         The function decode touch data.
  * @param  phost: Host handle
  * @retval USBH Status
  */
static USBH_StatusTypeDef USBH_HID_TouchDecode(USBH_HandleTypeDef *phost)
{
  HID_HandleTypeDef *HID_Handle = (HID_HandleTypeDef *) phost->pActiveClass->pData;

  if(HID_Handle->length == 0)
  {
    return USBH_FAIL;
  }

  /*Fill report */
  if (USBH_HID_FifoRead(&HID_Handle->fifo, &touch_report_data, HID_Handle->length) ==  HID_Handle->length)
  {
    /*Decode report */
	//touch_info.state = (uint8_t)HID_ReadItem((HID_Report_ItemTypedef *) &prop_state, 0);
	//touch_info.x = (uint16_t)HID_ReadItem((HID_Report_ItemTypedef *) &prop_x, 0);
	//touch_info.y = (uint16_t)HID_ReadItem((HID_Report_ItemTypedef *) &prop_y, 0);
	  touch_info.state = touch_report_data[1];
	  touch_info.x = touch_report_data[2] * 256 + touch_report_data[3];
	  touch_info.y = touch_report_data[4] * 256 + touch_report_data[5];

    return USBH_OK;
  }

  return   USBH_FAIL;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
