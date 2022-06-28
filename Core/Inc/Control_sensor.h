/*
 * Control_sensor.h
 *
 *  Created on: Jun 28, 2022
 *      Author: sf199
 */

#ifndef INC_CONTROL_SENSOR_H_
#define INC_CONTROL_SENSOR_H_

extern int g_sensor[5][20];
extern int g_sensor_diff[5];
extern int g_sensor_mean[5];

void battcheak();

void interrupt_calSensor();

#endif /* INC_CONTROL_SENSOR_H_ */
