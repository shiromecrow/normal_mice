/*
 * PID_wall.h
 *
 *  Created on: Jun 29, 2022
 *      Author: sf199
 */

#ifndef INC_PID_WALL_H_
#define INC_PID_WALL_H_

#include "stm32l4xx_hal.h"

#define CONTROLLEFTWALL 1
#define CONTROLRIGHTWALL 2

//typedef struct {
//	uint8_t g_WallControl_mode;//0で壁制御なし、1で通常の壁制御、2で斜めの制御
//	uint8_t g_WallControlStatus;
//
//
//}CONTROLWALL_MODE;

extern uint8_t g_WallControl_mode;


void init_WallControl();

float calWallConrol();


#endif /* INC_PID_WALL_H_ */
