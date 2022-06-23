/*
 * PL_motor.h
 *
 *  Created on: Jun 22, 2022
 *      Author: sf199
 */

#ifndef INC_PL_MOTOR_H_
#define INC_PL_MOTOR_H_

#include "stm32l4xx_hal.h"


void pl_test_motor();

void pl_motor_init();

void pl_motor_standby(int);
void pl_L_motor_mode(int);
void pl_R_motor_mode(int);

void pl_motor_start();
void pl_motor_stop();

void pl_motor_count(float,float);

uint16_t calMotorVelocityCount(float);

#endif /* INC_PL_MOTOR_H_ */
