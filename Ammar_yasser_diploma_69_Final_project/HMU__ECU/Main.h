 /******************************************************************************
 *
 *
 * File Name: Main.h
 *
 * Description: Header file for the main of mc1
 *
 * Author: Ammar yasser
 *
 *******************************************************************************/
#ifndef MAIN_H_
#define MAIN_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define KEYPAD_DELAY        500
#define UART_DELAY          50



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description : send the password
 */
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * description the function that will be included in the main of HIMI_ECU
 */
void start(void);
/*
 * description: this function will include store the 5 letters that will be stored in password plus confirm letter
 */
void enterPassword (uint8 password[] );
/*
 * description send the password byte after byte to the Control_ECU MC to be checked
 */
void sendPassword (uint8 password[] );
/*
 * this function will display the following options on the LCD
 */
void optionsDisplay (void);
/*
 * this function will display the procedures in case of opening the door on the LCD
 */
void openDoor (void);
/*
 * this function will display the procedures in case of entering wrong password 3 times on the LCD
 */
void securityAlarm (void);

/* Function Description
 * call back function that increase the tick every call*/
void timer_tick(void);

/* Function Description
 * wait until specified time in seconds */
void wait(uint16 seconds);

#endif
