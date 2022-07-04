/*
 * maze_wall.c
 *
 *  Created on: Jul 2, 2022
 *      Author: sf199
 */

#include "maze_wall.h"
#include "maze_strategy.h"
#include "define.h"

#include "stdio.h"

WALL wall;
WALL record;



unsigned short walk_count[256]; //歩数いれる箱
//unsigned short walk_count_slant[480]; //歩数いれる箱
//unsigned char walk_direction[256]; //歩数の方角
//int mode_255 = 0;



void maze_clear(void) { //初期化
	int tt = 0;

	while (tt <= 14) {
		wall.row[tt] = 0;
		wall.column[tt] = 0;
		wall.row_look[tt] = 0;
		wall.column_look[tt] = 0;
		tt++;
	}
	tt = 0;

	while (tt <= 255) {
		walk_count[tt] = 255;

		tt++;
	}


//ここから歩数マップの初期状態を作る．

	walk_count[(GOAL_X * 16) + GOAL_Y] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y] = 0;
	walk_count[(GOAL_X * 16) + GOAL_Y + 1] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y + 1] = 0;
	unsigned short coordinate;
	unsigned short count_number = 1;
	unsigned short Xcoordinate,Ycoordinate;
	while (count_number <= 255) {
		coordinate = 0;
		while (coordinate <= 255) {
			if (walk_count[coordinate] == count_number - 1) {
				Xcoordinate = (coordinate & 0xf0) >> 4;
				Ycoordinate = coordinate & 0x0f;
//壁情報のときに使う
				if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15) {
				} else {
					walk_count[coordinate + 1] = count_number;
				}
				if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0) {
				} else {
					walk_count[coordinate - 1] = count_number;
				}
				if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15) {
				} else {
					walk_count[coordinate + 16] = count_number;
				}
				if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0) {
				} else {
					walk_count[coordinate - 16] = count_number;
				}

			}
			if (coordinate == 255) {
				break;
			}
			coordinate++;

		}

		if (count_number == 255) {
			break;
		}
		count_number++;
	}


//kokomade

}

void update_wall(void){


	switch (direction) {
	case 1:
		if (y <= 14) {
			wall.column_look[y] = wall.column_look[y] | (1 << x);
			if(front_wall){wall.column[y] = wall.column[y] | (1 << x);}
		}

		if (x >= 1) {
			wall.row_look[x - 1] = wall.row_look[x - 1] | (1 << y);
			if(left_wall){wall.row[x - 1] = wall.row[x - 1] | (1 << y);}
		}

		if (x <= 14) {
			wall.row_look[x] = wall.row_look[x] | (1 << y);
			if(right_wall){wall.row[x] = wall.row[x] | (1 << y);}
		}

		break;
	case 2:
		if (x <= 14) {
			wall.row_look[x] = wall.row_look[x] | (1 << y);
			if(front_wall){wall.row[x] = wall.row[x] | (1 << y);}
		}

		if (y <= 14) {
			wall.column_look[y] = wall.column_look[y] | (1 << x);
			if(left_wall){wall.column[y] = wall.column[y] | (1 << x);}
		}

		if (y >= 1) {
			wall.column_look[y - 1] = wall.column_look[y - 1] | (1 << x);
			if(right_wall){wall.column[y - 1] = wall.column[y - 1] | (1 << x);}
		}

		break;
	case 3:
		if (y >= 1) {
			wall.column_look[y - 1] = wall.column_look[y - 1] | (1 << x);
			if(front_wall){wall.column[y - 1] = wall.column[y - 1] | (1 << x);}
		}

		if (x <= 14) {
			wall.row_look[x] = wall.row_look[x] | (1 << y);
			if(left_wall){wall.row[x] = wall.row[x] | (1 << y);}
		}

		if (x >= 1) {
			wall.row_look[x - 1] = wall.row_look[x - 1] | (1 << y);
			if(right_wall){wall.row[x - 1] = wall.row[x - 1] | (1 << y);}
		}

		break;
	case 4:
		if (x >= 1) {
			wall.row_look[x - 1] = wall.row_look[x - 1] | (1 << y);
			if(front_wall){wall.row[x - 1] = wall.row[x - 1] | (1 << y);}
		}

		if (y >= 1) {
			wall.column_look[y - 1] = wall.column_look[y - 1] | (1 << x);
			if(left_wall){wall.column[y - 1] = wall.column[y - 1] | (1 << x);}
		}

		if (y <= 14) {
			wall.column_look[y] = wall.column_look[y] | (1 << x);
			if(right_wall){wall.column[y] = wall.column[y] | (1 << x);}
		}

		break;

	}


}


void search_AroundWalkCount(unsigned short *front_count,unsigned short *right_count,unsigned short *back_count,unsigned short *left_count){
//int direction,int x_coordinate,int y_coordinate
	unsigned short north_count,east_count,south_count,west_count;
//	unsigned short front_count, right_count, back_count, left_count;

	if (y >= 15) {north_count = MAX_WALKCOUNT;}
	else {north_count = walk_count[16 * x + y + 1];}

	if (x >= 15) {east_count = MAX_WALKCOUNT;}
	else {east_count = walk_count[16 * (x + 1) + y];}

	if (y <= 0) {south_count = MAX_WALKCOUNT;}
	else {south_count = walk_count[16 * x + y - 1];}

	if (x <= 0) {west_count = MAX_WALKCOUNT;}
	else {west_count = walk_count[16 * (x - 1) + y];}


	switch (direction) {		//
	case 1:
		*front_count = north_count;
		*right_count = east_count;
		*back_count = south_count;
		*left_count = west_count;
		break;
	case 2:
		*front_count = east_count;
		*right_count = south_count;
		*back_count = west_count;
		*left_count = north_count;
		break;
	case 3:
		*front_count = south_count;
		*right_count = west_count;
		*back_count = north_count;
		*left_count = east_count;
		break;
	case 4:
		*front_count = west_count;
		*right_count = north_count;
		*back_count = east_count;
		*left_count = south_count;
		break;

	}


}



void maze_maker0(_Bool WallUpdataMode,_Bool WalkUpdataMode) {
	if(WallUpdataMode){
	update_wall();
	}

	if(WalkUpdataMode){
//	歩数マップを作成　*************************************
	int tt = 0;
	while (tt <= 255) {
		walk_count[tt] = 255;
		tt++;
	}
//　ゴール座標の歩数を0にする
	walk_count[(GOAL_X * 16) + GOAL_Y] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y] = 0;
	walk_count[(GOAL_X * 16) + GOAL_Y + 1] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y + 1] = 0;
	unsigned short coordinate;
	unsigned short count_number = 1;
	unsigned short Xcoordinate,Ycoordinate;
	unsigned short wall_north,wall_south,wall_east,wall_west;
	while (count_number <= 255) {
		coordinate = 0;
		while (coordinate <= 255) {
			if (walk_count[coordinate] == count_number - 1) {
				Xcoordinate = (coordinate & 0xf0) >> 4;
				Ycoordinate = coordinate & 0x0f;

//壁情報のときに使う

				if (Ycoordinate <= 14) {
					wall_north = wall.column[Ycoordinate] & (1 << Xcoordinate);
				}
				if (Ycoordinate >= 1) {
					wall_south = wall.column[Ycoordinate - 1] & (1 << Xcoordinate);
				}
				if (Xcoordinate <= 14) {
					wall_east = wall.row[Xcoordinate] & (1 << Ycoordinate);
				}
				if (Xcoordinate >= 1) {
					wall_west = wall.row[Xcoordinate - 1] & (1 << Ycoordinate);
				}

				if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
						|| wall_north >= 1) {
				} else {
					walk_count[coordinate + 1] = count_number;
				}
				if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
						|| wall_south >= 1) {
				} else {
					walk_count[coordinate - 1] = count_number;
				}
				if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
						|| wall_east >= 1) {
				} else {
					walk_count[coordinate + 16] = count_number;
				}
				if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
						|| wall_west >= 1) {
				} else {
					walk_count[coordinate - 16] = count_number;
				}

			}
			if (coordinate == 255) {break;}
			coordinate++;
		}
		if (count_number == 255) {break;}
		count_number++;
	}
	}

}

//試験用歩数マップ作成短縮方法＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

void maze_maker(void) {

	update_wall();

//ここから歩数マップを作る．*************************************
	int tt = 0;
	unsigned short count_box[40];
	unsigned short count_boxnext[40];
	while (tt <= 255) {
		walk_count[tt] = 255;
		tt++;
	}
	tt = 0;
	while (tt <= 39) {
		count_box[tt] = 256;
		count_boxnext[tt] = 256;
		tt++;
	}

	walk_count[(GOAL_X * 16) + GOAL_Y] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y] = 0;
	walk_count[(GOAL_X * 16) + GOAL_Y + 1] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y + 1] = 0;
	count_box[0] = (GOAL_X * 16) + GOAL_Y;
	count_box[1] = ((GOAL_X + 1) * 16) + GOAL_Y;
	count_box[2] = (GOAL_X * 16) + GOAL_Y + 1;
	count_box[3] = ((GOAL_X + 1) * 16) + GOAL_Y + 1;
	unsigned short coordinate;
	unsigned short count_number = 1;
	unsigned short Xcoordinate,Ycoordinate;
	unsigned short wall_north,wall_south,wall_east,wall_west;
	unsigned short box,boxnext;
	while (count_number <= 255) {
		box=0;boxnext=0;

		while (box <= 39) {

			coordinate = count_box[box];
			Xcoordinate = (coordinate & 0xf0) >> 4;
			Ycoordinate = coordinate & 0x0f;
//壁情報のときに使う
			if (Ycoordinate <= 14) {
				wall_north = wall.column[Ycoordinate] & (1 << Xcoordinate);
			}
			if (Ycoordinate >= 1) {
				wall_south = wall.column[Ycoordinate - 1] & (1 << Xcoordinate);
			}
			if (Xcoordinate <= 14) {
				wall_east = wall.row[Xcoordinate] & (1 << Ycoordinate);
			}
			if (Xcoordinate >= 1) {
				wall_west = wall.row[Xcoordinate - 1] & (1 << Ycoordinate);
			}

			if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
					|| wall_north >= 1) {} else {
				walk_count[coordinate + 1] = count_number;
				count_boxnext[boxnext] = coordinate + 1;
				boxnext++;
			}
			if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
					|| wall_south >= 1) {} else {
				walk_count[coordinate - 1] = count_number;
				count_boxnext[boxnext] = coordinate - 1;
				boxnext++;
			}
			if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
					|| wall_east >= 1) {} else {
				walk_count[coordinate + 16] = count_number;
				count_boxnext[boxnext] = coordinate + 16;
				boxnext++;
			}
			if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
					|| wall_west >= 1) {} else {
				walk_count[coordinate - 16] = count_number;
				count_boxnext[boxnext] = coordinate - 16;
				boxnext++;
			}
			if (box == 39) {break;}
			box++;
			if (count_box[box] == 256) {break;}
		}

		tt = 0;
		while (tt <= 39) {
			count_box[tt] = count_boxnext[tt];
			count_boxnext[tt] = 256;
			tt++;
		}
		if (count_number == 255 || count_box[0] == 256) {break;}
		count_number++;
	}

}


void maze_makerBack(void) {
	update_wall();

//ここから歩数マップを作る．*************************************
	int tt = 0;
	unsigned short count_box[40];
	unsigned short count_boxnext[40];
	while (tt <= 255) {
		walk_count[tt] = 255;
		tt++;
	}
	tt = 0;
	while (tt <= 39) {
		count_box[tt] = 256;
		count_boxnext[tt] = 256;
		tt++;
	}

	walk_count[0] = 0;
	count_box[0] = 0;
	unsigned short coordinate;
	unsigned short count_number = 1;
	unsigned short Xcoordinate,Ycoordinate;
	unsigned short wall_north,wall_south,wall_east,wall_west;
	unsigned short box,boxnext;
	while (count_number <= 255) {
		box=0;boxnext=0;

		while (box <= 39) {

			coordinate = count_box[box];
			Xcoordinate = (coordinate & 0xf0) >> 4;
			Ycoordinate = coordinate & 0x0f;
//壁情報のときに使う
			if (Ycoordinate <= 14) {
				wall_north = wall.column[Ycoordinate] & (1 << Xcoordinate);
			}
			if (Ycoordinate >= 1) {
				wall_south = wall.column[Ycoordinate - 1] & (1 << Xcoordinate);
			}
			if (Xcoordinate <= 14) {
				wall_east = wall.row[Xcoordinate] & (1 << Ycoordinate);
			}
			if (Xcoordinate >= 1) {
				wall_west = wall.row[Xcoordinate - 1] & (1 << Ycoordinate);
			}

			if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
					|| wall_north >= 1) {} else {
				walk_count[coordinate + 1] = count_number;
				count_boxnext[boxnext] = coordinate + 1;
				boxnext++;
			}
			if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
					|| wall_south >= 1) {} else {
				walk_count[coordinate - 1] = count_number;
				count_boxnext[boxnext] = coordinate - 1;
				boxnext++;
			}
			if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
					|| wall_east >= 1) {} else {
				walk_count[coordinate + 16] = count_number;
				count_boxnext[boxnext] = coordinate + 16;
				boxnext++;
			}
			if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
					|| wall_west >= 1) {} else {
				walk_count[coordinate - 16] = count_number;
				count_boxnext[boxnext] = coordinate - 16;
				boxnext++;
			}
			if (box == 39) {break;}
			box++;
			if (count_box[box] == 256) {break;}
		}

		tt = 0;
		while (tt <= 39) {
			count_box[tt] = count_boxnext[tt];
			count_boxnext[tt] = 256;
			tt++;
		}
		if (count_number == 255 || count_box[0] == 256) {break;}
		count_number++;
	}

}

void maze_display(void) {
	int ss;
	int tt = 14;
	unsigned short presence[16];

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n");
	while (tt >= -1) { //ttはｙ軸
		ss = 0;
		printf("|%5d", walk_count[tt + 1]);
		while (ss < 15) {
			presence[ss] = wall.row[ss] & (1 << (tt + 1));
			if (presence[ss] == 0) {
				printf(" %5d", walk_count[tt + 1 + (ss + 1) * 16]);
			} else {
				printf("|%5d", walk_count[tt + 1 + (ss + 1) * 16]);
			}
			ss++;
		}
		printf("|\n");
		ss = 0;
		while (ss <= 15) { // all clear***************************************
			presence[ss] = 0;
			ss++;
		}
		ss = 0; // all clear***************************************
		if (tt <= -1) {
			break;
		}
		while (ss <= 15) {
			presence[ss] = wall.column[tt] & (1 << ss);

			if (presence[ss] == 0) {
				printf("+     ");
			} else {
				printf("+-----");
			}
			ss++;
		}

		printf("+\n");

		ss = 0;

		while (ss <= 15) { // all clear***************************************
			presence[ss] = 0;

			ss++;
		}
		ss = 0; // all clear***************************************

		tt--;
	}

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n\n");

	tt = 14;
	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n");

	while (tt >= -1) { //ttはｙ軸


		ss = 0;
		printf("|%5d", walk_count[tt + 1]);
		while (ss < 15) {
			presence[ss] = wall.row_look[ss] & (1 << (tt + 1));
			if (presence[ss] == 0) {
				printf(" %5d", walk_count[tt + 1 + (ss + 1) * 16]);
			} else {
				printf("|%5d", walk_count[tt + 1 + (ss + 1) * 16]);
			}
			ss++;
		}
		printf("|\n");
		ss = 0;
		while (ss <= 15) { // all clear***************************************
			presence[ss] = 0;

			ss++;
		}
		ss = 0; // all clear***************************************
		if (tt <= -1) {
			break;
		}
		while (ss <= 15) {
			presence[ss] = wall.column_look[tt] & (1 << ss);

			if (presence[ss] == 0) {
				printf("+     ");
			} else {
				printf("+-----");
			}
			ss++;
		}

		printf("+\n");

		ss = 0;

		while (ss <= 15) { // all clear***************************************
			presence[ss] = 0;

			ss++;
		}
		ss = 0; // all clear***************************************

		tt--;
	}

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n\n");

}

