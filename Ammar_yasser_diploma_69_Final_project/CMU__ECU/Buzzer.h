 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the Buzzer AVR driver
 *
 * Author: Ammar yasser
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID     PORTB_ID
#define BUZZER_PIN_ID      PIN0_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * description: Setup the direction for the buzzer pin as output pin through the GPIO driver
 * Turn off the buzzer through the GPIO
 */
void Buzzer_init();
/*
 *Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void);
/*
 * description: turn off buzzer
 */
void Buzzer_off(void);

#endif
