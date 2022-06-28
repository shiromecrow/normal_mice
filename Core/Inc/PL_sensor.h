/*
 * PL_sensor.h
 *
 *  Created on: Jun 1, 2022
 *      Author: sf199
 */

#ifndef INC_PL_SENSOR_H_
#define INC_PL_SENSOR_H_

#include "stm32l4xx_hal.h"

extern uint16_t g_ADCBuffer[5];
extern char sensor_mode;


extern uint16_t g_sensor_on[4];
extern uint16_t g_sensor_off[4];



extern float g_V_batt;

float pl_getbatt();

void pl_callback_getSensor();

void pl_interupt_getSensor();

#endif /* INC_PL_SENSOR_H_ */
