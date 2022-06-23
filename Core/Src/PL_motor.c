/*
 * PL_motor.c
 *
 *  Created on: Jun 22, 2022
 *      Author: sf199
 */


#include "PL_motor.h"
#include "tim.h"
#include "define.h"

#include "math.h"




void pl_test_motor(void)
{

	pl_motor_standby(1);
	pl_motor_start();
	for(int count=100;count<600;count++){
		pl_motor_count((float)(count),(float)(count));
		HAL_Delay(1);
	}
	for(int count=600;count>100;count--){
		pl_motor_count((float)(count),(float)(count));
		HAL_Delay(1);
	}

	pl_motor_stop();
	pl_motor_standby(0);
}



/*******************************************************************/
/*	モータの初期化					(pl_speaker_init)	*/
/*******************************************************************/
/*	モータの初期化する。						*/
/*******************************************************************/
void pl_motor_init(void)
{

	  HAL_TIM_Base_Start_IT(&htim1);//motor
	  HAL_TIM_PWM_MspInit(&htim1);//motor

	  HAL_TIM_Base_Start_IT(&htim2);//motor
	  HAL_TIM_PWM_MspInit(&htim2);//motor

	  pl_L_motor_mode(L_MOTOR_FRONT);
	  pl_R_motor_mode(R_MOTOR_FRONT);


}

void pl_motor_standby(int pin){
	HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin, pin);
	pl_L_motor_mode(L_MOTOR_FRONT);
	pl_R_motor_mode(R_MOTOR_FRONT);
	HAL_GPIO_WritePin(MD_RESET_GPIO_Port,MD_RESET_Pin,GPIO_PIN_SET);
	HAL_Delay(3);
	HAL_GPIO_WritePin(MD_RESET_GPIO_Port,MD_RESET_Pin,GPIO_PIN_RESET);
}

void pl_L_motor_mode(int l_motor_mode){
	HAL_GPIO_WritePin(MOTOR_CLOCK_L_GPIO_Port,MOTOR_CLOCK_L_Pin,l_motor_mode);
}

void pl_R_motor_mode(int r_motor_mode){
	HAL_GPIO_WritePin(MOTOR_CLOCK_R_GPIO_Port,MOTOR_CLOCK_R_Pin,r_motor_mode);
}

void pl_motor_start(void){
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}

void pl_motor_stop(void){
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
}

void pl_motor_count(float velocity_l,float velocity_r){
	uint16_t motorCount_l,motorCount_r;
	motorCount_l = calMotorVelocityCount(velocity_l);
	motorCount_r = calMotorVelocityCount(velocity_r);
	__HAL_TIM_SET_AUTORELOAD(&htim1, motorCount_l);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,(uint16_t)((float)(motorCount_l)/2));
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim2, motorCount_r);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,(uint16_t)((float)(motorCount_r)/2));
	__HAL_TIM_SET_COUNTER(&htim2, 0);


}

/*******************************************************************/
/*	速度からcycleCountへの変換					(calFrequencyCount)	*/
/*******************************************************************/
/*	速度からPWMに送るcycleCountを計算する．。						*/
/*******************************************************************/
uint16_t calMotorVelocityCount(float Velocity) {
	float f_MotorCount;
	uint16_t MotorCount;

	f_MotorCount=(10000000 * 0.9 * M_PI / 180 * TIRE_DIAMETER / 2 / fabs(Velocity));
	if (Velocity == 0 || f_MotorCount > 65535) {
		MotorCount = 65535 - 1;
	} else {
		MotorCount = (uint16_t) (f_MotorCount)-1;
	}

	return MotorCount;
}


