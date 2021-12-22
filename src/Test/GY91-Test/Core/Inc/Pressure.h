/*
 * Pressure.h
 *
 *  Created on: 2021. 12. 21.
 *      Author: akkdong
 */

#ifndef INC_PRESSURE_H_
#define INC_PRESSURE_H_

#ifdef __cplusplus
extern "C"
{
#endif

//
//
//

int		vario_init();
float	vario_update();

//
//
//

int 	baro_init();
void	baro_measure();

float 	baro_getTemperature();
float	baro_getPressure();
float	baro_getAltitude();


#ifdef __cplusplus
}
#endif


#endif /* INC_PRESSURE_H_ */
