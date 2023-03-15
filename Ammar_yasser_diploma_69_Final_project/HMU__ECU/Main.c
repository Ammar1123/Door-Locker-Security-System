 /******************************************************************************
 *
 *
 * File Name: Main.c
 *
 * Description: source file for the main of mc1
 *
 * Author: Ammar yasser
 *
 *******************************************************************************/
#include "Keypad.h"
#include "lcd.h"
#include "uart.h"
#include "timer.h"
#include <avr/io.h>
#include <util/delay.h>
#include "Main.h"
#include "avr/interrupt.h"
/*******************************************************************************
 *                              Global variables                                 *
 *******************************************************************************/
uint32 g_tick=0;//the ticks timer will count

/*
 * define Uart struct
 * 8 bits of data,Disable parity ,One stop bit ,Baud rate=9600
 */
UART_ConfigType Config={Eight,Disabled,OneBit,Mode_9600};

/*****************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * description the function that will be included in the main
 */
void start(void){
	//Enable I-bit
	SREG|=(1<<7);
	//initialize the LCD
	LCD_init();
	//initialize the UART
	UART_init(&Config);
	uint8 password[5] , confirmPassword[5] , passwordVerified , command ;
	while(passwordVerified == 0)
	{
		LCD_clearScreen();
		LCD_displayString("Plz enter pass");


		enterPassword(password);
		_delay_ms(UART_DELAY);
		sendPassword(password);

		LCD_clearScreen();
		LCD_displayString("Confirm Pass");
		enterPassword( confirmPassword );
		_delay_ms(UART_DELAY);
		sendPassword( confirmPassword );
		_delay_ms(UART_DELAY);

		passwordVerified = UART_recieveByte();
		_delay_ms(UART_DELAY);

		if(passwordVerified)
		{
			LCD_clearScreen();
			LCD_displayString("Right Password");
		}

		else
		{
			LCD_clearScreen();
			LCD_displayString("Wrong Password");
		}

		_delay_ms(3000);

	}

	while(1)
	{
		optionsDisplay();
		command = KEYPAD_getPressedKey();
		_delay_ms(KEYPAD_DELAY);
		UART_sendByte(command);
		_delay_ms(UART_DELAY);
		if(command == '+')
		{
			LCD_clearScreen();
			LCD_displayString("Plz enter pass");
			enterPassword(password);
			_delay_ms(UART_DELAY);
			sendPassword(password);
			passwordVerified = 0;
			passwordVerified = UART_recieveByte();
			if(passwordVerified)
			{
				openDoor();
			}

			else
			{
				uint8 falsePasswordCounter = UART_recieveByte();
				if(falsePasswordCounter >=3)
				{
					securityAlarm();
				}

				else
				{
					LCD_clearScreen();
					LCD_displayString("Wrong Password");
					_delay_ms(2500);
				}

			}

		}

		else if(command == '-')
		{
			LCD_clearScreen();
			LCD_displayString("Enter old pass");


			enterPassword(password);
			_delay_ms(UART_DELAY);
			sendPassword(password);

			passwordVerified = 0;
			passwordVerified = UART_recieveByte();


			if(passwordVerified)
			{
				LCD_clearScreen();
				LCD_displayString("Enter New pass");

				enterPassword(password);
				_delay_ms(UART_DELAY);
				sendPassword(password);

				LCD_clearScreen();
				LCD_displayString("Confirm New pass");

				enterPassword( confirmPassword );
				_delay_ms(UART_DELAY);
				sendPassword( confirmPassword );
				_delay_ms(UART_DELAY);

				passwordVerified = 0;
				passwordVerified = UART_recieveByte();

				if(passwordVerified)
				{
					LCD_clearScreen();
					LCD_displayString("Password Changed");
					_delay_ms(3000);
				}

				else
				{
					LCD_clearScreen();
					LCD_displayString("Wrong Password");
					_delay_ms(2500);
				}
			}

			else
			{
				uint8 falsePasswordCounter = UART_recieveByte();
				if(falsePasswordCounter >=3)
				{
					securityAlarm();
				}

				else
				{
					LCD_clearScreen();
					LCD_displayString("Wrong Password");
					_delay_ms(2500);
				}
			}
		}
	}
}

/*
 * description: this function will include store the 5 letters that will be stored in password plus confirm letter
 */
void enterPassword (uint8 password[])
{
	uint8 i;
	LCD_moveCursor(1, 5);

	for (i=0 ; i<6 ;++i)
	{
		while ((KEYPAD_getPressedKey() != 13) && (i == 5));

		password[i] = KEYPAD_getPressedKey();
		_delay_ms (KEYPAD_DELAY);
		LCD_displayCharacter('*');
	}

	_delay_ms (KEYPAD_DELAY);
}
/*
 * description send the password byte after byte to the Control_ECU MC to be checked
 */
void sendPassword (uint8 password[])
{
	uint8 i;

	for (i=0 ; i<5 ; ++i)
	{
		UART_sendByte (password[i]);
	}
	_delay_ms (UART_DELAY);
}
/*
 * this function will display the procedures in case of opening the door on the LCD
 */
void optionsDisplay (void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "- :Change Pass");
	LCD_displayStringRowColumn(1, 0, "+ :Open Door");
}

void openDoor (void)
{
	LCD_clearScreen();
	LCD_displayString("Door Unlocking.");

	wait(15);//wait 15 seconds

	LCD_clearScreen();
	LCD_displayString("Door Opened");

	wait(3);//wait 3 seconds

	LCD_clearScreen();
	LCD_displayString("Door is Locking.");
	wait(15);//wait 15 seconds
}

void securityAlarm (void)
{

	LCD_clearScreen();
	LCD_displayString("Security Alarm....");
	wait(60);//wait for 1 minute
}
/* Function Description
 * call back function that increase the tick every call*/
void timer_tick(void){
	g_tick++;
}
/* Function Description
 * wait until specified time in seconds */
void wait(uint16 seconds){
	g_tick=0;
	uint32 counter=seconds;/*the seconds required to be waited */
	Timer1_ConfigType timerS={0,7813,F_1024,CTC};
	Timer1_init(&timerS);
	Timer1_setCallBack(timer_tick);
	while(g_tick<counter);
	Timer1_deInit();
}

/*******************************************************************************
 *                              MAIN Function                                  *
 *******************************************************************************/

int main()
{
	start();
}


