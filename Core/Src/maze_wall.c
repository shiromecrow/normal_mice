/*
 * maze_wall.c
 *
 *  Created on: Jul 2, 2022
 *      Author: sf199
 */

#include "maze_wall.h"
#include "define.h"

#include "stdio.h"

WALL wall;
WALL record;

int tt = 0;
int ss = 0;
int mode_255 = 0;
unsigned char Xend_cheak = 240; //x終わりの判定240
unsigned char Yend_cheak = 15; //y終わりの判定15



unsigned short walk_count[256]; //歩数いれる箱
unsigned short walk_count_slant[480]; //歩数いれる箱
unsigned char walk_direction[256]; //歩数の方角
unsigned char coordinate; //座標


unsigned char Xcheak_result;
unsigned char Ycheak_result;
unsigned char Xcoordinate;
unsigned char Ycoordinate;
unsigned short wall_north;
unsigned short wall_south;
unsigned short wall_east;
unsigned short wall_west;
unsigned short front_count;
unsigned short left_count;
unsigned short right_count;
unsigned short back_count;
unsigned short count_box[40];
unsigned char box;
unsigned short count_boxnext[40];
unsigned char boxnext;




unsigned short presence[16];

void maze_clear(void) { //初期化
	tt = 0;
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
	tt = 0;

//ここから歩数マップの初期状態を作る．

	walk_count[(GOAL_X * 16) + GOAL_Y] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y] = 0;
	walk_count[(GOAL_X * 16) + GOAL_Y + 1] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y + 1] = 0;
	unsigned short count_number = 1;
	while (count_number <= 255) {
		coordinate = 0;
		while (coordinate <= 255) {
			if (walk_count[coordinate] == count_number - 1) {
				Xcheak_result = coordinate & Xend_cheak;
				Ycheak_result = coordinate & Yend_cheak;
				Xcoordinate = Xcheak_result >> 4;
				Ycoordinate = Ycheak_result;

//壁情報のときに使う
//				shift1 = 1;
//							shift1 = shift1 << Ycoordinate;
//
//							row[Xcoordinate] = row[Xcoordinate] | shift1;

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

void update_wall(int direction, _Bool front_wall , _Bool right_wall, _Bool left_wall,int x, int y){


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

void maze_maker(int direction, _Bool front_wall , _Bool right_wall, _Bool left_wall,int x, int y) {

// 壁情報の更新


//	歩数マップを作成　*************************************
	tt = 0;
	while (tt <= 255) {
		walk_count[tt] = 255;

		tt++;
	}
	tt = 0;

	walk_count[(GOAL_X * 16) + GOAL_Y] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y] = 0;
	walk_count[(GOAL_X * 16) + GOAL_Y + 1] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y + 1] = 0;
	unsigned short count_number = 1;
	while (count_number <= 255) {
		coordinate = 0;
		while (coordinate <= 255) {
			if (walk_count[coordinate] == count_number - 1) {
				Xcheak_result = coordinate & Xend_cheak;
				Ycheak_result = coordinate & Yend_cheak;
				Xcoordinate = Xcheak_result >> 4;
				Ycoordinate = Ycheak_result;

//壁情報のときに使う
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate <= 14) {
					wall_north = column[Ycoordinate] & shift1;
				}
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate >= 1) {
					wall_south = column[Ycoordinate - 1] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate <= 14) {
					wall_east = row[Xcoordinate] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate >= 1) {
					wall_west = row[Xcoordinate - 1] & shift1;
				}
				shift1 = 1;

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

}

//試験用歩数マップ作成短縮方法＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

void maze_maker2(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {

	switch (direction) {
	case 1:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (front_SEN >= f_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (left_SEN >= l_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (right_SEN >= r_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}

		break;
	case 2:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (front_SEN >= f_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (left_SEN >= l_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (right_SEN >= r_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}

		break;
	case 3:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (front_SEN >= f_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (left_SEN >= l_presence && x <= 14) {

			row[x] = row[x] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (right_SEN >= r_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;
		}

		break;
	case 4:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (front_SEN >= f_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (left_SEN >= l_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (right_SEN >= r_presence && y <= 14) {

			column[y] = column[y] | shift1;
		}

		break;

	}

//ここから歩数マッppuを作る．*************************************
	tt = 0;
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
	tt = 0;

	walk_count[(GOAL_X * 16) + GOAL_Y] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y] = 0;
	walk_count[(GOAL_X * 16) + GOAL_Y + 1] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y + 1] = 0;
	count_box[0] = (GOAL_X * 16) + GOAL_Y;
	count_box[1] = ((GOAL_X + 1) * 16) + GOAL_Y;
	count_box[2] = (GOAL_X * 16) + GOAL_Y + 1;
	count_box[3] = ((GOAL_X + 1) * 16) + GOAL_Y + 1;
	unsigned short count_number = 1;
	while (count_number <= 255) {
		box = 0;
		boxnext = 0;
		while (box <= 39) {

			coordinate = count_box[box];
			Xcheak_result = coordinate & Xend_cheak;
			Ycheak_result = coordinate & Yend_cheak;
			Xcoordinate = Xcheak_result >> 4;
			Ycoordinate = Ycheak_result;

//壁情報のときに使う
			shift1 = 1;
			shift1 = shift1 << Xcoordinate;
			if (Ycoordinate <= 14) {
				wall_north = column[Ycoordinate] & shift1;
			}
			shift1 = 1;
			shift1 = shift1 << Xcoordinate;
			if (Ycoordinate >= 1) {
				wall_south = column[Ycoordinate - 1] & shift1;
			}

			shift1 = 1;
			shift1 = shift1 << Ycoordinate;
			if (Xcoordinate <= 14) {
				wall_east = row[Xcoordinate] & shift1;
			}

			shift1 = 1;
			shift1 = shift1 << Ycoordinate;
			if (Xcoordinate >= 1) {
				wall_west = row[Xcoordinate - 1] & shift1;
			}
			shift1 = 1;

			if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
					|| wall_north >= 1) {
			} else {

				walk_count[coordinate + 1] = count_number;
				count_boxnext[boxnext] = coordinate + 1;
				boxnext++;
			}
			if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
					|| wall_south >= 1) {
			} else {

				walk_count[coordinate - 1] = count_number;
				count_boxnext[boxnext] = coordinate - 1;
				boxnext++;
			}
			if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
					|| wall_east >= 1) {
			} else {

				walk_count[coordinate + 16] = count_number;
				count_boxnext[boxnext] = coordinate + 16;
				boxnext++;
			}
			if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
					|| wall_west >= 1) {
			} else {

				walk_count[coordinate - 16] = count_number;
				count_boxnext[boxnext] = coordinate - 16;
				boxnext++;
			}

			if (box == 39) {

				break;
			}
			box++;
			if (count_box[box] == 256) {
				break;
			}

		}
		tt = 0;
		while (tt <= 39) {

			count_box[tt] = count_boxnext[tt];
			count_boxnext[tt] = 256;
			tt++;
		}
		tt = 0;
		if (count_number == 255 || count_box[0] == 256) {
			break;
		}
		count_number++;

	}


}

void maze_makerhosuu(int direction, int x, int y) {

//ここから歩数マッppuを作る．*************************************
	tt = 0;
	while (tt <= 255) {
		walk_count[tt] = 255;

		tt++;
	}
	tt = 0;

	walk_count[(GOAL_X * 16) + GOAL_Y] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y] = 0;
	walk_count[(GOAL_X * 16) + GOAL_Y + 1] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y + 1] = 0;

	unsigned short count_number = 1;
	while (count_number <= 255) {
		coordinate = 0;
		while (coordinate <= 255) {
			if (walk_count[coordinate] == count_number - 1) {
				Xcheak_result = coordinate & Xend_cheak;
				Ycheak_result = coordinate & Yend_cheak;
				Xcoordinate = Xcheak_result >> 4;
				Ycoordinate = Ycheak_result;

				//壁情報のときに使う
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate <= 14) {
					wall_north = column[Ycoordinate] & shift1;
				}
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate >= 1) {
					wall_south = column[Ycoordinate - 1] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate <= 14) {
					wall_east = row[Xcoordinate] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate >= 1) {
					wall_west = row[Xcoordinate - 1] & shift1;
				}
				shift1 = 1;

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

}
void maze_makerST(int STmass) { //いつか作る直進優先の歩数マップ
//XXX
//ここから歩数マッppuを作る．*************************************
	tt = 0;
	while (tt <= 255) {
		walk_count[tt] = 65535;

		tt++;
	}
	tt = 0;

	walk_count[(GOAL_X * 16) + GOAL_Y] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y] = 0;
	walk_count[(GOAL_X * 16) + GOAL_Y + 1] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y + 1] = 0;
	walk_direction[(GOAL_X * 16) + GOAL_Y] = 0;
	walk_direction[((GOAL_X + 1) * 16) + GOAL_Y] = 0;
	walk_direction[(GOAL_X * 16) + GOAL_Y + 1] = 0;
	walk_direction[((GOAL_X + 1) * 16) + GOAL_Y + 1] = 0;

	unsigned short count_number = 1;
	while (count_number <= 255) {
		coordinate = 0;
		while (coordinate <= 255) {
			if (walk_count[coordinate] == count_number - 1) {
				Xcheak_result = coordinate & Xend_cheak;
				Ycheak_result = coordinate & Yend_cheak;
				Xcoordinate = Xcheak_result >> 4;
				Ycoordinate = Ycheak_result;

				//壁情報のときに使う
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate <= 14) {
					wall_north = column[Ycoordinate] & shift1;
				}
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate >= 1) {
					wall_south = column[Ycoordinate - 1] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate <= 14) {
					wall_east = row[Xcoordinate] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate >= 1) {
					wall_west = row[Xcoordinate - 1] & shift1;
				}
				shift1 = 1;

				if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
						|| wall_north >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate + 1] = count_number;
						walk_direction[coordinate + 1] = 1;
					} else {
//					if(walk_count[coordinate - 1] == count_number-1 || )
						if (walk_direction[coordinate] == 1) {
							walk_count[coordinate + 1] = count_number;
							walk_direction[coordinate + 1] = 1;
						} else {
							walk_count[coordinate + 1] = count_number + STmass;
							walk_direction[coordinate + 1] = 1;
						}
					}

				}
				if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
						|| wall_south >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate - 1] = count_number;
						walk_direction[coordinate - 1] = 3;
					} else {
						if (walk_direction[coordinate] == 3) {
							walk_count[coordinate - 1] = count_number;
							walk_direction[coordinate - 1] = 3;
						} else {
							walk_count[coordinate - 1] = count_number + STmass;
							walk_direction[coordinate - 1] = 3;
						}
					}
				}
				if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
						|| wall_east >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate + 16] = count_number;
						walk_direction[coordinate + 16] = 2;
					} else {
						if (walk_direction[coordinate] == 2) {
							walk_count[coordinate + 16] = count_number;
							walk_direction[coordinate + 16] = 2;
						} else {
							walk_count[coordinate + 16] = count_number + STmass;
							walk_direction[coordinate + 16] = 2;
						}
					}
				}
				if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
						|| wall_west >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate - 16] = count_number;
						walk_direction[coordinate - 16] = 4;
					} else {
						if (walk_direction[coordinate] == 4) {
							walk_count[coordinate - 16] = count_number;
							walk_direction[coordinate - 16] = 4;
						} else {
							walk_count[coordinate - 16] = count_number + STmass;
							walk_direction[coordinate - 16] = 4;
						}
					}
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

}

void maze_makerRun(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {

	switch (direction) {
	case 1:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (front_SEN >= f_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (left_SEN >= l_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (right_SEN >= r_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}

		break;
	case 2:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (front_SEN >= f_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (left_SEN >= l_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (right_SEN >= r_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}

		break;
	case 3:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (front_SEN >= f_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (left_SEN >= l_presence && x <= 14) {

			row[x] = row[x] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (right_SEN >= r_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;
		}

		break;
	case 4:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (front_SEN >= f_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (left_SEN >= l_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (right_SEN >= r_presence && y <= 14) {

			column[y] = column[y] | shift1;
		}

		break;

	}

//ここから歩数マッppuを作る．*************************************
	tt = 0;
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
	tt = 0;

	walk_count[(GOAL_X * 16) + GOAL_Y] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y] = 0;
	walk_count[(GOAL_X * 16) + GOAL_Y + 1] = 0;
	walk_count[((GOAL_X + 1) * 16) + GOAL_Y + 1] = 0;
	count_box[0] = (GOAL_X * 16) + GOAL_Y;
	count_box[1] = ((GOAL_X + 1) * 16) + GOAL_Y;
	count_box[2] = (GOAL_X * 16) + GOAL_Y + 1;
	count_box[3] = ((GOAL_X + 1) * 16) + GOAL_Y + 1;
	unsigned short count_number = 1;
	while (count_number <= 255) {
		box = 0;
		boxnext = 0;
		while (box <= 39) {
			coordinate = count_box[box];
			Xcheak_result = coordinate & Xend_cheak;
			Ycheak_result = coordinate & Yend_cheak;
			Xcoordinate = Xcheak_result >> 4;
			Ycoordinate = Ycheak_result;

//壁情報のときに使う
			shift1 = 1;
			shift1 = shift1 << Xcoordinate;
			if (Ycoordinate <= 14) {
				wall_north = column[Ycoordinate] & shift1;
			}
			shift1 = 1;
			shift1 = shift1 << Xcoordinate;
			if (Ycoordinate >= 1) {
				wall_south = column[Ycoordinate - 1] & shift1;
			}

			shift1 = 1;
			shift1 = shift1 << Ycoordinate;
			if (Xcoordinate <= 14) {
				wall_east = row[Xcoordinate] & shift1;
			}

			shift1 = 1;
			shift1 = shift1 << Ycoordinate;
			if (Xcoordinate >= 1) {
				wall_west = row[Xcoordinate - 1] & shift1;
			}
			shift1 = 1;

			if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
					|| wall_north >= 1) {
			} else {
				walk_count[coordinate + 1] = count_number;
				count_boxnext[boxnext] = coordinate + 1;
				boxnext++;
			}
			if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
					|| wall_south >= 1) {
			} else {
				walk_count[coordinate - 1] = count_number;
				count_boxnext[boxnext] = coordinate - 1;
				boxnext++;
			}
			if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
					|| wall_east >= 1) {
			} else {
				walk_count[coordinate + 16] = count_number;
				count_boxnext[boxnext] = coordinate + 16;
				boxnext++;
			}
			if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
					|| wall_west >= 1) {
			} else {
				walk_count[coordinate - 16] = count_number;
				count_boxnext[boxnext] = coordinate - 16;
				boxnext++;
			}

			if (box == 39) {
				break;
			}
			box++;
			if (count_box[box] == 256) {
				break;
			}
		}
		tt = 0;
		while (tt <= 39) {

			count_box[tt] = count_boxnext[tt];
			count_boxnext[tt] = 256;
			tt++;
		}
		tt = 0;
		if (count_number == 255 || count_box[0] == 256) {
			break;
		}
		if (walk_count[(x * 16) + y + 1] <= 254
				&& walk_count[(x * 16) + y - 1] <= 254
				&& walk_count[((x + 1) * 16) + y] <= 254
				&& walk_count[((x - 1) * 16) + y] <= 254) {
			break;
		}
		count_number++;
	}


}

void maze_makeronly(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {

	switch (direction) {
	case 1:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (front_SEN >= f_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (left_SEN >= l_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (right_SEN >= r_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}

		break;
	case 2:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (front_SEN >= f_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (left_SEN >= l_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (right_SEN >= r_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}

		break;
	case 3:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (front_SEN >= f_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (left_SEN >= l_presence && x <= 14) {

			row[x] = row[x] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (right_SEN >= r_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;
		}

		break;
	case 4:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (front_SEN >= f_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (left_SEN >= l_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (right_SEN >= r_presence && y <= 14) {

			column[y] = column[y] | shift1;
		}

		break;

	}

}

void maze_makerback(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {

	switch (direction) {
	case 1:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (front_SEN >= f_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (left_SEN >= l_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (right_SEN >= r_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}

		break;
	case 2:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (front_SEN >= f_presence && x <= 14) {

			row[x] = row[x] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (left_SEN >= l_presence && y <= 14) {

			column[y] = column[y] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (right_SEN >= r_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}

		break;
	case 3:
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (front_SEN >= f_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x <= 14) {
			row_look[x] = row_look[x] | shift1;
		}
		if (left_SEN >= l_presence && x <= 14) {

			row[x] = row[x] | shift1;
		}
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (right_SEN >= r_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;
		}

		break;
	case 4:
		shift1 = 1;
		shift1 = shift1 << y;
		if (x >= 1) {
			row_look[x - 1] = row_look[x - 1] | shift1;
		}
		if (front_SEN >= f_presence && x >= 1) {

			row[x - 1] = row[x - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y >= 1) {
			column_look[y - 1] = column_look[y - 1] | shift1;
		}
		if (left_SEN >= l_presence && y >= 1) {

			column[y - 1] = column[y - 1] | shift1;

		}
		shift1 = 1;
		shift1 = shift1 << x;
		if (y <= 14) {
			column_look[y] = column_look[y] | shift1;
		}
		if (right_SEN >= r_presence && y <= 14) {

			column[y] = column[y] | shift1;
		}

		break;

	}

//ここから歩数マッppuを作る．*************************************
	tt = 0;
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
	tt = 0;

	walk_count[0] = 0;
	count_box[0] = 0;
	unsigned short count_number = 1;
	while (count_number <= 255) {
		box = 0;
		boxnext = 0;
		while (box <= 39) {

			coordinate = count_box[box];
			Xcheak_result = coordinate & Xend_cheak;
			Ycheak_result = coordinate & Yend_cheak;
			Xcoordinate = Xcheak_result >> 4;
			Ycoordinate = Ycheak_result;

//壁情報のときに使う
			shift1 = 1;
			shift1 = shift1 << Xcoordinate;
			if (Ycoordinate <= 14) {
				wall_north = column[Ycoordinate] & shift1;
			}
			shift1 = 1;
			shift1 = shift1 << Xcoordinate;
			if (Ycoordinate >= 1) {
				wall_south = column[Ycoordinate - 1] & shift1;
			}

			shift1 = 1;
			shift1 = shift1 << Ycoordinate;
			if (Xcoordinate <= 14) {
				wall_east = row[Xcoordinate] & shift1;
			}

			shift1 = 1;
			shift1 = shift1 << Ycoordinate;
			if (Xcoordinate >= 1) {
				wall_west = row[Xcoordinate - 1] & shift1;
			}
			shift1 = 1;

			if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
					|| wall_north >= 1) {
			} else {

				walk_count[coordinate + 1] = count_number;
				count_boxnext[boxnext] = coordinate + 1;
				boxnext++;
			}
			if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
					|| wall_south >= 1) {
			} else {

				walk_count[coordinate - 1] = count_number;
				count_boxnext[boxnext] = coordinate - 1;
				boxnext++;
			}
			if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
					|| wall_east >= 1) {
			} else {

				walk_count[coordinate + 16] = count_number;
				count_boxnext[boxnext] = coordinate + 16;
				boxnext++;
			}
			if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
					|| wall_west >= 1) {
			} else {

				walk_count[coordinate - 16] = count_number;
				count_boxnext[boxnext] = coordinate - 16;
				boxnext++;
			}

			if (box == 39) {

				break;
			}
			box++;
			if (count_box[box] == 256) {
				break;
			}

		}
		tt = 0;
		while (tt <= 39) {

			count_box[tt] = count_boxnext[tt];
			count_boxnext[tt] = 256;
			tt++;
		}
		tt = 0;
		if (count_number == 255 || count_box[0] == 256) {
			break;
		}
		count_number++;
	}


}

void maze_makerslant(void) { //いつか作る直進優先の歩数マップ
//XXX
//ここから歩数マッppuを作る．*************************************
	int count1, count2;
	int row_exist, column_exist;
	tt = 0;
	while (tt <= 255) {
		walk_count_slant[tt] = 65535 - 1;

		tt++;
	}
	tt = 0;

	walk_count_slant[columnnumber + 16 * GOAL_Y + GOAL_X] = 0;
	walk_count_slant[columnnumber + 16 * GOAL_Y + GOAL_X + 1] = 0;
	walk_count_slant[rownumber + 16 * GOAL_X + GOAL_Y] = 0;
	walk_count_slant[rownumber + 16 * GOAL_X + GOAL_Y + 1] = 0;
//	walk_direction[(GOAL_X * 16) + GOAL_Y] = 0;
//	walk_direction[((GOAL_X + 1) * 16) + GOAL_Y] = 0;
//	walk_direction[(GOAL_X * 16) + GOAL_Y + 1] = 0;
//	walk_direction[((GOAL_X + 1) * 16) + GOAL_Y + 1] = 0;

	for (count1 = 0; count1 < 15; count1++) {
		for (count2 = 0; count2 < 16; count2++) {
			shift1 = 1;
			shift1 = shift1 << count2;
			column_exist = column[count1] && shift1;
			shift1 = 1;
			shift1 = shift1 << count2;
			row_exist = row[count1] && shift1;
			if (column_exist >= 1) {
				walk_count_slant[columnnumber + 16 * count1 + count2] = 65535;
			}
			if (row_exist >= 1) {
				walk_count_slant[rownumber + 16 * count1 + count2] = 65535;
			}
		}

	}

	unsigned short count_number = 1;
	while (count_number <= 255) {
		coordinate = 0;
		while (coordinate <= 255) {
			if (walk_count[coordinate] == count_number - 1) {
				Xcheak_result = coordinate & Xend_cheak;
				Ycheak_result = coordinate & Yend_cheak;
				Xcoordinate = Xcheak_result >> 4;
				Ycoordinate = Ycheak_result;

				//壁情報のときに使う
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate <= 14) {
					wall_north = column[Ycoordinate] & shift1;
				}
				shift1 = 1;
				shift1 = shift1 << Xcoordinate;
				if (Ycoordinate >= 1) {
					wall_south = column[Ycoordinate - 1] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate <= 14) {
					wall_east = row[Xcoordinate] & shift1;
				}

				shift1 = 1;
				shift1 = shift1 << Ycoordinate;
				if (Xcoordinate >= 1) {
					wall_west = row[Xcoordinate - 1] & shift1;
				}
				shift1 = 1;

				if (walk_count[coordinate + 1] <= 254 || Ycoordinate == 15
						|| wall_north >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate + 1] = count_number;
						walk_direction[coordinate + 1] = 1;
					} else {
//					if(walk_count[coordinate - 1] == count_number-1 || )
						if (walk_direction[coordinate] == 1) {
							walk_count[coordinate + 1] = count_number;
							walk_direction[coordinate + 1] = 1;
						} else {
							walk_count[coordinate + 1] = count_number;
							walk_direction[coordinate + 1] = 1;
						}
					}

				}
				if (walk_count[coordinate - 1] <= 254 || Ycoordinate == 0
						|| wall_south >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate - 1] = count_number;
						walk_direction[coordinate - 1] = 3;
					} else {
						if (walk_direction[coordinate] == 3) {
							walk_count[coordinate - 1] = count_number;
							walk_direction[coordinate - 1] = 3;
						} else {
							walk_count[coordinate - 1] = count_number;
							walk_direction[coordinate - 1] = 3;
						}
					}
				}
				if (walk_count[coordinate + 16] <= 254 || Xcoordinate == 15
						|| wall_east >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate + 16] = count_number;
						walk_direction[coordinate + 16] = 2;
					} else {
						if (walk_direction[coordinate] == 2) {
							walk_count[coordinate + 16] = count_number;
							walk_direction[coordinate + 16] = 2;
						} else {
							walk_count[coordinate + 16] = count_number;
							walk_direction[coordinate + 16] = 2;
						}
					}
				}
				if (walk_count[coordinate - 16] <= 254 || Xcoordinate == 0
						|| wall_west >= 1) {
				} else {
					if (walk_direction[coordinate] == 0) {
						walk_count[coordinate - 16] = count_number;
						walk_direction[coordinate - 16] = 4;
					} else {
						if (walk_direction[coordinate] == 4) {
							walk_count[coordinate - 16] = count_number;
							walk_direction[coordinate - 16] = 4;
						} else {
							walk_count[coordinate - 16] = count_number;
							walk_direction[coordinate - 16] = 4;
						}
					}
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

}


void maze_display(void) {

	tt = 14;

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n");
	while (tt >= -1) { //ttはｙ軸
		shift2 = 1;

		shift2 = shift2 << (tt + 1);
		ss = 0;
		printf("|%5d", walk_count[tt + 1]);
		while (ss < 15) {
			presence[ss] = row[ss] & shift2;
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
			shift2 = 1;
			shift2 = shift2 << ss;
			presence[ss] = column[tt] & shift2;

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

//  myprintf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+ + + + + + + + + + + + + + + + +\n");
//	myprintf("|                               |\n");
//	myprintf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n");
//look_display
//	tt = 0;
//		while (tt <= 14) {
//			row_look[tt] = ~ row_look[tt];
//column_look[tt]= ~ column_look[tt];
//				tt++;
//			}
//		tt=0;
	tt = 14;
	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n");

	while (tt >= -1) { //ttはｙ軸
		shift2 = 1;

		shift2 = shift2 << (tt + 1);
		ss = 0;
		printf("|%5d", walk_count[tt + 1]);
		while (ss < 15) {
			presence[ss] = row_look[ss] & shift2;
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
			shift2 = 1;
			shift2 = shift2 << ss;
			presence[ss] = column_look[tt] & shift2;

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

