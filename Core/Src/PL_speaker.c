/*
 * PL_speaker.c
 *
 *  Created on: 2022/06/22
 *      Author: sf199
 */


#include "PL_speaker.h"
#include "tim.h"

void pl_speaker_init(void)
{

	  HAL_TIM_Base_Start_IT(&htim15);//speaker
	  HAL_TIM_PWM_MspInit(&htim15);//speaker

}
