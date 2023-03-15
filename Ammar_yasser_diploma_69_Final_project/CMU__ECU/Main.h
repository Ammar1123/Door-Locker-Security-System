 /******************************************************************************
 *
 *
 * File Name: Main.h
 *
 * Description: Header file for the Main file of second MC
 *
 * Author: Ammar yasser
 *
 *******************************************************************************/
#ifndef MAIN_H_
#define MAIN_H_

#include "std_types.h"
#include "buzzer.h"
#include "uart.h"
#include "dcmotor.h"
#include "twi.h"
#include "external_eeprom.h"
#include "timer.h"
#include <util/delay.h>
#include <avr/io.h>
#include "gpio.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define KEYPAD_DELAY        600
#define UART_DELAY          130
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * description the function that will be included in the main of the Control_ECU
 */
void start(void);
/*
 * description : this function will receive the password from HIMI_ECU
 */
void receivePassword (uint8 password[]);
/*
 * description : this function will be used to verify the password with the stored password in eeprom
 */
uint8 verifyPassword (uint8 password[] , uint8 confirmPassword[]);
/*
 * description : this function will be used to make open the door procedures
 * make motor move CW for 15 sec
 * make motor stop for 3 sec
 * make motor move A_CW for 15 sec
 */
void openDoor (void);
/*
 * description: this function will be used to make procedures of failing to enter password 3 times
 * activate buzzer for 1 minute the deactivate it
 */
void falsePassword (void);
/*
 * description: store the password in the eeprom
 */
void storePasswordeeprom (uint8 password[]);
/*
 * description: retrieve the password from the eeprom
 */
void readPasswordeeprom (uint8 password []);


/* Function Description
 * call back function that increase the tick every call*/
void timer_tick(void);

/* Function Description
 * wait until specified time in milliseconds */
void wait(uint16 seconds);
#endif
