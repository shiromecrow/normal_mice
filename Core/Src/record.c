/*
 * record.c
 *
 *  Created on: Jul 1, 2022
 *      Author: sf199
 */


#include "record.h"
#include "Control_sensor.h"


float record_value[max_record_num][max_record_time];

char record_mode;

int record_time;

//int SEN_record[5][15];
//int SEN_recordD[5][15];



void record_reset(void) {
	record_mode=0;
	record_time = 0;
}



void record_data(float *input_record_data, int numlen) {
	if (record_mode == 1) {
		for (int record_count = 0; record_count < numlen; record_count++) {
		record_value[record_count][record_time] = input_record_data[record_count];
		}


		record_time++;
		if (record_time >= max_record_time) {
					record_mode = 0;
				}
	}
}

void record_print(void) {
	int a;
	for (a = 0; a <= record_time; a++) {
		printf("%d", a);
		for (int record_count = 0; record_count < max_record_num; record_count++) {
		printf(",%f", record_value[record_count][a]);
		}
		printf("\n");
	}
}

void interrupt_record(void){

	float r_data[max_record_num]={(float)(g_sensor[0][0]),(float)(g_sensor[1][0]),(float)(g_sensor[2][0]),(float)(g_sensor[3][0])};
	//	float r_data[max_record_num]={g_TargetStraight.velocity};
	record_data(r_data, max_record_num);



}
