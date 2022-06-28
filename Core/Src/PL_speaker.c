/*
 * PL_speaker.c
 *
 *  Created on: 2022/06/22
 *      Author: sf199
 */


#include "PL_speaker.h"
#include "tim.h"
#include "define.h"



soundData seria[seriaNUM];
soundData Zelda_nazo[Zelda_nazoNUM];

void pl_test_speaker(void)
{
	for(int count=1;count<15;count++){
		pl_play_oneSound(count);
		}

	pl_play_Music(8, Zelda_nazo);
	pl_play_Music(169, seria);


}



/*******************************************************************/
/*	スピーカーの初期化					(pl_speaker_init)	*/
/*******************************************************************/
/*	スピーカーの初期化する。						*/
/*******************************************************************/
void pl_speaker_init(void)
{

	  HAL_TIM_Base_Start_IT(&htim15);//speaker
	  HAL_TIM_PWM_MspInit(&htim15);//speaker

	  inputseria();
	  inputZelda_nazo();


}


/*******************************************************************/
/*	周波数からcycleCountへの変換					(calFrequencyCount)	*/
/*******************************************************************/
/*	周波数からPWMに送るcycleCountを計算する．。						*/
/*******************************************************************/
uint16_t calFrequencyCount(float tarHz) {
	uint16_t tarCount;
	if (tarHz == 0) {
		tarCount = 0;
	} else {
		tarCount = (uint16_t) (1000000.0 / tarHz - 1.0);
	}
	return tarCount;
}


/*******************************************************************/
/*	speakerの停止と初期化					(pl_stop_Sound)	*/
/*******************************************************************/
/*	speakerを停止してグローバル変数を初期化する．						*/
/*******************************************************************/
void pl_stop_Sound(void){
	HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_2);

}

/*******************************************************************/
/*	任意の周波数の一音を出力					(pl_play_oneSound)	*/
/*******************************************************************/
/*	scaleにあわせた周波数での一音を出力する．．						*/
/*******************************************************************/
void pl_play_oneSound(char scale) {
	uint16_t cycleCount, j;
	float Hz;
	Hz = 1.0;
	for (j = 0; j < scale; j++) {
		Hz = Hz * 1.0595;
	}
	cycleCount = calFrequencyCount(440 * 0.6 * Hz);
	__HAL_TIM_SET_AUTORELOAD(&htim15, cycleCount);
	__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2,cycleCount * SPEAKER_LOUDNESS);

	__HAL_TIM_SET_COUNTER(&htim15, 0);
	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);
	HAL_Delay(600);
	HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_2);

}



/*******************************************************************/
/*	任意の音楽を出力					(pl_play_Music)	*/
/*******************************************************************/
/*	playDataの音楽を出力する．						*/
/*******************************************************************/
void pl_play_Music(uint16_t dataMaxNum, soundData *playData) {

	uint16_t i;
	uint16_t cycleCount, cycleCount_f;

	for (i = 0; i < dataMaxNum; i++) {
		HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_2);

		cycleCount = calFrequencyCount(playData[i].interval);
		cycleCount_f = (int) ((float) (cycleCount) * SPEAKER_LOUDNESS);
		__HAL_TIM_SET_AUTORELOAD(&htim15, cycleCount);

		__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2,cycleCount_f);
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);
		HAL_Delay(playData[i].waittime);
	}
	HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_2);
}




/*******************************************************************/
/*	音楽用構造体配列の入力					(input)	*/
/*******************************************************************/
/*	音楽用の構造体を定義してる．						*/
/*******************************************************************/
void inputZelda_nazo(void) {
	Zelda_nazo[0].interval = 1480;
	Zelda_nazo[0].waittime = 19 * 7;
	Zelda_nazo[1].interval = 1397;
	Zelda_nazo[1].waittime = 19 * 7;
	Zelda_nazo[2].interval = 1175;
	Zelda_nazo[2].waittime = 19 * 7;
	Zelda_nazo[3].interval = 831;
	Zelda_nazo[3].waittime = 19 * 7;
	Zelda_nazo[4].interval = 784;
	Zelda_nazo[4].waittime = 19 * 7;
	Zelda_nazo[5].interval = 1245;
	Zelda_nazo[5].waittime = 19 * 7;
	Zelda_nazo[6].interval = 1568;
	Zelda_nazo[6].waittime = 19 * 7;
	Zelda_nazo[7].interval = 1976;
	Zelda_nazo[7].waittime = 99 * 7;

}


void inputseria(void) {
	seria[0].interval = 698;
	seria[0].waittime = 224;
	seria[1].interval = 880;
	seria[1].waittime = 224;
	seria[2].interval = 988;
	seria[2].waittime = 462;
	seria[3].interval = 698;
	seria[3].waittime = 224;
	seria[4].interval = 880;
	seria[4].waittime = 224;
	seria[5].interval = 988;
	seria[5].waittime = 462;
	seria[6].interval = 698;
	seria[6].waittime = 224;
	seria[7].interval = 880;
	seria[7].waittime = 224;
	seria[8].interval = 988;
	seria[8].waittime = 224;
	seria[9].interval = 1319;
	seria[9].waittime = 224;
	seria[10].interval = 1175;
	seria[10].waittime = 462;
	seria[11].interval = 988;
	seria[11].waittime = 224;
	seria[12].interval = 1047;
	seria[12].waittime = 224;
	seria[13].interval = 988;
	seria[13].waittime = 224;
	seria[14].interval = 784;
	seria[14].waittime = 224;
	seria[15].interval = 659;
	seria[15].waittime = 1169;
	seria[16].interval = 587;
	seria[16].waittime = 224;
	seria[17].interval = 659;
	seria[17].waittime = 224;
	seria[18].interval = 784;
	seria[18].waittime = 224;
	seria[19].interval = 659;
	seria[19].waittime = 1400;
	seria[20].interval = 698;
	seria[20].waittime = 224;
	seria[21].interval = 880;
	seria[21].waittime = 224;
	seria[22].interval = 988;
	seria[22].waittime = 462;
	seria[23].interval = 698;
	seria[23].waittime = 224;
	seria[24].interval = 880;
	seria[24].waittime = 224;
	seria[25].interval = 988;
	seria[25].waittime = 462;
	seria[26].interval = 698;
	seria[26].waittime = 224;
	seria[27].interval = 880;
	seria[27].waittime = 224;
	seria[28].interval = 988;
	seria[28].waittime = 224;
	seria[29].interval = 1319;
	seria[29].waittime = 224;
	seria[30].interval = 1175;
	seria[30].waittime = 462;
	seria[31].interval = 988;
	seria[31].waittime = 224;
	seria[32].interval = 1047;
	seria[32].waittime = 224;
	seria[33].interval = 1319;
	seria[33].waittime = 224;
	seria[34].interval = 988;
	seria[34].waittime = 224;
	seria[35].interval = 784;
	seria[35].waittime = 1169;
	seria[36].interval = 988;
	seria[36].waittime = 224;
	seria[37].interval = 784;
	seria[37].waittime = 224;
	seria[38].interval = 587;
	seria[38].waittime = 224;
	seria[39].interval = 659;
	seria[39].waittime = 1400;
	seria[40].interval = 294;
	seria[40].waittime = 224;
	seria[41].interval = 330;
	seria[41].waittime = 224;
	seria[42].interval = 349;
	seria[42].waittime = 462;
	seria[43].interval = 392;
	seria[43].waittime = 224;
	seria[44].interval = 440;
	seria[44].waittime = 224;
	seria[45].interval = 494;
	seria[45].waittime = 462;
	seria[46].interval = 523;
	seria[46].waittime = 224;
	seria[47].interval = 494;
	seria[47].waittime = 224;
	seria[48].interval = 330;
	seria[48].waittime = 1400;
	seria[49].interval = 698;
	seria[49].waittime = 224;
	seria[50].interval = 784;
	seria[50].waittime = 224;
	seria[51].interval = 880;
	seria[51].waittime = 462;
	seria[52].interval = 988;
	seria[52].waittime = 224;
	seria[53].interval = 1047;
	seria[53].waittime = 224;
	seria[54].interval = 1175;
	seria[54].waittime = 462;
	seria[55].interval = 1319;
	seria[55].waittime = 224;
	seria[56].interval = 1397;
	seria[56].waittime = 224;
	seria[57].interval = 1568;
	seria[57].waittime = 1400;
	seria[58].interval = 294;
	seria[58].waittime = 224;
	seria[59].interval = 330;
	seria[59].waittime = 224;
	seria[60].interval = 349;
	seria[60].waittime = 462;
	seria[61].interval = 392;
	seria[61].waittime = 224;
	seria[62].interval = 440;
	seria[62].waittime = 224;
	seria[63].interval = 494;
	seria[63].waittime = 462;
	seria[64].interval = 523;
	seria[64].waittime = 224;
	seria[65].interval = 494;
	seria[65].waittime = 224;
	seria[66].interval = 330;
	seria[66].waittime = 1400;
	seria[67].interval = 698;
	seria[67].waittime = 224;
	seria[68].interval = 659;
	seria[68].waittime = 105;
	seria[69].interval = 880;
	seria[69].waittime = 224;
	seria[70].interval = 784;
	seria[70].waittime = 105;
	seria[71].interval = 988;
	seria[71].waittime = 224;
	seria[72].interval = 880;
	seria[72].waittime = 105;
	seria[73].interval = 1047;
	seria[73].waittime = 224;
	seria[74].interval = 988;
	seria[74].waittime = 105;
	seria[75].interval = 1175;
	seria[75].waittime = 224;
	seria[76].interval = 1047;
	seria[76].waittime = 105;
	seria[77].interval = 1319;
	seria[77].waittime = 224;
	seria[78].interval = 1175;
	seria[78].waittime = 105;
	seria[79].interval = 1397;
	seria[79].waittime = 224;
	seria[80].interval = 1319;
	seria[80].waittime = 105;
	seria[81].interval = 988;
	seria[81].waittime = 105;
	seria[82].interval = 1047;
	seria[82].waittime = 105;
	seria[83].interval = 880;
	seria[83].waittime = 105;
	seria[84].interval = 988;
	seria[84].waittime = 2576;
	seria[85].interval = 698;
	seria[85].waittime = 224;
	seria[86].interval = 880;
	seria[86].waittime = 224;
	seria[87].interval = 988;
	seria[87].waittime = 462;
	seria[88].interval = 698;
	seria[88].waittime = 224;
	seria[89].interval = 880;
	seria[89].waittime = 224;
	seria[90].interval = 988;
	seria[90].waittime = 462;
	seria[91].interval = 698;
	seria[91].waittime = 224;
	seria[92].interval = 880;
	seria[92].waittime = 224;
	seria[93].interval = 988;
	seria[93].waittime = 224;
	seria[94].interval = 1319;
	seria[94].waittime = 224;
	seria[95].interval = 1175;
	seria[95].waittime = 462;
	seria[96].interval = 988;
	seria[96].waittime = 224;
	seria[97].interval = 1047;
	seria[97].waittime = 224;
	seria[98].interval = 988;
	seria[98].waittime = 224;
	seria[99].interval = 784;
	seria[99].waittime = 224;
	seria[100].interval = 659;
	seria[100].waittime = 1169;
	seria[101].interval = 587;
	seria[101].waittime = 224;
	seria[102].interval = 659;
	seria[102].waittime = 224;
	seria[103].interval = 784;
	seria[103].waittime = 224;
	seria[104].interval = 659;
	seria[104].waittime = 1400;
	seria[105].interval = 698;
	seria[105].waittime = 224;
	seria[106].interval = 880;
	seria[106].waittime = 224;
	seria[107].interval = 988;
	seria[107].waittime = 462;
	seria[108].interval = 698;
	seria[108].waittime = 224;
	seria[109].interval = 880;
	seria[109].waittime = 224;
	seria[110].interval = 988;
	seria[110].waittime = 462;
	seria[111].interval = 698;
	seria[111].waittime = 224;
	seria[112].interval = 880;
	seria[112].waittime = 224;
	seria[113].interval = 988;
	seria[113].waittime = 224;
	seria[114].interval = 1319;
	seria[114].waittime = 224;
	seria[115].interval = 1175;
	seria[115].waittime = 462;
	seria[116].interval = 988;
	seria[116].waittime = 224;
	seria[117].interval = 1047;
	seria[117].waittime = 224;
	seria[118].interval = 1319;
	seria[118].waittime = 224;
	seria[119].interval = 988;
	seria[119].waittime = 224;
	seria[120].interval = 784;
	seria[120].waittime = 1169;
	seria[121].interval = 988;
	seria[121].waittime = 224;
	seria[122].interval = 784;
	seria[122].waittime = 224;
	seria[123].interval = 587;
	seria[123].waittime = 224;
	seria[124].interval = 659;
	seria[124].waittime = 1400;
	seria[125].interval = 294;
	seria[125].waittime = 224;
	seria[126].interval = 330;
	seria[126].waittime = 224;
	seria[127].interval = 349;
	seria[127].waittime = 462;
	seria[128].interval = 392;
	seria[128].waittime = 224;
	seria[129].interval = 440;
	seria[129].waittime = 224;
	seria[130].interval = 494;
	seria[130].waittime = 462;
	seria[131].interval = 523;
	seria[131].waittime = 224;
	seria[132].interval = 494;
	seria[132].waittime = 224;
	seria[133].interval = 330;
	seria[133].waittime = 1400;
	seria[134].interval = 698;
	seria[134].waittime = 224;
	seria[135].interval = 784;
	seria[135].waittime = 224;
	seria[136].interval = 880;
	seria[136].waittime = 462;
	seria[137].interval = 988;
	seria[137].waittime = 224;
	seria[138].interval = 1047;
	seria[138].waittime = 224;
	seria[139].interval = 1175;
	seria[139].waittime = 462;
	seria[140].interval = 1319;
	seria[140].waittime = 224;
	seria[141].interval = 1397;
	seria[141].waittime = 224;
	seria[142].interval = 1568;
	seria[142].waittime = 1400;
	seria[143].interval = 294;
	seria[143].waittime = 224;
	seria[144].interval = 330;
	seria[144].waittime = 224;
	seria[145].interval = 349;
	seria[145].waittime = 462;
	seria[146].interval = 392;
	seria[146].waittime = 224;
	seria[147].interval = 440;
	seria[147].waittime = 224;
	seria[148].interval = 494;
	seria[148].waittime = 462;
	seria[149].interval = 523;
	seria[149].waittime = 224;
	seria[150].interval = 494;
	seria[150].waittime = 224;
	seria[151].interval = 330;
	seria[151].waittime = 1400;
	seria[152].interval = 698;
	seria[152].waittime = 224;
	seria[153].interval = 659;
	seria[153].waittime = 105;
	seria[154].interval = 880;
	seria[154].waittime = 224;
	seria[155].interval = 784;
	seria[155].waittime = 105;
	seria[156].interval = 988;
	seria[156].waittime = 224;
	seria[157].interval = 880;
	seria[157].waittime = 105;
	seria[158].interval = 1047;
	seria[158].waittime = 224;
	seria[159].interval = 988;
	seria[159].waittime = 105;
	seria[160].interval = 1175;
	seria[160].waittime = 224;
	seria[161].interval = 1047;
	seria[161].waittime = 105;
	seria[162].interval = 1319;
	seria[162].waittime = 224;
	seria[163].interval = 1175;
	seria[163].waittime = 105;
	seria[164].interval = 1397;
	seria[164].waittime = 224;
	seria[165].interval = 1319;
	seria[165].waittime = 105;
	seria[166].interval = 988;
	seria[166].waittime = 105;
	seria[167].interval = 1047;
	seria[167].waittime = 105;
	seria[168].interval = 880;
	seria[168].waittime = 105;
	seria[169].interval = 988;
	seria[169].waittime = 2576;

}
