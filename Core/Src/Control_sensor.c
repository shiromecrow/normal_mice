/*
 * Control_sensor.c
 *
 *  Created on: Jun 28, 2022
 *      Author: sf199
 */


#include "Control_sensor.h"
#include "PL_sensor.h"
#include "PL_lcd.h"
#include "adc.h"
#include "define.h"
#include "stdio.h"
#include "math.h"

int g_sensor[5][20];
int g_sensor_diff[5];
int g_sensor_mean[5];

/*******************************************************************/
/*	バッテリーの確認				(battcheak)	*/
/*******************************************************************/
/*	バッテリーの残電圧のチェックし、小さい場合は機能の停止を行う．	．						*/
/*******************************************************************/
void battcheak(void){

	float batt;

	batt=pl_getbatt();
	if(batt <= LIPO_LIMIT){
		pl_stop_Sound();
		while(1){
			  pl_lcd_clear();
			  pl_lcd_pos(0, 0);
			  pl_lcd_puts("LIPO");
			  pl_lcd_pos(1, 0);
			  pl_lcd_puts("error");
			  HAL_Delay(1000);
		}
	}
}

/*******************************************************************/
/*	割り込み用動作関数(センサー処理)			(interupt_calSensor)	*/
/*******************************************************************/
/*	センサーの情報を処理する割り込み関数．						*/
/*******************************************************************/
void interrupt_calSensor(void){
	int j;

//	if (sensor_mode == 1) {
	for (j = 19; j >= 1; j--) {
		g_sensor[0][j] = g_sensor[0][j - 1];
		g_sensor[1][j] = g_sensor[1][j - 1];
		g_sensor[2][j] = g_sensor[2][j - 1];
		g_sensor[3][j] = g_sensor[3][j - 1];
		g_sensor[4][j] = g_sensor[4][j - 1];
	}
	g_sensor[0][0] = g_sensor_on[0] - g_sensor_off[0];
	g_sensor[1][0] = g_sensor_on[1] - g_sensor_off[1];
	g_sensor[2][0] = g_sensor_on[2] - g_sensor_off[2];
	g_sensor[3][0] = g_sensor_on[3] - g_sensor_off[3];
	g_sensor[4][0] = g_sensor_on[4] - g_sensor_off[4];
	for (j = 0; j <= 4; j++) {
		g_sensor_diff[j]=g_sensor[j][0]-g_sensor[j][11];
		g_sensor_mean[j] = (g_sensor[j][0] + g_sensor[j][1] + g_sensor[j][2]) / 3;
	}


//	}

}

/*******************************************************************/
/*	センサーの線形補間用データの測定			(sensor_line)	*/
/*******************************************************************/
/*	センサーの線形補間用データの測定して出力する．						*/
/*******************************************************************/
void sensor_line(void){
	float L_displacement[19],R_displacement[19];
	int L_sensor[19],R_sensor[19];

	for(int count=0;count<19;count++){
	while (g_sensor[2][0] <= SENSOR_FINGER_2) {
					HAL_Delay(1);
				}
	HAL_Delay(100);
	while (g_sensor[2][0] <= SENSOR_FINGER_2) {
						HAL_Delay(1);
					}
	HAL_Delay(500);
	printf("SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d,SEN5=%d\n", g_sensor[0][0],
											g_sensor[1][0], g_sensor[2][0], g_sensor[3][0], g_sensor[4][0]);
	L_displacement[count]=count*5+40;
	R_displacement[18-count]=130-count*5;
	L_sensor[count]=g_sensor[4][0];
	R_sensor[18-count]=g_sensor[0][0];
	pl_yellow_LED_count(count);
	pl_play_oneSound(count);
	}
	while (g_sensor[0][0] <= SENSOR_FINGER_0 || g_sensor[2][0] <= SENSOR_FINGER_2 || g_sensor[3][0] <= SENSOR_FINGER_3) {
							HAL_Delay(1);
						}


	printf("L_SEN,L_displacement,R_SEN,R_displacement\n");
	for(int count=0;count<19;count++){
	printf("%d,%f,%d,%f\n",L_sensor[count],L_displacement[count], R_sensor[count], R_displacement[count]);
	}
}
