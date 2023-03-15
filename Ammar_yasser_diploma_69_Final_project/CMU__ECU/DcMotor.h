 /******************************************************************************
 *
 * Module: Dc motor
 *
 * File Name: dc_motor.h
 *
 * Description: header file for the dc_motor driver
 *
 * Author: Ammar yasser
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
/*******************************************************************************
 *                                Define new data type                                  *
 *******************************************************************************/
typedef enum{
	Clockwise, AntiClockWise,Stop
}DcMotor_State;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MOTOR_PORT_ID   PORTC_ID
#define MOTOR_PIN_1_ID  PIN4_ID
#define MOTOR_PIN_2_ID  PIN5_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * description
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 *  Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void);



void DcMotor_Rotate(DcMotor_State state);
#endif
