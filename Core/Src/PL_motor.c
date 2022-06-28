/*
 * PL_motor.c
 *
 *  Created on: Jun 22, 2022
 *      Author: sf199
 */


#include "PL_motor.h"
#include "gpio.h"
#include "tim.h"
#include "define.h"

#include "math.h"


uint16_t g_motorCount_l,g_motorCount_r;


void pl_test_motor(void)
{

	pl_motor_standby(1);
	pl_motor_start();
	for(int count=100;count<600;count++){
		pl_motor_count_L((float)(count));
		pl_motor_count_R((float)(count));
		HAL_Delay(1);
	}
	for(int count=600;count>100;count--){
		pl_motor_count_L((float)(count));
		pl_motor_count_R((float)(count));
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

	  pl_motor_mode_L(1);
	  pl_motor_mode_R(1);



}

void pl_motor_standby(int pin){
	HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_Port, MOTOR_ENABLE_Pin, pin);
	pl_motor_mode_L(1);
	pl_motor_mode_R(1);
	HAL_GPIO_WritePin(MD_RESET_GPIO_Port,MD_RESET_Pin,GPIO_PIN_SET);
	HAL_Delay(3);
	HAL_GPIO_WritePin(MD_RESET_GPIO_Port,MD_RESET_Pin,GPIO_PIN_RESET);
	HAL_Delay(500);
}

void pl_motor_mode_L(float velocity_l){
	if (velocity_l>=0){
		HAL_GPIO_WritePin(MOTOR_CW_CCW_L_GPIO_Port,MOTOR_CW_CCW_L_Pin,L_MOTOR_FRONT);
	}else{
		HAL_GPIO_WritePin(MOTOR_CW_CCW_L_GPIO_Port,MOTOR_CW_CCW_L_Pin,L_MOTOR_BACK);
	}
}

void pl_motor_mode_R(float velocity_r){
	if (velocity_r>=0){
		HAL_GPIO_WritePin(MOTOR_CW_CCW_R_GPIO_Port,MOTOR_CW_CCW_R_Pin,R_MOTOR_FRONT);
	}else{
		HAL_GPIO_WritePin(MOTOR_CW_CCW_R_GPIO_Port,MOTOR_CW_CCW_R_Pin,R_MOTOR_BACK);
	}
}

void pl_motor_start(void){
	pl_interrupt_motor_count_L();
	pl_interrupt_motor_count_R();
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}

void pl_motor_stop(void){
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
}

void pl_motor_count_L(float velocity_l){
//	uint16_t motorCount_l;
	g_motorCount_l = calMotorVelocityCount(velocity_l);
//	__HAL_TIM_SET_AUTORELOAD(&htim1, g_motorCount_l);
//	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,(uint16_t)((float)(g_motorCount_l)/2));
//	__HAL_TIM_SET_COUNTER(&htim1, 0);
}

void pl_motor_count_R(float velocity_r){
//	uint16_t motorCount_r;
	g_motorCount_r = calMotorVelocityCount(velocity_r);
//	__HAL_TIM_SET_AUTORELOAD(&htim2, g_motorCount_r);
//	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,(uint16_t)((float)(g_motorCount_r)/2));
//	__HAL_TIM_SET_COUNTER(&htim2, 0);

}

void pl_interrupt_motor_count_L(void){
	__HAL_TIM_SET_AUTORELOAD(&htim1, g_motorCount_l);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,(uint16_t)((float)(g_motorCount_l)/2));
	__HAL_TIM_SET_COUNTER(&htim1, 0);
}

void pl_interrupt_motor_count_R(void){
	__HAL_TIM_SET_AUTORELOAD(&htim2, g_motorCount_r);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,(uint16_t)((float)(g_motorCount_r)/2));
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

	f_MotorCount=(10000000 * STEP_DEGREE * M_PI / 180 * TIRE_DIAMETER / 2 / fabs(Velocity));
	if (Velocity == 0 || f_MotorCount > 65535 || f_MotorCount < 0) {
		MotorCount = 30535 - 1;
	} else {
		MotorCount = (uint16_t) (f_MotorCount)-1;
	}

	return MotorCount;
}


