/*
 * lv_port.h
 *
 *  Created on: 2021. 6. 14.
 *      Author: akkdong
 */

#ifndef INC_LV_PORT_H_
#define INC_LV_PORT_H_

#include "lvgl/lvgl.h"


#ifdef __cplusplus
extern "C" {
#endif


//

void hal_init(void);

//
void app_init(void);


#ifdef __cplusplus
}
#endif


#endif /* INC_LV_PORT_H_ */
