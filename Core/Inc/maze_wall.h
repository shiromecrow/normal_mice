/*
 * maze_wall.h
 *
 *  Created on: Jul 2, 2022
 *      Author: sf199
 */

#ifndef INC_MAZE_WALL_H_
#define INC_MAZE_WALL_H_


typedef struct{
	unsigned short row[15];
	unsigned short column[15];
	unsigned short row_look[15];
	unsigned short column_look[15];

}WALL;

extern WALL wall;
extern WALL record;


extern unsigned short walk_count[256]; //歩数いれる箱


void maze_clear();
void update_wall(int, _Bool , _Bool, _Bool,int, int);

void maze_maker(int,int,int,int,int,int);
void maze_maker2(int,int,int,int,int,int);
void maze_makerhosuu(int,int,int);
void maze_makerST(int);
void maze_makerRun(int,int,int,int,int,int);
void maze_makeronly(int,int,int,int,int,int);
void maze_makerback(int,int,int,int,int,int);
void maze_makerslant(void);

void maze_display();


#endif /* INC_MAZE_WALL_H_ */
