/*
 * maze_strategy.h
 *
 *  Created on: Jul 1, 2022
 *      Author: sf199
 */

#ifndef INC_MAZE_STRATEGY_H_
#define INC_MAZE_STRATEGY_H_

//int pass[255]; //1f 2r 3l
#include "maze_Turning.h"

extern int x;
extern int y;
extern int direction;
extern _Bool front_wall;
extern _Bool right_wall;
extern _Bool left_wall;



//void maze_clean(void);
//void record_in(void);
//void record_out(void);


void AdatiWayReturn(float,float,float,float);

void update_coordinate();


void ShortestWay(float, float,parameter_speed,char);
//void most_speed(float,float,int,char,char,parameter_speed);
//void most_speed3(float,float,int);


#endif /* INC_MAZE_STRATEGY_H_ */
