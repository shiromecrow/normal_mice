/*
 * PID_wall.c
 *
 *  Created on: Jun 29, 2022
 *      Author: sf199
 */

#include "PID_wall.h"
#include "Control_sensor.h"
#include "PL_motor.h"
#include "tim.h"
#include "define.h"

#include "stdio.h"
#include "math.h"

uint8_t g_WallControl_mode;//0で壁制御なし、1で通常の壁制御、2で斜めの制御
uint8_t g_WallControlStatus;
uint8_t StabilityCount_L,StabilityCount_R;

void init_WallControl(void){
	g_WallControl_mode=0;
	g_WallControlStatus=0;
	StabilityCount_L=0;
	StabilityCount_R=0;
}

float calWallConrol(void){
    float PID_wall;
//	float SensorDistanceL,SensorDistanceR;
//
//	//距離の線形補間
//	SensorDistanceL = -0.0000003162 * g_sensor[1][0] * g_sensor[1][0] * g_sensor[1][0]
//				+ 0.0006010785 * g_sensor[1][0] * g_sensor[1][0] - 0.4363050788 * g_sensor[1][0]
//				+ 190.114;
//
//	SensorDistanceR = -0.0000001684 * g_sensor[2][0] * g_sensor[2][0] * g_sensor[2][0]
//				+ 0.0004061427 * g_sensor[2][0] * g_sensor[2][0] - 0.3784837856 * g_sensor[2][0]
//				+ 197.1162;


    if(g_WallControl_mode == 0){
    	g_WallControlStatus=0;
    	StabilityCount_L=0;
    	StabilityCount_R=0;
    	PID_wall=0;

    }else if (g_WallControl_mode == 1) {

		// 左壁の有無の判定
		if ((g_WallControlStatus >> 0)&1 == 1){
			//前回左壁あり
			//閾値を下回る　or 変化量の急増
			if (g_sensor[SENSOR_LEFT][0] < CONTROLWALL_THRESHOLD_L || g_sensor_diff[SENSOR_LEFT] > CONTROLWALLCUT_THRESHOLD_L){
				g_WallControlStatus=g_WallControlStatus - 1;
			}
		}else{
			//前回左壁なし
			//閾値を上回る　and 変化量が落ち着く　+ その安定な状態が数回続く
			if (g_sensor[SENSOR_LEFT][0] > CONTROLWALL_THRESHOLD_L && g_sensor_diff[SENSOR_LEFT] < CONTROLWALLCUT_THRESHOLD_L){
				StabilityCount_L++;
			}else{
				StabilityCount_L=0;
			}
			if(StabilityCount_L>=10){
				g_WallControlStatus=g_WallControlStatus + 1;
			}
		}
		// 右壁の有無の判定
		if ((g_WallControlStatus >> 1)&1 == 1){
			//前回右壁あり
			//閾値を下回る　or 変化量の急増
			if (g_sensor[SENSOR_RIGHT][0] < CONTROLWALL_THRESHOLD_R || g_sensor_diff[SENSOR_RIGHT] > CONTROLWALLCUT_THRESHOLD_R){
				g_WallControlStatus=g_WallControlStatus - 2;
			}
		}else{
			//前回右壁なし
			//閾値を上回る　and 変化量が落ち着く　+ その安定な状態が数回続く
			if (g_sensor[SENSOR_RIGHT][0] > CONTROLWALL_THRESHOLD_R && g_sensor_diff[SENSOR_RIGHT] < CONTROLWALLCUT_THRESHOLD_R){
				StabilityCount_R++;
			}else{
				StabilityCount_R=0;
			}
			if(StabilityCount_R>=10){
				g_WallControlStatus=g_WallControlStatus + 2;
			}
		}
		switch (g_WallControlStatus){
		case 0://両壁なし
			PID_wall= 0;
		break;
		case 1://左壁のみ
			PID_wall= SENSOR_GAIN*(2*(float)(g_sensor[SENSOR_LEFT][0] - CENTER_L));
		break;
		case 2://右壁のみ
			PID_wall= SENSOR_GAIN * (-2 * (float)(g_sensor[SENSOR_RIGHT][0] - CENTER_R));
		break;
		case 3://両壁あり
			PID_wall= SENSOR_GAIN * ((float)(g_sensor[SENSOR_LEFT][0] - CENTER_L)-(float)(g_sensor[SENSOR_RIGHT][0] - CENTER_R));
		break;
		}


	}




	return PID_wall;
}
