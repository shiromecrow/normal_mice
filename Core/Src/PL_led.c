/*
 * PL_led.c
 *
 *  Created on: Jun 30, 2022
 *      Author: sf199
 */


#include "PL_led.h"
#include "gpio.h"

void write_LED(char pin){

	HAL_GPIO_WritePin(INTERFACELED_GPIO_Port,INTERFACELED_Pin,pin);

}
