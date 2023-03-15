/*
 * Timer.h
 *
 *  Created on: Oct 31, 2022
 *      Author: amaar
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

typedef enum{
	NoClock,Noprescaler,F_8,F_64,F_256,F_1024
}Timer1_Prescaler;

typedef enum{
	Normal,CTC
}Timer1_Mode;


typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

void Timer1_init(const Timer1_ConfigType * Config_Ptr);

void PWM_Timer0_Init(unsigned char set_duty_cycle);

void Timer1_setCallBack(void(*a_ptr)(void));

void Timer1_deInit(void);

#endif /* TIMER_H_ */
