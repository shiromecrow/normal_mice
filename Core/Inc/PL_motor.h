/*
 * PL_motor.h
 *
 *  Created on: Jun 22, 2022
 *      Author: sf199
 */

#ifndef INC_PL_MOTOR_H_
#define INC_PL_MOTOR_H_

#include "stm32l4xx_hal.h"

extern uint16_t g_motorCount_l,g_motorCount_r;


void pl_test_motor();

void pl_motor_init();

void pl_motor_standby(int);
void pl_motor_mode_L(float);
void pl_motor_mode_R(float);

void pl_motor_start();
void pl_motor_stop();

void pl_motor_count_L(float);
void pl_motor_count_R(float);

void pl_interrupt_motor_count_L();
void pl_interrupt_motor_count_R();

uint16_t calMotorVelocityCount(float);

#endif /* INC_PL_MOTOR_H_ */
