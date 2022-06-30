/*
 * PL_switch.c
 *
 *  Created on: Jun 30, 2022
 *      Author: sf199
 */


#include "PL_switch.h"
#include "gpio.h"

char read_switch1(void){

	char check=(HAL_GPIO_ReadPin(SWITCH_1_GPIO_Port,SWITCH_1_Pin)==0);


return check;
}

char read_switch2(void){

	char check=(HAL_GPIO_ReadPin(SWITCH_2_GPIO_Port,SWITCH_2_Pin)==0);


return check;
}


