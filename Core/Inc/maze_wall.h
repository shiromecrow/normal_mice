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
void update_wall();
void search_AroundWalkCount(unsigned short *,unsigned short *,unsigned short *,unsigned short *);

void maze_maker0(_Bool,_Bool);
void maze_maker();
//void maze_makerhosuu(int,int,int);
//void maze_makerST(int);
//void maze_makerRun(int,int,int,int,int,int);
//void maze_makeronly(int,int,int,int,int,int);
void maze_makerBack();
//void maze_makerslant(void);

void maze_display();


#endif /* INC_MAZE_WALL_H_ */
