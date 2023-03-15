 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the configurable UART AVR driver
 *
 * Author: Ammar yasser
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
/*******************************************************************************
 *                      Types Declaration                                    *
 *******************************************************************************/
//to choose number of data bits in your frame
typedef enum{
	Five,Six,Seven,Eight,Reserved1,Reserved2,Reserved3,Nine
}UART_BitData;
//to choose type of parity (Bit 5-4 (UPM1,UPM0) in UCSRC Register)
typedef enum{
	Disabled,Reserved,Enabled_Even,Enabled_ODD
}UART_Parity;
//to choose the number of stop bits to be inserted (bit 3 USBS in UCSRC Register)
typedef enum{
	OneBit,TwoBit
}UART_StopBit;
//determine baud rate that will  be used in UBRRL,UBRRH
typedef enum{
	Mode_10=10,Mode_300=300,Mode_600=600,Mode_1200=1200,Mode_2400=2400,
	Mode_4800=4800,Mode_9600=9600,Mode_14400=14400,Mode_19200=19200,
	Mode_38400=38400,Mode_57600=57600,Mode_115200=115200,Mode_128000=128000,Mode_256000=256000
}UART_BaudRate;

typedef struct{
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 UART_BaudRate baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
