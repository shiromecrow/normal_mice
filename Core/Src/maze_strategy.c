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

#include "stdio.h"


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
			while (front_wall==0) {
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



void ShortestWay(float input_StraightVelocity, float input_StraightAcceleration,parameter_speed input_turn,char slant_mode){
	int pass[255];
	unsigned char slant_count;
	int slant_direction;
	_Bool north_wall,east_wall,south_wall,west_wall;
	unsigned short front_count, right_count, back_count, left_count;
	unsigned short pass_count = 0;
	int t=0;
	x = 0;
	y = 0;
	direction = 1;
	slant_direction = -2;

	//highspeed_mode = 1;
	while (t <= 255) {
		pass[t] = 0;
		t++;
	}
	t = 0;
	while (t <= 14) {
		record.row[t] = wall.row[t];
		record.column[t] = wall.column[t];
		t++;
	}
	t = 0;
	while (t <= 14) {
		record.row_look[t] = wall.row_look[t];
		record.column_look[t] = wall.column_look[t];
		t++;
	}
	t = 0;
	while (t <= 14) {
		wall.row[t] = wall.row[t] | ~wall.row_look[t];
		wall.column[t] = wall.column[t] | ~wall.column_look[t];
		t++;
	}

	pass_count = 0;
//	maze_makerhosuu(direction, x, y);
//	maze_makerST(stmass);//あとで修正
	maze_maker0(0,1);
	maze_display();

	pass[0] = 1;

	while (1) {
//		if (mode_safty == 1) {
//
//			break;
//		}
		update_coordinate();
		search_AroundWalkCount(&front_count,&right_count,&back_count,&left_count);

		if((x == GOAL_X || x == GOAL_X+1) && (y == GOAL_Y || y == GOAL_Y+1)){
			if (pass[pass_count] >= 0) {
			} else {
				pass_count++;
			}
			pass[pass_count] = pass[pass_count] + 1;

			break;
		}

		if (y <= 14) {
			north_wall = wall.column[y] & (1 << x);
		} else {
			north_wall = 1;
		}

		if (y >= 1) {
			south_wall = wall.column[y - 1] & (1 << x);
		} else {
			south_wall = 1;
		}

		if (x <= 14) {
			east_wall = wall.row[x] & (1 << y);
		} else {
			east_wall = 1;
		}

		if (x >= 1) {
			west_wall = wall.row[x - 1] & (1 << y);
		} else {
			west_wall = 1;
		}

		switch (direction) {
		case 1:
			front_wall = north_wall;
			left_wall = west_wall;
			right_wall = east_wall;
			break;
		case 2:
			front_wall = east_wall;
			left_wall = north_wall;
			right_wall = south_wall;
			break;
		case 3:
			front_wall = south_wall;
			left_wall = east_wall;
			right_wall = west_wall;

			break;
		case 4:
			front_wall = west_wall;
			left_wall = south_wall;
			right_wall = north_wall;
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

		if (front_count==MAX_WALKCOUNT && right_count==MAX_WALKCOUNT && left_count==MAX_WALKCOUNT && back_count==MAX_WALKCOUNT){
			break;
		}

		if (front_count <= right_count && front_count <= left_count){
			//直進
			if (pass[pass_count] >= 0) {
			} else {
				pass_count++;
			}
			pass[pass_count] = pass[pass_count] + 2;
		}
		if(right_count < front_count && right_count <= left_count){
			//右旋回
			pass_count++;
			pass[pass_count] = -2;
			direction++;

		}
		if(left_count < front_count && left_count < right_count){
			//左旋回
			pass_count++;
			pass[pass_count] = -3;
			direction--;
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
	pass_count = 1;

	while (1) {		//パス圧縮
//		if (mode_safty == 1) {
//
//			break;
//		}
		if (pass[pass_count] == 0) {
			break;
		}

		if (pass[pass_count] == -2 && pass[pass_count - 1] >= 1	//右90度大回りの条件
		&& pass[pass_count + 1] >= 1) {
			pass[pass_count - 1] = pass[pass_count - 1] - 1;	//前90直進の削除
			pass[pass_count + 1] = pass[pass_count + 1] - 1;	//後90直進の削除
			pass[pass_count] = -4;		//右90度大回り

		}
		if (pass[pass_count] == -3 && pass[pass_count - 1] >= 1	//左90度大回りの条件
		&& pass[pass_count + 1] >= 1) {
			pass[pass_count - 1] = pass[pass_count - 1] - 1;	//前90直進の削除
			pass[pass_count + 1] = pass[pass_count + 1] - 1;	//後90直進の削除
			pass[pass_count] = -5;		//左90度大回り

		}
		if (pass[pass_count - 1] >= 1 && pass[pass_count] == -2
				&& pass[pass_count + 1] == -2 && pass[pass_count + 2] >= 1) {//右180度大回りの条件
			pass[pass_count - 1] = pass[pass_count - 1] - 1;
			pass[pass_count] = -6;
			pass[pass_count + 1] = -1;
			pass[pass_count + 2] = pass[pass_count + 2] - 1;

		}
		if (pass[pass_count - 1] >= 1 && pass[pass_count] == -3
				&& pass[pass_count + 1] == -3 && pass[pass_count + 2] >= 1) {//左180度大回りの条件
			pass[pass_count - 1] = pass[pass_count - 1] - 1;
			pass[pass_count] = -7;
			pass[pass_count + 1] = -1;
			pass[pass_count + 2] = pass[pass_count + 2] - 1;
		}
		if (pass[pass_count] == -2 && pass[pass_count - 1] == -3	//左90度大回りの条件

				) {
		}
		if (pass[pass_count - 1] == 0) {
			pass[pass_count - 1] = -1;		//passが0になってしまったときの対策
		}

		pass_count++;
	}

	pass_count = 1;
	if (slant_mode == 1) {
		while (1) {		//斜め入出の圧縮
			if (pass[pass_count] == 0) {
				break;
			}

			if (pass[pass_count - 1] >= 1) {
				if (pass[pass_count] == -2 || pass[pass_count] == -3) {
//***************************************************************************************入りのモーションstart
					if (pass[pass_count] == -2 && pass[pass_count + 1] == -3) {
						pass[pass_count - 1] = pass[pass_count - 1] - 1;
						if (pass[pass_count - 1] == 0) {
							pass[pass_count - 1] = -1;	//passが0になってしまったときの対策
						}
						pass[pass_count] = -8;		//右45
					}
					if (pass[pass_count] == -3 && pass[pass_count + 1] == -2) {
						pass[pass_count - 1] = pass[pass_count - 1] - 1;
						if (pass[pass_count - 1] == 0) {
							pass[pass_count - 1] = -1;	//passが0になってしまったときの対策
						}
						pass[pass_count] = -9;		//左45
					}
					if (pass[pass_count] == -2 && pass[pass_count + 1] == -2) {
						pass[pass_count - 1] = pass[pass_count - 1] - 1;
						if (pass[pass_count - 1] == 0) {
							pass[pass_count - 1] = -1;	//passが0になってしまったときの対策
						}
						pass[pass_count] = -10;		//右135
						pass[pass_count + 1] = -1;
					}
					if (pass[pass_count] == -3 && pass[pass_count + 1] == -3) {
						pass[pass_count - 1] = pass[pass_count - 1] - 1;
						if (pass[pass_count - 1] == 0) {
							pass[pass_count - 1] = -1;	//passが0になってしまったときの対策
						}
						pass[pass_count] = -11;		//左135
						pass[pass_count + 1] = -1;
					}
//***************************************************************************************入りのモーションend

//***************************************************************************************途中のモーションstart
					while (pass[pass_count] <= -1) {
						pass_count++;
					}
//***************************************************************************************途中のモーションend

//***************************************************************************************出のモーションstart
					if (pass[pass_count - 1] == -2) {
						if (pass[pass_count - 2] == -2) {
							pass[pass_count] = pass[pass_count] - 1;
							if (pass[pass_count] == 0) {
								pass[pass_count] = -1;	//passが0になってしまったときの対策
							}
							pass[pass_count - 1] = -14;		//右135
							pass[pass_count - 2] = -1;
						} else {
							pass[pass_count] = pass[pass_count] - 1;
							if (pass[pass_count] == 0) {
								pass[pass_count] = -1;	//passが0になってしまったときの対策
							}
							pass[pass_count - 1] = -12;		//右45
						}

					}
					if (pass[pass_count - 1] == -3) {
						if (pass[pass_count - 2] == -3) {
							pass[pass_count] = pass[pass_count] - 1;
							if (pass[pass_count] == 0) {
								pass[pass_count] = -1;	//passが0になってしまったときの対策
							}
							pass[pass_count - 1] = -15;		//左135
							pass[pass_count - 2] = -1;
						} else {
							pass[pass_count] = pass[pass_count] - 1;
							if (pass[pass_count] == 0) {
								pass[pass_count] = -1;	//passが0になってしまったときの対策
							}
							pass[pass_count - 1] = -13;		//左45
						}

					}
//***************************************************************************************出のモーションend
				}
			}

			pass_count++;
		}

		pass_count = 1;
		while (1) {		//斜の圧縮
			if (pass[pass_count] == 0) {
				break;
			}

			if (pass[pass_count] == -8 || pass[pass_count] == -9
					|| pass[pass_count] == -10 || pass[pass_count] == -11) {
				if (pass[pass_count] == -8 || pass[pass_count] == -10) {
					slant_direction = -3;
				}
				if (pass[pass_count] == -9 || pass[pass_count] == -11) {
					slant_direction = -2;
				}
				pass_count++;
				if (pass[pass_count] == -1) {		//135ターンようのー１を進めるため
					pass_count++;
				}
				if (pass[pass_count] == -1) {		//135ターンようのー１を進めるため
					pass_count++;
				}
				if (pass[pass_count] >= -3) {
					slant_count = pass_count;
					pass[slant_count] = 51;
					pass_count++;
				}

				//***************************************************************************************途中のモーションstart
				while (pass[pass_count] >= -3) {
					if (pass[pass_count] == -1) {		//135ターンようのー１を進めるため
						pass_count++;
					}
					if (pass[pass_count] == -12 || pass[pass_count] == -13
							|| pass[pass_count] == -14
							|| pass[pass_count] == -15) {
						break;
					}
					if (pass[pass_count] == slant_direction) {
						pass[slant_count] = pass[slant_count] - 1;
						slant_count = pass_count;
						if (slant_direction == -2) {
							pass[pass_count] = -16;
						}
						if (slant_direction == -3) {
							pass[pass_count] = -17;
						}

					} else {
						if (pass[slant_count] >= 50) {
							pass[pass_count] = -1;
						} else {
							slant_count = pass_count;
							pass[slant_count] = 50;
						}
						pass[slant_count] = pass[slant_count] + 1;
						if (slant_direction == -2) {
							slant_direction = -3;
						} else {
							slant_direction = -2;
						}

					}

					pass_count++;
				}
				//***************************************************************************************途中のモーションend

			}

			//		if(){}

			pass_count++;
		}
	}
	t = 0;
	while (pass[t] != 0) {
		printf("pass_count %d pass %d\n", t, pass[t]);
		t++;
	}

// 最短走行の実行
	MOTOR_MODE mode;
	float v_e;
	mode.WallControlMode=1;
	mode.WallControlStatus=0;
	mode.WallCutMode=0;
	mode.calMazeMode=0;
	pl_motor_standby(1);
	HAL_Delay(500);
	pl_motor_start();

//	maze_mode = 1;
//	highspeed_mode = 1;
//	Avespeed = 1400;
//	wall_control = 0;
	pass_count = 0;

	if (pass[pass_count] == -2 || pass[pass_count] == -3) {
		//straight_table(39.5, 0, 800, 800, 26000);
		v_e=straight_table(BACK_TO_CENTER, 120,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
	} else {
		v_e=straight_table(BACK_TO_CENTER, 120,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
		//straight_table(39.5, 0, howspeed.turn90_R.g_speed,howspeed.turn90_R.g_speed,howspeed.turn90_R.g_speed * howspeed.turn90_R.g_speed / 39.5);
	}

	while (pass_count <= 255) {

		if (pass[pass_count] == -1) {
			pass_count++;
		}
		if (pass[pass_count] == -2) {
			slalomR(input_turn.slalom_R, OFF,SHORTEST);
			pass_count++;
		}
		if (pass[pass_count] == -3) {
			slalomL(input_turn.slalom_L, OFF,SHORTEST);
			pass_count++;
		}
		if (pass[pass_count] == -4) {
			turn90R(input_turn.turn90_R, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -5) {
			turn90L(input_turn.turn90_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -6) {
			turn180R(input_turn.turn180_R, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -7) {
			turn180L(input_turn.turn180_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -8) { //入り45R
			turn45inR(input_turn.turn45in_R, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -9) { //入り45L
			turn45inL(input_turn.turn45in_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -10) { //入り135R
			turn135inR(input_turn.turn135in_R, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -11) { //入り135L
			turn135inL(input_turn.turn135in_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -12) { //出り45R
			turn45outR(input_turn.turn45out_R, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -13) { //出り45L
			turn45outL(input_turn.turn45out_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -14) { //出り135R
			turn135outR(input_turn.turn135out_R, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -15) { //出り135L
			turn135outL(input_turn.turn135out_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -16) { //V90R
			V90R(input_turn.V90_R, OFF);
			pass_count++;
		}
		if (pass[pass_count] == -17) { //V90L
			V90L(input_turn.V90_L, OFF);
			pass_count++;
		}
		if (pass[pass_count] >= 1) {
			if (pass_count >= 1) {

				if (pass[pass_count - 1] == -2 || pass[pass_count - 1] == -3) {
					//first_v = 800;
				}
			}
			if (pass[pass_count + 1] == -2 || pass[pass_count + 1] == -3) {
				//last_v = 800;
			}
			if (pass[pass_count] >= 50) {
				//wall_control_mode = 2;
				v_e=straight_table((90 * 1.414 * (pass[pass_count] - 50)), v_e,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
				//straight_table((90 * 1.414 * (pass[pass_count] - 50)), first_v,last_v, inspeed, inacc);

			} else {
				//wall_control_mode = 1;
				//straight_table((90 * pass[pass_count]), first_v, last_v,inspeed, inacc);
			}
			pass_count++;
		}

		if (pass[pass_count] == 0) {
			break;
		}

		if (x == 0 && y == 0) {
			break;
		}

	}
	if (x == 0 && y == 0) {
	} else {
//		straight_table(180, (E_speedR + E_speedL) / 2, 0,(E_speedR + E_speedL) / 2, inacc);
		HAL_Delay(700);
		turning_table(180, 0, 0, 400, 5000);
	}
	pl_motor_stop();
	HAL_Delay(500);
	pl_motor_standby(0);



	t = 0;
	while (t <= 14) {
		wall.row[t] = record.row[t];
		wall.column[t] = record.column[t];
		t++;
	}

}



