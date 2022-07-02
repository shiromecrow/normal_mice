/*
 * Control_motor.c
 *
 *  Created on: Jun 23, 2022
 *      Author: sf199
 */


#include "Control_motor.h"
#include "PL_motor.h"
#include "define.h"
#include "stdio.h"
#include "math.h"
#include "PID_wall.h"


TARGET g_TargetStraight;
TARGET g_TargetTurning;

TRAPEZOID g_TrapezoidStraight;
TRAPEZOID g_TrapezoidTurning;



char modeacc;
volatile char g_acc_flag;

void control_test_motor(uint8_t WallMode)
{
	MOTOR_MODE mode;
//	mode.WallControlMode=0;
	mode.WallControlMode=WallMode;
	mode.WallControlStatus=0;
	mode.WallCutMode=0;
	mode.calMazeMode=0;
	pl_motor_standby(1);
	pl_motor_start();

//	float v_e=straight_table(-180, -100, -100, -500, 7000, mode);
	float v_e=straight_table(540, 200, 200, 600, 7000, mode);

//	float v_e=straight_table(180, 150, 600, 600, 7000);
//	slalom_table(v_e,90, 0, 0, 400, 7000);
//	v_e=straight_table(180, v_e, 150, 600, 7000);
	pl_motor_stop();
	HAL_Delay(500);

	pl_motor_start();
	v_e=turning_table(360, 240, 240, 600, 7000);

	pl_motor_stop();
	HAL_Delay(500);
	pl_motor_standby(0);
}

void control_test_motor2(uint8_t turn_mode,uint8_t WallMode)
{
	MOTOR_MODE mode;
//	mode.WallControlMode=0;
	mode.WallControlMode=WallMode;
	mode.WallControlStatus=0;
	mode.WallCutMode=0;
	mode.calMazeMode=0;
	pl_motor_standby(1);
	pl_motor_start();

if(turn_mode==0){
	straight_table(540, 100, 100, 600, 7000, mode);
}else{
	turning_table(360*5, 120, 120, 600, 7000);
}

	pl_motor_stop();
	HAL_Delay(500);
	pl_motor_standby(0);
}


/*******************************************************************/
/*	モータの初期化					(pl_speaker_init)	*/
/*******************************************************************/
/*	モータの初期化する。						*/
/*******************************************************************/
void motor_init(void)
{

	modeacc=0;
	g_acc_flag=0;


}



void interrupt_Motor(void){


	if (modeacc == 0) {
		//g_WallControl_mode=0;
		//g_acc_flag=0;
	}
	if (modeacc == 1) {
		g_TargetStraight.displacement += g_TargetStraight.velocity*INTERRUPT_TIME;// + g_TargetStraight.acceleration*INTERRUPT_TIME*INTERRUPT_TIME/2;
		g_TargetStraight.velocity += g_TargetStraight.acceleration*INTERRUPT_TIME;
		g_TargetTurning.displacement += g_TargetTurning.velocity*INTERRUPT_TIME;// + g_TargetTurning.acceleration*INTERRUPT_TIME*INTERRUPT_TIME/2;
		g_TargetTurning.velocity += g_TargetTurning.acceleration*INTERRUPT_TIME;
		cal_table(g_TrapezoidStraight,&g_TargetStraight);
	}
	if (modeacc == 2){
		g_WallControl_mode=0;
		g_TargetStraight.displacement += g_TargetStraight.velocity*INTERRUPT_TIME;// + g_TargetStraight.acceleration*INTERRUPT_TIME*INTERRUPT_TIME/2;
		g_TargetStraight.velocity += g_TargetStraight.acceleration*INTERRUPT_TIME;
		g_TargetTurning.displacement += g_TargetTurning.velocity*INTERRUPT_TIME;// + g_TargetTurning.acceleration*INTERRUPT_TIME*INTERRUPT_TIME/2;
		g_TargetTurning.velocity += g_TargetTurning.acceleration*INTERRUPT_TIME;
		cal_table(g_TrapezoidTurning,&g_TargetTurning);
	}
	float PID_wall = calWallConrol();
	float velocity_l = g_TargetStraight.velocity + g_TargetTurning.velocity * TREAD_WIDTH / 2 * M_PI / 180 + PID_wall;
		pl_motor_mode_L(velocity_l);
		pl_motor_count_L(velocity_l);
	float velocity_r = g_TargetStraight.velocity - g_TargetTurning.velocity * TREAD_WIDTH / 2 * M_PI / 180 - PID_wall;
	    pl_motor_mode_R(velocity_r);
	    pl_motor_count_R(velocity_r);



}

void cal_table(TRAPEZOID input,TARGET *target){
float time_over;
if (input.displacement>=0){
	switch (g_acc_flag) {
	case 0:
		//速度FBなし
		break;
	case 1:
		//加速(減速)
			if (target->velocity >= input.count_velocity){
				target->velocity = input.count_velocity;
				target->acceleration = 0;
				g_acc_flag=2;
			}
			else if((input.displacement <= (2*target->velocity*target->velocity
					-input.start_velocity*input.start_velocity
					-input.end_velocity*input.end_velocity)
					/2/input.acceleration)){
				time_over=((2*target->velocity*target->velocity
						-input.start_velocity*input.start_velocity
						-input.end_velocity*input.end_velocity)
						/2/input.acceleration-input.displacement)/target->velocity;
				target->displacement -= 1/2*INTERRUPT_TIME*input.acceleration*(2*time_over);
				target->velocity -= input.acceleration*(2*time_over);

				target->acceleration = -input.acceleration;
				g_acc_flag=3;
			}
		break;
	case 2:
		//定常
		if (input.displacement-target->displacement <=
				(input.count_velocity*input.count_velocity
						-input.end_velocity*input.end_velocity)/2/input.acceleration) {
			time_over=(target->displacement+(input.count_velocity*input.count_velocity
						-input.end_velocity*input.end_velocity)/2
						/input.acceleration-input.displacement)/target->velocity;
			target->displacement -= 1/2*INTERRUPT_TIME*input.acceleration*time_over;
			target->velocity -= input.acceleration*(time_over);

			target->acceleration = -input.acceleration;
			g_acc_flag=3;
		}
		break;
	case 3:
		//減速(加速)
		if (target->velocity <= input.end_velocity){
			target->velocity = input.end_velocity;
			target->acceleration = 0;
			g_acc_flag=4;
		}
		break;
	case 4:
		//終了(0でもいいかも)
		break;
	case 5:
		//加速のみ
		if (target->displacement >= input.displacement){
			target->acceleration = 0;
			g_acc_flag=4;
		}
	case 6:
		//減速のみ
		if (target->displacement >= input.displacement){
			target->acceleration = 0;
			g_acc_flag=4;
		}
		break;
	}
}else{
	switch (g_acc_flag) {
	case 0:
		//速度FBなし
		break;
	case 1:
		//加速(減速)
			if (target->velocity <= input.count_velocity){
				target->velocity = input.count_velocity;
				target->acceleration = 0;
				g_acc_flag=2;
			}

			else if((-input.displacement <= (2*target->velocity*target->velocity
					-input.start_velocity*input.start_velocity
					-input.end_velocity*input.end_velocity)
					/2/input.acceleration)){
				time_over=(-(2*target->velocity*target->velocity
						-input.start_velocity*input.start_velocity
						-input.end_velocity*input.end_velocity)
						/2/input.acceleration-input.displacement)/target->velocity;
				target->displacement += 1/2*INTERRUPT_TIME*input.acceleration*(2*time_over);
				target->velocity += input.acceleration*(2*time_over);

				target->acceleration = input.acceleration;
				g_acc_flag=3;
			}
		break;
	case 2:
		//定常
		if (-input.displacement+target->displacement <=
				(input.count_velocity*input.count_velocity
						-input.end_velocity*input.end_velocity)/2/input.acceleration) {
			time_over=(target->displacement-(input.count_velocity*input.count_velocity
						-input.end_velocity*input.end_velocity)/2
						/input.acceleration-input.displacement)/target->velocity;
			target->displacement += 1/2*INTERRUPT_TIME*input.acceleration*time_over;
			target->velocity += input.acceleration*(time_over);

			target->acceleration = input.acceleration;
			g_acc_flag=3;
		}
		break;
	case 3:
		//減速(加速)
		if (target->velocity >= input.end_velocity){
			target->velocity = input.end_velocity;
			target->acceleration = 0;
			g_acc_flag=4;
		}
		break;
	case 4:
		//終了(0でもいいかも)
	case 5:
		//加速のみ
		if (target->displacement <= input.displacement){
			target->acceleration = 0;
			g_acc_flag=4;
		}
	case 6:
		//減速のみ
		if (target->displacement <= input.displacement){
			target->acceleration = 0;
			g_acc_flag=4;
		}
	}

}

}


float straight_table(float input_displacement, float input_start_velocity,
	float input_end_velocity, float input_count_velocity, float input_acceleration,MOTOR_MODE mode) {

	float MinRequired_displacement=
			(input_end_velocity*input_end_velocity
					-input_start_velocity*input_start_velocity
					)/2/input_acceleration;

	g_WallControl_mode=mode.WallControlMode;
	//g_WallControlStatus=mode.WallControlStatus;
	// 例外処理
	if (input_acceleration < 0){input_acceleration=-input_acceleration;}//加速が負

	g_TrapezoidStraight.displacement = input_displacement;
	g_TrapezoidStraight.start_velocity = input_start_velocity;
	g_TrapezoidStraight.end_velocity = input_end_velocity;
	g_TrapezoidStraight.count_velocity = input_count_velocity;
	g_TrapezoidStraight.acceleration = input_acceleration;

	if (input_count_velocity>=0){g_TargetStraight.acceleration = input_acceleration;
	}else{g_TargetStraight.acceleration = -input_acceleration;}
	g_TargetStraight.velocity = input_start_velocity;
	g_TargetStraight.displacement = 0;
	g_TargetTurning.velocity = 0;
	g_TargetTurning.acceleration = 0;
	g_TargetTurning.displacement = 0;

	g_acc_flag=1;
		if (input_displacement>0 && MinRequired_displacement>input_displacement){g_acc_flag=5;g_TargetStraight.acceleration = input_acceleration;}
		if (input_displacement>0 && MinRequired_displacement<-input_displacement){g_acc_flag=6;g_TargetStraight.acceleration = -input_acceleration;}
		if (input_displacement<0 && MinRequired_displacement>-input_displacement){g_acc_flag=5;g_TargetStraight.acceleration = -input_acceleration;}
		if (input_displacement<0 && MinRequired_displacement<input_displacement){g_acc_flag=6;g_TargetStraight.acceleration = input_acceleration;}
	modeacc = 1;



	//pl_motor_start();
	while (g_acc_flag!=4){
//		printf("SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d\n", g_motorCount_l,g_motorCount_r,g_motorCount_l,g_motorCount_l);
		if(mode.calMazeMode==1){
		update_wall(direction,front_wall ,right_wall,left_wall,x,y);
		}
	}
	modeacc = 0;

	//pl_motor_stop();

	return g_TargetStraight.velocity;
}


float turning_table(float input_displacement, float input_start_velocity,
	float input_end_velocity, float input_count_velocity, float input_acceleration) {

	float MinRequired_displacement=
			(input_end_velocity*input_end_velocity
					-input_start_velocity*input_start_velocity
					)/2/input_acceleration;
	// 例外処理
	if (input_acceleration < 0){input_acceleration=-input_acceleration;}//加速が負

	g_TrapezoidTurning.displacement = input_displacement;
	g_TrapezoidTurning.start_velocity = input_start_velocity;
	g_TrapezoidTurning.end_velocity = input_end_velocity;
	g_TrapezoidTurning.count_velocity = input_count_velocity;
	g_TrapezoidTurning.acceleration = input_acceleration;

	if (input_count_velocity>=0){g_TargetTurning.acceleration = input_acceleration;
	}else{g_TargetTurning.acceleration = -input_acceleration;}
	g_TargetTurning.velocity = input_start_velocity;
	g_TargetTurning.displacement = 0;
	g_TargetStraight.velocity = 0;
	g_TargetStraight.acceleration = 0;
	g_TargetStraight.displacement = 0;

	g_acc_flag=1;
		if (input_displacement>0 && MinRequired_displacement>input_displacement){g_acc_flag=5;g_TargetTurning.acceleration = input_acceleration;}
		if (input_displacement>0 && MinRequired_displacement<-input_displacement){g_acc_flag=6;g_TargetTurning.acceleration = -input_acceleration;}
		if (input_displacement<0 && MinRequired_displacement>-input_displacement){g_acc_flag=5;g_TargetTurning.acceleration = -input_acceleration;}
		if (input_displacement<0 && MinRequired_displacement<input_displacement){g_acc_flag=6;g_TargetTurning.acceleration = input_acceleration;}
	modeacc = 2;


	//pl_motor_start();
	while (g_acc_flag!=4){

	}
	modeacc = 0;

	//pl_motor_stop();

	return g_TargetTurning.velocity;
}


float slalom_table(float input_center_velocity,float input_displacement, float input_start_velocity,
	float input_end_velocity, float input_count_velocity, float input_acceleration) {

	float MinRequired_displacement=
			(input_end_velocity*input_end_velocity
					-input_start_velocity*input_start_velocity
					)/2/input_acceleration;
	// 例外処理
	if (input_acceleration < 0){input_acceleration=-input_acceleration;}//加速が負

	g_TrapezoidTurning.displacement = input_displacement;
	g_TrapezoidTurning.start_velocity = input_start_velocity;
	g_TrapezoidTurning.end_velocity = input_end_velocity;
	g_TrapezoidTurning.count_velocity = input_count_velocity;
	g_TrapezoidTurning.acceleration = input_acceleration;

	if (input_count_velocity>=0){g_TargetTurning.acceleration = input_acceleration;
	}else{g_TargetTurning.acceleration = -input_acceleration;}
	g_TargetTurning.velocity = input_start_velocity;
	g_TargetTurning.displacement = 0;
	g_TargetStraight.velocity = input_center_velocity;
	g_TargetStraight.acceleration = 0;
	g_TargetStraight.displacement = 0;

	g_acc_flag=1;
		if (input_displacement>0 && MinRequired_displacement>input_displacement){g_acc_flag=5;g_TargetTurning.acceleration = input_acceleration;}
		if (input_displacement>0 && MinRequired_displacement<-input_displacement){g_acc_flag=6;g_TargetTurning.acceleration = -input_acceleration;}
		if (input_displacement<0 && MinRequired_displacement>-input_displacement){g_acc_flag=5;g_TargetTurning.acceleration = -input_acceleration;}
		if (input_displacement<0 && MinRequired_displacement<input_displacement){g_acc_flag=6;g_TargetTurning.acceleration = input_acceleration;}
	modeacc = 2;


	//pl_motor_start();
	while (g_acc_flag!=4){

	}
	modeacc = 0;

	//pl_motor_stop();

	return g_TargetTurning.velocity;
}
