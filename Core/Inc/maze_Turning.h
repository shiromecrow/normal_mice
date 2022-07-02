/*
 * maze_Turning.h
 *
 *  Created on: Jul 2, 2022
 *      Author: sf199
 */

#ifndef INC_MAZE_TURNING_H_
#define INC_MAZE_TURNING_H_

#include "Control_motor.h"

typedef struct {
	float g_speed;
		float f_ofset;
		float e_ofset;
		float t_speed;
		float t_acc;
} parameter;

typedef struct {

parameter slalom_R;
parameter slalom_L;
parameter turn90_R;
parameter turn90_L;
parameter turn180_R;
parameter turn180_L;
parameter turn45in_R;
parameter turn45in_L;
parameter turn135in_R;
parameter turn135in_L;
parameter turn45out_R;
parameter turn45out_L;
parameter turn135out_R;
parameter turn135out_L;
parameter V90_R;
parameter V90_L;

}parameter_speed;

extern parameter_speed speed500_exploration;
extern parameter_speed speed600_shortest;
extern parameter_speed speed800_shortest;
extern parameter_speed speed1000_shortest;


void test_motor_start(MOTOR_MODE *);
void test_motor_stop();

void slalomR(parameter,char,char);
void slalomL(parameter,char,char);
void turn90R(parameter,char);
void turn90L(parameter,char);
void turn180R(parameter,char);
void turn180L(parameter,char);
void turn45inR(parameter,char);
void turn45inL(parameter,char);
void turn135inR(parameter,char);
void turn135inL(parameter,char);
void turn45outR(parameter,char);
void turn45outL(parameter,char);
void turn135outR(parameter,char);
void turn135outL(parameter,char);
void V90R(parameter,char test_mode);
void V90L(parameter,char test_mode);



void testturning(parameter_speed,int,char);


#endif /* INC_MAZE_TURNING_H_ */
