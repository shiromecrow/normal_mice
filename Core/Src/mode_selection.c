/*
 * mode_selection.c
 *
 *  Created on: Jun 30, 2022
 *      Author: sf199
 */


#include "mode_selection.h"
#include "Control_sensor.h"
#include "Control_motor.h"
#include "PL_switch.h"
#include "PL_led.h"
#include "PL_sensor.h"
#include "PL_lcd.h"
#include "PL_timer.h"
#include "PL_speaker.h"
#include "define.h"
#include "stdio.h"
#include "math.h"




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
		now_mode++;
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
		now_mode--;
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

	while (g_sensor_on[3]<=SENSOR_FINGER_3){
		wait_ms(1);
	}

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
		case 9://PLname
		break;
		case 10://PLname
		break;
	}

}

void mode_Running(unsigned char now_mode2){
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
		case 9://PLname
		break;
		case 10://PLname
		break;
	}

}


void mode_Tuning(unsigned char now_mode2){
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
		case 9://PLname
		break;
		case 10://PLname
		break;
	}

}
