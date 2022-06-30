/*
 * mode_selection.h
 *
 *  Created on: Jun 30, 2022
 *      Author: sf199
 */

#ifndef INC_MODE_SELECTION_H_
#define INC_MODE_SELECTION_H_


unsigned char mode_decision(unsigned char,unsigned char);

void mode_display0();
void mode_display1();

void mode_execution(unsigned char,unsigned char);

void mode_PLtest(unsigned char);
void mode_Running(unsigned char);
void mode_Tuning(unsigned char);


#endif /* INC_MODE_SELECTION_H_ */
