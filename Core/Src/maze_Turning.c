/*
 * maze_Turning.c
 *
 *  Created on: Jul 2, 2022
 *      Author: sf199
 */

#include "maze_Turning.h"
#include "Control_motor.h"
#include "PL_motor.h"
#include "define.h"

parameter_speed speed500_exploration;
parameter_speed speed700_shortest;
parameter_speed speed900_shortest;
parameter_speed speed1000_shortest;




void test_motor_start(MOTOR_MODE *wallmode){
	wallmode->WallControlMode=1;
	wallmode->WallControlStatus=0;
	wallmode->WallCutMode=0;
	wallmode->calMazeMode=0;
	pl_motor_standby(1);
	HAL_Delay(500);
	pl_motor_start();

}

void test_motor_stop(void){
	pl_motor_stop();
	HAL_Delay(500);
	pl_motor_standby(0);
}

void slalomR(parameter turnpara,char test_mode,char shortest_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 270, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=0;
		if(shortest_mode==0){
			straight_table(MAZE_OFFSET+turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		}else{
			straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		}

		slalom_table(turnpara.g_speed,90, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(90 + turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	} else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=0;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,90, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
				straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}

void slalomL(parameter turnpara,char test_mode,char shortest_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 270, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=0;
		if(shortest_mode==0){
			straight_table(MAZE_OFFSET+turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		}else{
			straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		}

		slalom_table(turnpara.g_speed,-90, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(90 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	} else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=0;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,-90, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
				straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}



void turn90R(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 180, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed / 2 / 90,wallmode);
		wallmode.WallCutMode=1;

		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,90, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	} else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=1;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,90, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}

void turn90L(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 180, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=1;

		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,-90, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	} else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=1;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,-90, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}


void turn180R(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 180, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=1;

		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,180, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	} else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=1;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,180, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}

void turn180L(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 180, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=1;

		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,-180, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	} else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=1;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,-180, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}



void turn45inR(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 180, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=1;

		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,45, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	} else if(test_mode == 2){
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 180, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=1;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,45, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
	}
	else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=1;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,45, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}

void turn45inL(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 180, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=1;

		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,-45, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	} else if(test_mode == 2){
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 180, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=1;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,-45, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
	}
	else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=1;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,-45, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}



void turn135inR(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 180, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=1;

		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,135, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	} else if(test_mode == 2){
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 180, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=1;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,135, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
	}
	else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=1;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,135, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, 0, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}

void turn135inL(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 180, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=1;

		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,-135, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	} else if(test_mode == 2){
//		highspeed_mode = 1;
//		record_mode = 1;
		test_motor_start(&wallmode);
		straight_table(BACK_TO_CENTER + 180, 100, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		wallmode.WallCutMode=1;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,-135, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
	}
	else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=1;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,-135, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}



void turn45outR(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=2;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,45, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	}else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=2;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,45, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}


void turn45outL(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=2;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,-45, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	}else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=2;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,-45, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}

void turn135outR(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=2;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,135, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	}else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=2;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,135, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}


void turn135outL(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=2;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,-135, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	}else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=2;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,-135, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}
}

void V90R(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=2;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,90, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	}else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=2;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,90, 0, 0, turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}

}

void V90L(parameter turnpara, char test_mode) {
	MOTOR_MODE wallmode;
	if (test_mode == 1) {
//		highspeed_mode = 1;
//		record_mode = 1;
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=2;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
									turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

		slalom_table(turnpara.g_speed,-90, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		straight_table(180 * 1.4142 + turnpara.e_ofset, turnpara.g_speed, 100, turnpara.g_speed,
				turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

//		record_mode = 0;
		test_motor_stop();
//      highspeed_mode = 0;
	}else {
		wallmode.WallControlMode=0;
		wallmode.WallControlStatus=0;
		wallmode.WallCutMode=2;
		wallmode.calMazeMode=0;
		straight_table(turnpara.f_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
											turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);
		slalom_table(turnpara.g_speed,-90, 0, 0, -turnpara.t_speed, turnpara.t_acc);
		wallmode.WallControlMode=0;
		wallmode.WallCutMode=0;
		straight_table(turnpara.e_ofset, turnpara.g_speed, turnpara.g_speed, turnpara.g_speed,
						turnpara.g_speed * turnpara.g_speed  / 2 / 90,wallmode);

	}

}


void testturning(parameter_speed Howspeed,int turnmode,char shortest_mode){
	//0=slalomR,1=slalomL,2=90R,3=90L,4=180R,5=180L,6=in45R,7=in45L,8=in135R,9=in135L
	//10=out45R,11=out45L,12=out135R,13=out135L,14=V90R,15=V90L

	if(turnmode==0){slalomR(Howspeed.slalom_R,ON,shortest_mode);}
	if(turnmode==1){slalomL(Howspeed.slalom_L,ON,shortest_mode);}
	if(turnmode==2){turn90R(Howspeed.turn90_R,ON);}
	if(turnmode==3){turn90L(Howspeed.turn90_L,ON);}
	if(turnmode==4){turn180R(Howspeed.turn180_R,ON);}
	if(turnmode==5){turn180L(Howspeed.turn180_L,ON);}
	if(turnmode==6){turn45inR(Howspeed.turn45in_R,ON);}
	if(turnmode==7){turn45inL(Howspeed.turn45in_L,ON);}
	if(turnmode==8){turn135inR(Howspeed.turn135in_R,ON);}
	if(turnmode==9){turn135inL(Howspeed.turn135in_L,ON);}
	if(turnmode==10){turn45inL(Howspeed.turn45in_L, CONNECT);turn45outR(Howspeed.turn45out_R,ON);}
	if(turnmode==11){turn45inR(Howspeed.turn45in_R, CONNECT);turn45outL(Howspeed.turn45out_L,ON);}
	if(turnmode==12){turn135inL(Howspeed.turn135in_L, CONNECT);turn135outR(Howspeed.turn135out_R,ON);}
	if(turnmode==13){turn135inR(Howspeed.turn135in_R, CONNECT);turn135outL(Howspeed.turn135out_L,ON);}
	if(turnmode==14){turn45inL(Howspeed.turn45in_L, CONNECT);V90R(Howspeed.V90_R,ON);}
	if(turnmode==15){turn45inR(Howspeed.turn45in_R, CONNECT);V90L(Howspeed.V90_L,ON);}

	HAL_Delay(500);

}
