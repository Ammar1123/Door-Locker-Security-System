/*
 * Timer.c
 *
 *  Created on: Oct 31, 2022
 *      Author: amaar
 */
#include "Timer.h"
#include <avr/io.h>
#include <util/delay.h>
#include "std_types.h"
#include <avr/interrupt.h>
#include "common_macros.h"


static volatile void (*g_callBackPtr)(void) = NULL_PTR;

ISR(TIMER1_OVF_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

void PWM_Timer0_Init(unsigned char set_duty_cycle)
{

	TCNT0 = 0; //Set Timer Initial value

	OCR0 = ((float)set_duty_cycle/100) * 255;

	DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	TCCR1A =0;
	SET_BIT(TCCR1A,FOC1A); /* for non-PWM mode */
	SET_BIT(TCCR1A,FOC1B);
	TCCR1B = Config_Ptr->prescaler;
	TCNT1 = Config_Ptr->initial_value;

	if (Config_Ptr->mode == Normal) {
		SET_BIT(TIMSK, TOIE1); /* enable interrupts for overflow mode */
		SET_BIT(TIFR,TOV1);

	} else if (Config_Ptr->mode == CTC) {
		SET_BIT(TCCR1B, WGM12);
		OCR1A = Config_Ptr->compare_value;
		SET_BIT(TIMSK, OCIE1A); /* enable interrupts for CTC mode */
		SET_BIT(TIFR,OCF1A); /* enable CTC flag */
	}
}
void Timer1_deInit(void){
	TCCR1B = 0xF8;
	OCR1A = 0;
	TIMSK &= 0xE3;
	TCNT1 = 0;

}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

