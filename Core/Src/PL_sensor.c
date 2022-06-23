/*
 * PL_sensor.c
 *
 *  Created on: Jun 1, 2022
 *      Author: sf199
 */


#include <PL_sensor.h>
#include "adc.h"
#include "dma.h"
#include "gpio.h"



uint16_t g_ADCBuffer[5];
char AD_step;
char sensor_mode;

uint16_t g_sensor_on[4];
uint16_t g_sensor_off[4];


float g_V_batt;


/*******************************************************************/
/*	電圧の取得			(pl_getbatt)	*/
/*******************************************************************/
/*	戻り値に電圧を返す．						*/
/*******************************************************************/
float pl_getbatt(void){
	 float batt;
	 uint16_t battAD;


	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 50);
	battAD = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	batt = 3.3  * (float) battAD / 1023.0 * (100.0 + 22.0) / 22.0;


return batt;
}

/*******************************************************************/
/*	callback用関数			(pl_callback_getSensor)	*/
/*******************************************************************/
/*	DMAがスタートしたら実行するコード					*/
/*******************************************************************/
void pl_callback_getSensor(void) {
	uint16_t V_battAD;

	int j;
	HAL_ADC_Stop_DMA(&hadc1);
	switch (AD_step) {
		case 0:
			HAL_GPIO_WritePin(SENSORLED_1_GPIO_Port, SENSORLED_1_Pin, GPIO_PIN_SET);
		    HAL_GPIO_WritePin(SENSORLED_2_GPIO_Port, SENSORLED_2_Pin,GPIO_PIN_RESET);
					for (j = 0; j <= 500; j++) {
					}
			break;
		case 1:
			g_sensor_on[0] = g_ADCBuffer[1];
			g_sensor_on[1] = g_ADCBuffer[2];
			g_sensor_off[2] = g_ADCBuffer[3];
			g_sensor_off[3] = g_ADCBuffer[4];
			HAL_GPIO_WritePin(SENSORLED_1_GPIO_Port, SENSORLED_1_Pin, GPIO_PIN_RESET);
		    HAL_GPIO_WritePin(SENSORLED_2_GPIO_Port, SENSORLED_2_Pin,GPIO_PIN_SET);
					for (j = 0; j <= 500; j++) {
					}
			break;
		case 2:
			g_sensor_off[0] = g_ADCBuffer[1];
			g_sensor_off[1] = g_ADCBuffer[2];
			g_sensor_on[2] = g_ADCBuffer[3];
			g_sensor_on[3] = g_ADCBuffer[4];
			HAL_GPIO_WritePin(SENSORLED_1_GPIO_Port, SENSORLED_1_Pin, GPIO_PIN_RESET);
		    HAL_GPIO_WritePin(SENSORLED_2_GPIO_Port, SENSORLED_2_Pin,GPIO_PIN_RESET);
					for (j = 0; j <= 10; j++) {
					}
			break;
	}
	V_battAD = g_ADCBuffer[0];
		g_V_batt = 3.3 * (float) V_battAD / 1023 * (100.0 + 22.0) / 22.0;
		AD_step++;

		if (AD_step != 3) {
			HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,
					sizeof(g_ADCBuffer) / sizeof(uint16_t));

		} else {
			AD_step = 0;

		}

}




/*******************************************************************/
/*	割り込み用動作関数(センサー取得)			(interupt_calSensor)	*/
/*******************************************************************/
/*	センサーの情報を取得する割り込み関数．						*/
/*******************************************************************/
void pl_interupt_getSensor(void){
	if (sensor_mode == 1) {
		HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,
				sizeof(g_ADCBuffer) / sizeof(uint16_t));
	}

}
