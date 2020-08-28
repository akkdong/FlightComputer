/**
  ******************************************************************************
  * @file    usbh_hid_touch.h
  * @author  Kangwoo Cheon
  * @version V0.1.0
  * @date    08-August-2020
  * @brief   This file contains all the prototypes for the usbh_hid_touch.c
  ******************************************************************************
  */

/* Define to prevent recursive  ----------------------------------------------*/
#ifndef __USBH_HID_TOUCH_H
#define __USBH_HID_TOUCH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbh_hid.h"

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
  * @brief This file is the Header file for usbh_hid_touch.c
  * @{
  */


/** @defgroup USBH_HID_TOUCH_Exported_Types
  * @{
  */

typedef struct _HID_TOUCH_Info
{
  uint16_t              x;
  uint16_t              y;
  uint8_t              state;
}
HID_TOUCH_Info_TypeDef;

/**
  * @}
  */

/** @defgroup USBH_HIDTOUCH_Exported_Defines
  * @{
  */
/**
  * @}
  */

/** @defgroup USBH_HID_TOUCH_Exported_Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup USBH_HID_TOUCH_Exported_Variables
  * @{
  */
/**
  * @}
  */

/** @defgroup USBH_HID_TOUCH_Exported_FunctionsPrototype
  * @{
  */
USBH_StatusTypeDef USBH_HID_TouchInit(USBH_HandleTypeDef *phost);
HID_TOUCH_Info_TypeDef *USBH_HID_GetTouchInfo(USBH_HandleTypeDef *phost);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __USBH_HID_TOUCH_H */

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

