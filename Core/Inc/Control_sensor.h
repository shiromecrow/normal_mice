/*
 * Control_sensor.h
 *
 *  Created on: Jun 28, 2022
 *      Author: sf199
 */

#ifndef INC_CONTROL_SENSOR_H_
#define INC_CONTROL_SENSOR_H_

extern int g_sensor[4][20];
extern int g_sensor_diff[4];
extern int g_sensor_mean[4];

void battcheak();

void interrupt_calSensor();

void sensor_line();

#endif /* INC_CONTROL_SENSOR_H_ */
