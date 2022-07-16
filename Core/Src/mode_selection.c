/*
 * mode_selection.c
 *
 *  Created on: Jun 30, 2022
 *      Author: sf199
 */


#include "mode_selection.h"
#include "record.h"
#include "Control_sensor.h"
#include "Control_motor.h"
#include "PL_switch.h"
#include "PL_led.h"
#include "PL_sensor.h"
#include "PL_lcd.h"
#include "PL_timer.h"
#include "PL_speaker.h"
#include "PL_motor.h"
#include "define.h"

#include "stdio.h"
#include "math.h"

#include "maze_wall.h"
#include "maze_Turning.h"
#include "maze_strategy.h"



unsigned char mode_decision(unsigned char select,unsigned char now_mode){

//LCDで現在のモード番号を表示
switch (select){
case 0:
mode_display0(now_mode);
break;
case 1:
mode_display1(now_mode);
break;
}


while (g_sensor_on[0]<=SENSOR_FINGER_0){
	if(read_switch1()==1){
		if(select==0 && now_mode > MAX_MODE0){now_mode=0;}
		else if(select==1 && now_mode > MAX_MODE1){now_mode=0;}
		else{now_mode++;}

		switch (select){
		case 0:
		mode_display0(now_mode);
		break;
		case 1:
		mode_display1(now_mode);
		break;
		}
		pl_play_oneSound(now_mode);
		wait_ms(100);
	}
	if(read_switch2()==1){
		if(select==0 && now_mode == 0){now_mode=MAX_MODE0+1;}
		else if(select==1 && now_mode == 0){now_mode=MAX_MODE1+1;}
		else{now_mode--;}

		switch (select){
		case 0:
		mode_display0(now_mode);
		break;
		case 1:
		mode_display1(now_mode);
		break;
		}
		pl_play_oneSound(now_mode);
		wait_ms(100);
	}


}

while (g_sensor_on[0]>=SENSOR_FINGER_0){
	wait_ms(1);
}
pl_play_Music(8, Zelda_nazo);

return now_mode;
}

void mode_display0(int mode){
	pl_lcd_clear();
	pl_lcd_pos(0, 0);
	switch(mode){
	case 0:
		pl_lcd_puts("test");
	break;
	case 1:
		pl_lcd_puts("run");
	break;
	case 2:
		pl_lcd_puts("tune");
	break;
	case 3:
		pl_lcd_puts("log");
	break;
	case 4:
		pl_lcd_puts("endure");
	break;
	}

	pl_lcd_pos(1, 0);
	pl_lcd_puts("mode");

}


void mode_display1(int mode){
	pl_lcd_clear();
	pl_lcd_pos(0, 0);
	pl_lcd_puts("mode");
	char strBuffer[17] = {0};
	sprintf(strBuffer, "CNT=%04d", mode);
	pl_lcd_pos(1, 0);
	pl_lcd_puts(strBuffer);

}





void mode_execution(unsigned char now_mode1,unsigned char now_mode2){
	pl_lcd_clear();
	pl_lcd_pos(0, 0);
	pl_lcd_puts("mode");
	pl_lcd_pos(1, 0);
	pl_lcd_puts("select");
	while (g_sensor_on[3]<=SENSOR_FINGER_3){
		wait_ms(1);
		if(read_switch1()==1 && read_switch2()==1){
			now_mode1=100;
			break;
		}
	}
	pl_play_Music(8, Zelda_nazo);

switch (now_mode1) {
	case 0://PLテストモード1
		mode_PLtest(now_mode2);
	break;
	case 1://実行モード1
		mode_Running(now_mode2);
	break;
	case 2://調整
		mode_Tuning(now_mode2);
	break;
	case 3://ログ
		mode_Log(now_mode2);
	break;
	case 4://耐久テスト
//		mode_Tuning2(now_mode2);
	break;
	case 100://エラー脱出
		wait_ms(10);
	break;

	}
}

void mode_PLtest(unsigned char now_mode2){
	uint8_t Pin=0;
	uint8_t hello[] = "Hello World\n\r";
	char strBuffer[17] = {0};


	switch (now_mode2) {
		case 0://LED
			while(read_switch1()==0){
			write_LED(1);
			HAL_Delay(500);
			write_LED(0);
			HAL_Delay(500);
			}
		break;
		case 1://SWITCH
			while(read_switch1()==0){
			if (read_switch2()==1 && Pin==0){
				Pin=1;
				HAL_Delay(100);
			}else if(read_switch2()==1 && Pin==1){
				Pin=0;
				HAL_Delay(100);
			}
			write_LED(1);
			}
		break;
		case 2://USART

			while(read_switch1()==0){
			// test USART2
			setbuf(stdout, NULL);
			printf("hello=%s", hello);
			uint8_t hoge = 3;
			float PI=3.14;
			printf("hoge=%d\n", hoge);
			printf("M_PI=%f\n", PI); // @suppress("Float formatting support")
			}
		break;
		case 3://timer
			while(read_switch1()==0){
				write_LED(1);
				wait_ms(500);
				write_LED(0);
				wait_ms(500);
				}
		break;
		case 4://sensor
			// sensor test
			while(read_switch1()==0){
			//HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,sizeof(g_ADCBuffer) / sizeof(uint16_t));
			//printf("BATT=%f\n",g_V_batt);
			printf("SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d\n", g_sensor[0][0],g_sensor[1][0],g_sensor[2][0],g_sensor[3][0]);
			wait_ms(500);
			}
		break;
		case 5://speaker
			pl_test_speaker();
		break;
		case 6://LCD
			while(read_switch1()==0){
			sprintf(strBuffer, "CNT=%04d", Pin);
			Pin++;
			pl_lcd_pos(1, 0);
			pl_lcd_puts(strBuffer);
			}
		break;
		case 7://motor
		    control_test_motor(0);
		break;
		case 8://motor+sensor
			control_test_motor(1);
		break;
		case 9://record
			record_mode=1;
			wait_ms(1000);
			while(read_switch1()==0){
			record_mode=0;
			}
			record_print();
		break;
		case 10://flash
		break;
		case 11://PLname
		break;
		case 12://PLname
		break;
	}

}

void mode_Running(unsigned char now_mode2){

	switch (now_mode2) {
		case 0://迷路情報の可視化
			maze_display();
		break;
		case 1://足立法
			AdatiWayReturn(500, 500, 7000,7000);
		break;
		case 2://足立法(帰りあり)
		break;
		case 3://最短走行(パス圧縮なし)
			ShortestWay(1000,10000,speed600_shortest,0);
		break;
		case 4://最短走行(パス圧縮あり)
		break;
		case 5://最短走行(斜め走行)
		break;
		case 6://Runname
		break;
		case 7://Runname
		break;
	}

}


void mode_Tuning(unsigned char now_mode2){

	pl_motor_standby(1);
	while(read_switch1()==0 || read_switch2()==0){
		wait_ms(1);
		}
	wait_ms(2000);
	switch (now_mode2) {
		case 0://タイヤ径
			control_test_motor2(0,0,10);
		break;
		case 1://トレッド幅
			control_test_motor2(1,0,5);
		break;
		case 2://壁制御
			control_test_motor2(0,1,6);
		break;
		case 3://右スラローム(探索)
			testturning(speed500_exploration,0,0);
		break;
		case 4://左スラローム(探索)
			testturning(speed500_exploration,1,0);
		break;
		case 5://右スラローム
			testturning(speed900_shortest,0,1);
		break;
		case 6://左スラローム
			testturning(speed900_shortest,1,1);
		break;
		case 7://右壁切れ
			testturning(speed900_shortest,2,1);
		break;
		case 8://左壁切れ
			testturning(speed900_shortest,3,1);
		break;
		case 9://右大回り90
			testturning(speed900_shortest,4,1);
		break;
		case 10://左大回り90
			testturning(speed900_shortest,5,1);
		break;
		case 11://右大回り180
		break;
		case 12://左大回り180
		break;
		case 13://右斜め45
		break;
		case 14://左斜め45
		break;
		case 15://右斜め135
		break;
		case 16://左斜め135
		break;
	}

}

void mode_Log(unsigned char now_mode2){

	pl_motor_standby(1);

	switch (now_mode2) {
		case 0://タイヤ径
			record_mode=1;
			control_test_motor2(0,1,5);
			record_mode=0;
			while(read_switch1()==0 || read_switch2()==0){
				wait_ms(1);
				}
			record_print();
		break;
		case 1://トレッド幅
		break;
		case 2://壁制御
		break;
		case 3://右スラローム(探索)
			testturning(speed500_exploration,0,0);
		break;
		case 4://左スラローム(探索)
			testturning(speed500_exploration,1,0);
		break;
		case 5://右スラローム
			control_test_motor2(2,1,0);
		break;
		case 6://左スラローム
		break;
		case 7://右壁切れ
		break;
		case 8://左壁切れ
		break;
		case 9://右大回り90
		break;
		case 10://左大回り90
		break;
		case 11://右大回り180
		break;
		case 12://左大回り180
		break;
		case 13://右斜め45
		break;
		case 14://左斜め45
		break;
		case 15://右斜め135
		break;
		case 16://左斜め135
		break;
	}

}
