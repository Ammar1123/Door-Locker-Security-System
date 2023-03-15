 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: source file for the Buzzer AVR driver
 *
 * Author: Ammar yasser
 *
 *******************************************************************************/
#include "buzzer.h"
#include "gpio.h"
 /*******************************************************************************
  *                           Function Definition                                  *
  *******************************************************************************/
/*
 * description: Setup the direction for the buzzer pin as output pin through the GPIO driver
 * Turn off the buzzer through the GPIO
 */
void Buzzer_init(){
	//setup direction  pin
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);//to turn off buzzer
}
/*
 *Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void){
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}
/*
 * description: turn off buzzer
 */
void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
