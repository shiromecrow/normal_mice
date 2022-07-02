/*
 * maze_strategy.c
 *
 *  Created on: Jul 1, 2022
 *      Author: sf199
 */


#include "maze_strategy.h"
#include "Control_motor.h"
#include "Control_sensor.h"
#include "PL_timer.h"
#include "maze_Turning.h"
#include "PL_motor.h"
#include "define.h"
#include "maze_wall.h"




//extern char highspeed_mode;
//extern int safe;
//extern int mode_safty;
//extern char slant_direction;
//extern char slant_count;
//

//構造体にする
int x;
int y;
int direction;
_Bool front_wall;
_Bool right_wall;
_Bool left_wall;






//void maze_clean(void) {

//	x = 0;
//	y = 0;
//	direction = 1;

//}




//void record_in(void) {
//	t = 0;
//	while (t <= 14) {
//		record.row[t] = row[t];
//		record.column[t] = column[t];
//		t++;
//	}
//	t = 0;
//	while (t <= 14) {
//		record.row_look[t] = row_look[t];
//		record.column_look[t] = column_look[t];
//		t++;
//	}
//	t = 0;
//	writeFlash(start_address, (uint16_t*) record.row, sizeof(record.row), ON);
//	writeFlash(start_address + sizeof(record.row), (uint16_t*) record.column,
//			sizeof(record.column), OFF);
//	writeFlash(start_address + 2 * sizeof(record.row),
//			(uint16_t*) record.row_look, sizeof(record.row_look),
//			OFF);
//	writeFlash(start_address + 3 * sizeof(record.row),
//			(uint16_t*) record.column_look, sizeof(record.column_look),
//			OFF);
//}


//void record_out(void) {
//	loadFlash(start_address, (uint16_t*) record.row, sizeof(record.row));
//	loadFlash(start_address + sizeof(record.row), (uint16_t*) record.column,
//			sizeof(record.column));
//	loadFlash(start_address + 2 * sizeof(record.row),
//			(uint16_t*) record.row_look, sizeof(record.row_look));
//	loadFlash(start_address + 3 * sizeof(record.row),
//			(uint16_t*) record.column_look, sizeof(record.column_look));
//
//	t = 0;
//	while (t <= 14) {
//		row[t] = record.row[t];
//		column[t] = record.column[t];
//		t++;
//	}
//	t = 0;
//	while (t <= 14) {
//		row_look[t] = record.row_look[t];
//		column_look[t] = record.column_look[t];
//		t++;
//	}
//
//	t = 0;
//
//}



void AdatiWayReturn(float input_StraightVelocity, float input_TurningVelocity, float input_StraightAcceleration,
		float input_TurningAcceleration) {

	unsigned short front_count, right_count, back_count, left_count;
	float v_e,v_ea;
//初期化
	x=0;
	y=0;
	direction=1;
//	maze_mode = 1;

	MOTOR_MODE mode;
	mode.WallControlMode=1;
	mode.WallControlStatus=0;
	mode.WallCutMode=0;
	mode.calMazeMode=0;
	pl_motor_standby(1);
	HAL_Delay(500);

	front_wall=((int)((float)(g_sensor_mean[0]+g_sensor_mean[3])/2) >= F_PRESENCE);
	right_wall=(g_sensor_mean[2] >= R_PRESENCE);
	left_wall=(g_sensor_mean[1] >= L_PRESENCE);

	maze_maker();

	HAL_Delay(100);

	pl_motor_start();
	v_e=straight_table(90+BACK_TO_CENTER, 120,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);

	while (1) {

		update_coordinate();

		front_wall=((int)((float)(g_sensor_mean[0]+g_sensor_mean[3])/2) >= F_PRESENCE);
		right_wall=(g_sensor_mean[2] >= R_PRESENCE);
		left_wall=(g_sensor_mean[1] >= L_PRESENCE);
		mode.WallControlMode=1;
		mode.calMazeMode=1;
		mode.WallCutMode=0;
		v_e=straight_table(MAZE_OFFSET, v_e,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);

		search_AroundWalkCount(&front_count,&right_count,&back_count,&left_count);

		if (x == 0 && y == 0) {
			break;
		}
		if((x == GOAL_X || x == GOAL_X+1) && (y == GOAL_Y || y == GOAL_Y+1)){
			while (front_wall) {
				//直進
				mode.WallControlMode=1;
				mode.calMazeMode=0;
				mode.WallCutMode=0;
				v_e=straight_table(180-MAZE_OFFSET, v_e,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);


				update_coordinate();

				front_wall=((int)((float)(g_sensor_mean[0]+g_sensor_mean[3])/2) >= F_PRESENCE);
				right_wall=(g_sensor_mean[2] >= R_PRESENCE);
				left_wall=(g_sensor_mean[1] >= L_PRESENCE);

				mode.WallControlMode=1;
				mode.calMazeMode=1;
				mode.WallCutMode=0;
				v_e=straight_table(MAZE_OFFSET, v_e,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);

				search_AroundWalkCount(&front_count,&right_count,&back_count,&left_count);

			}
			mode.WallControlMode=0;
			mode.calMazeMode=0;
			mode.WallCutMode=0;
			v_e=straight_table(90-MAZE_OFFSET, v_e,100,input_StraightVelocity,input_StraightAcceleration, mode);
			pl_motor_stop();
			wait_ms(300);
			pl_motor_start();
			v_ea=turning_table(180, 120,120,input_TurningVelocity,input_TurningAcceleration);
			pl_motor_stop();
			wait_ms(300);
			pl_motor_start();
			v_e=straight_table(-90, -v_e,-100,-200,input_StraightAcceleration, mode);
			pl_motor_stop();
			wait_ms(600);

			direction = direction + 2;

			if (direction == 5) {
				direction = 1;
			}
			if (direction == 6) {
				direction = 2;
			}
			if (direction == 0) {
				direction = 4;
			}
			if (direction == -1) {
				direction = 3;
			}
			break;
		}



			if (front_wall) {
				front_count = MAX_WALKCOUNT;
			}
			if (right_wall) {
				right_count = MAX_WALKCOUNT;
			}
			if (left_wall) {
				left_count = MAX_WALKCOUNT;
			}
// 移動の優先順位 ： 前→右→左→後
			if (front_count==MAX_WALKCOUNT && right_count==MAX_WALKCOUNT && left_count==MAX_WALKCOUNT && back_count==MAX_WALKCOUNT){
				break;
			}

			if (front_count <= right_count && front_count <= left_count
					&& front_count <= back_count){
				//直進
				mode.WallControlMode=1;
				mode.calMazeMode=0;
				mode.WallCutMode=0;
				v_e=straight_table(180-MAZE_OFFSET, v_e,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);

			}
			if(right_count < front_count && right_count <= left_count
					&& right_count <= back_count){
				//右旋回
				mode.WallControlMode=0;
				mode.calMazeMode=0;
				mode.WallCutMode=1;
				slalomR(speed500_exploration.slalom_R, OFF,EXPLORATION);
				direction++;

			}
			if(left_count < front_count && left_count < right_count
					&& left_count <= back_count){
				mode.WallControlMode=0;
				mode.calMazeMode=0;
				mode.WallCutMode=1;
				slalomL(speed500_exploration.slalom_L, OFF,EXPLORATION);
				direction--;
			}
			if(back_count < front_count && back_count < right_count
					&& back_count < left_count){

				if (front_wall){
					mode.WallControlMode=0;
					mode.calMazeMode=0;
					mode.WallCutMode=0;
					v_e=straight_table(90-MAZE_OFFSET, v_e,100,input_StraightVelocity,input_StraightAcceleration, mode);
					pl_motor_stop();
					wait_ms(300);
					pl_motor_start();
					v_ea=turning_table(180, 120,120,input_TurningVelocity,input_TurningAcceleration);
					pl_motor_stop();
					wait_ms(300);
					pl_motor_start();
					v_e=straight_table(-90, -v_e,-100,-200,input_StraightAcceleration, mode);
					pl_motor_stop();
					wait_ms(600);
					mode.WallControlMode=1;
					pl_motor_start();
					v_e=straight_table(90+BACK_TO_CENTER, 120,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
					direction = direction + 2;
				}else{
					mode.WallControlMode=0;
					mode.calMazeMode=0;
					mode.WallCutMode=0;
					pl_motor_start();
					v_e=straight_table(90-MAZE_OFFSET, v_e,100,input_StraightVelocity,input_StraightAcceleration, mode);
					pl_motor_stop();
					wait_ms(300);
					pl_motor_start();
					v_ea=turning_table(180, 120,120,input_TurningVelocity,input_TurningAcceleration);
					pl_motor_stop();
					wait_ms(300);
					pl_motor_start();
					v_e=straight_table(-BACK_TO_CENTER, -v_e,-100,-200,input_StraightAcceleration, mode);
					pl_motor_stop();
					wait_ms(600);
					mode.WallControlMode=1;
					pl_motor_start();
					v_e=straight_table(90+BACK_TO_CENTER, 120,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
					direction = direction + 2;

				}

			}

		if (direction == 5) {
			direction = 1;
		}
		if (direction == 6) {
			direction = 2;
		}
		if (direction == 0) {
			direction = 4;
		}
		if (direction == -1) {
			direction = 3;
		}

	}

//	record_in();
	pl_motor_start();
	v_e=straight_table(90+BACK_TO_CENTER, 120,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);

	while (1) {

		update_coordinate();

		front_wall=((int)((float)(g_sensor_mean[0]+g_sensor_mean[3])/2) >= F_PRESENCE);
		right_wall=(g_sensor_mean[2] >= R_PRESENCE);
		left_wall=(g_sensor_mean[1] >= L_PRESENCE);
		mode.WallControlMode=1;
		mode.calMazeMode=2;
		mode.WallCutMode=0;
		v_e=straight_table(MAZE_OFFSET, v_e,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);

		search_AroundWalkCount(&front_count,&right_count,&back_count,&left_count);

		if (x == 0 && y == 0) { ///////goal************************
			mode.WallControlMode=0;
			mode.calMazeMode=0;
			mode.WallCutMode=0;
			v_e=straight_table(90-MAZE_OFFSET, v_e,100,input_StraightVelocity,input_StraightAcceleration, mode);
			pl_motor_stop();
			wait_ms(300);
			pl_motor_start();
			v_ea=turning_table(180, 120,120,input_TurningVelocity,input_TurningAcceleration);
			pl_motor_stop();
			wait_ms(300);

			maze_display();
			direction = direction + 2;

			if (direction == 5) {
				direction = 1;
			}
			if (direction == 6) {
				direction = 2;
			}
			if (direction == 0) {
				direction = 4;
			}
			if (direction == -1) {
				direction = 3;
			}

			break;
		}


		if (front_wall) {
			front_count = MAX_WALKCOUNT;
		}
		if (right_wall) {
			right_count = MAX_WALKCOUNT;
		}
		if (left_wall) {
			left_count = MAX_WALKCOUNT;
		}
// 移動の優先順位 ： 前→右→左→後
		if (front_count==MAX_WALKCOUNT && right_count==MAX_WALKCOUNT && left_count==MAX_WALKCOUNT && back_count==MAX_WALKCOUNT){
			break;
		}

		if (front_count <= right_count && front_count <= left_count
				&& front_count <= back_count){
			//直進
			mode.WallControlMode=1;
			mode.calMazeMode=0;
			mode.WallCutMode=0;
			v_e=straight_table(180-MAZE_OFFSET, v_e,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);

		}
		if(right_count < front_count && right_count <= left_count
				&& right_count <= back_count){
			//右旋回
			mode.WallControlMode=0;
			mode.calMazeMode=0;
			mode.WallCutMode=1;
			slalomR(speed500_exploration.slalom_R, OFF,EXPLORATION);
			direction++;

		}
		if(left_count < front_count && left_count < right_count
				&& left_count <= back_count){
			mode.WallControlMode=0;
			mode.calMazeMode=0;
			mode.WallCutMode=1;
			slalomL(speed500_exploration.slalom_L, OFF,EXPLORATION);
			direction--;
		}
		if(back_count < front_count && back_count < right_count
				&& back_count < left_count){

			if (front_wall){
				mode.WallControlMode=0;
				mode.calMazeMode=0;
				mode.WallCutMode=0;
				v_e=straight_table(90-MAZE_OFFSET, v_e,100,input_StraightVelocity,input_StraightAcceleration, mode);
				pl_motor_stop();
				wait_ms(300);
				pl_motor_start();
				v_ea=turning_table(180, 120,120,input_TurningVelocity,input_TurningAcceleration);
				pl_motor_stop();
				wait_ms(300);
				pl_motor_start();
				v_e=straight_table(-90, -v_e,-100,-200,input_StraightAcceleration, mode);
				pl_motor_stop();
				wait_ms(600);
				mode.WallControlMode=1;
				pl_motor_start();
				v_e=straight_table(90+BACK_TO_CENTER, 120,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
				direction = direction + 2;
			}else{
				mode.WallControlMode=0;
				mode.calMazeMode=0;
				mode.WallCutMode=0;
				pl_motor_start();
				v_e=straight_table(90-MAZE_OFFSET, v_e,100,input_StraightVelocity,input_StraightAcceleration, mode);
				pl_motor_stop();
				wait_ms(300);
				pl_motor_start();
				v_ea=turning_table(180, 120,120,input_TurningVelocity,input_TurningAcceleration);
				pl_motor_stop();
				wait_ms(300);
				pl_motor_start();
				v_e=straight_table(-BACK_TO_CENTER, -v_e,-100,-200,input_StraightAcceleration, mode);
				pl_motor_stop();
				wait_ms(600);
				mode.WallControlMode=1;
				pl_motor_start();
				v_e=straight_table(90+BACK_TO_CENTER, 120,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
				direction = direction + 2;

			}

		}


		if (direction == 5) {
			direction = 1;
		}
		if (direction == 6) {
			direction = 2;
		}
		if (direction == 0) {
			direction = 4;
		}
		if (direction == -1) {
			direction = 3;
		}

//だ出ツール
//		if (red_switch == 0) {
//			while (green_switch == 1) {
//			}
//			while (green_switch == 0) {
//			}

	}
	pl_motor_stop();
	wait_ms(500);
	pl_motor_standby(0);
	maze_display();


}

void update_coordinate(void){
// int direction,int *x_coordinate,int *y_coordinate
	switch (direction) {
	case 1://北
		y = y + 1;
		break;
	case 2://東
		x = x + 1;
		break;
	case 3://南
		y = y - 1;
		break;
	case 4://西
		x = x - 1;
		break;
	}

}





