/*
 * PL_speaker.h
 *
 *  Created on: 2022/06/22
 *      Author: sf199
 */

#ifndef INC_PL_SPEAKER_H_
#define INC_PL_SPEAKER_H_


#include "stm32l4xx_hal.h"

typedef struct {
	float interval;
	uint16_t waittime;
} soundData;


#define seriaNUM 170
#define Zelda_nazoNUM 8


extern soundData seria[seriaNUM];
extern soundData Zelda_nazo[Zelda_nazoNUM];

void pl_test_speaker();

void pl_speaker_init();

uint16_t calFrequencyCount(float);

void pl_stop_Sound();

void pl_play_oneSound(char);

void pl_play_Music(uint16_t, soundData *);

void inputZelda_nazo();
void inputseria();



#endif /* INC_PL_SPEAKER_H_ */
