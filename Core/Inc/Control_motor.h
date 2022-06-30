/*
 * Control_motor.h
 *
 *  Created on: Jun 23, 2022
 *      Author: sf199
 */

#ifndef INC_CONTROL_MOTOR_H_
#define INC_CONTROL_MOTOR_H_

#include "stm32l4xx_hal.h"

typedef struct {
	float velocity;
	float acceleration;
	float displacement;

}TARGET;

typedef struct{
	float displacement;
	float start_velocity;
	float end_velocity;
	float count_velocity;
	float acceleration;

}TRAPEZOID;

typedef struct {
	uint8_t WallControlMode;//0で壁制御なし、1で通常の壁制御、2で斜めの制御
	uint8_t WallControlStatus;
	uint8_t calMazeMode;
	uint8_t WallCutMode;



}MOTOR_MODE;



extern TARGET g_TargetStraight;;
extern TARGET g_TargetTurning;

void control_test_motor(uint8_t);

void motor_init();

void interrupt_Motor();


void cal_table(TRAPEZOID,TARGET *);

float straight_table(float, float, float, float, float,MOTOR_MODE);

float turning_table(float, float, float, float, float);

float slalom_table(float,float, float, float, float, float);

#endif /* INC_CONTROL_MOTOR_H_ */
