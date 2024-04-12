/*
 * DC_MOT.h
 *
 *  Created on: Apr 2, 2024
 *      Author: clt
 */

#ifndef INC_DC_MOT_H_
#define INC_DC_MOT_H_

#include "stm32f1xx_hal.h"
extern TIM_HandleTypeDef  htim3;
extern TIM_HandleTypeDef  htim4;


// MACROS Define Motor PINS
/*#define ENA_PIN_6           GPIO_ODR_ODR6 //A    //PWM for motor  TIM3  //GA
#define IN1_PIN_5           GPIO_ODR_ODR5   //B    //Direction Control
#define IN2_PIN_15           GPIO_ODR_ODR15    //A    //Direction control
#define ENB_PIN_6           GPIO_ODR_ODR6 //B     //PWM for motor   TIM4
#define IN3_PIN_3           GPIO_ODR_ODR3  //B          //Direction Control
#define IN4_PIN_4           GPIO_ODR_ODR4  //B           //Direction control*/

#define ENA_PIN_6           GPIO_PIN_6 //A    //PWM for motor  TIM3  //GA
#define IN1_PIN_5           GPIO_PIN_5   //B    //Direction Control
#define IN2_PIN_15          GPIO_PIN_15    //A    //Direction control
#define ENB_PIN_6      	    GPIO_PIN_6 //B     //PWM for motor   TIM4
#define IN3_PIN_3           GPIO_PIN_3  //B          //Direction Control
#define IN4_PIN_4  		    GPIO_PIN_4





/**
 * @brief:  Starts the DC motor by enabling PWM on TIM3 channel 1 andTIM4 channel 1 his function starts the pulse width modulation (PWM) on TIM3 channel 1, which is used to control the speed
           of a DC motor. By calling this function, the DC motor will begin rotating at the desired speed..
 * @note  Before calling this function, make sure that the TIM3 &TIM4 peripheral and TIM3 &TIM4 channel 1 are properly configured..
 * @retval None
 */


void DC_Motor_Init(void);

/**

@brief: This function sets the speed of the DC motor by adjusting the duty cycle of the PWM signal on TIM3 channel 1.
The duty cycle is specified by the parameter 'dutyCycle', which should be a value between 0 and 255 representing
@note Before calling this function, make sure that the TIM3 &TIM4  peripheral and TIM3&TIM4 channel 1 are properly configured.
@param[in]: dutyCycle The duty cycle value representing the desired speed. Should be between 0 and 255.
@retval: None
 */
void DC_Motor_SetSpeed(uint8_t dutyCycle);


/**

@brief: this function gradually decreases the speed of the DC motor by adjusting the duty cycle of the PWM signal on TIM3 channel 1.
The speed is decreased gradually from the current speed to 0. The parameter 'speed' specifies the initial speed of the motor,
@note: Before calling this function, make sure that the TIM3 &TIM4 peripheral, TIM3 &TIM4 channel 1, and the DC motor are properly configured.
@param[in] speed The initial speed of the motor. Should be between 0 and 255.
@retval: None
 */
void Decrease_speed_Gradually(uint8_t speed);

/**
@brief: his function gradually increase the speed of the DC motor by adjusting the duty cycle of the PWM signal on TIM3 channel 1.
The speed is increase gradually from the current speed to MAX_VALUE DUTY_CYCLE 100. The parameter 'speed' specifies the initial speed of the motor,
@note: Before calling this function, make sure that the TIM3 &TIM4 peripheral, TIM3 &TIM4 channel 1, and the DC motor are properly configured.
@param[in] speed The initial speed of the motor. Should be between 0 and 255.
@retval: None
 */
void increase_speed_Gradually(uint8_t speed);

/**
@brief: This function sets the direction of the DC motor by controlling the GPIO pins connected to the motor driver.
The parameter 'direction' specifies the desired direction, which can be one of the following values:
1: Forward
2: Backward
3: Left
4: Right
@note Before calling this function, make sure that the GPIO pins connected to the motor driver are properly configured OUTPUT.
@param[in] direction The desired direction of the motor. Should be one of the values mentioned above.
@retval None
 */
void DC_Motor_SetDirection(uint8_t direction);

/**

@brief :This function stops the DC motor by disabling the pulse width modulation (PWM) on TIM3 &TIM4 channel 1.
By calling this function, the PWM signal that controls the motor speed will be turned off, causing the motor to stop rotating.
@note Before calling this function, make sure that the TIM3 peripheral and TIM3 &TIM4 channel 1 are properly configured.
@retval None
 */

void DC_Motor_STOP(void);



#endif /* INC_DC_MOT_H_ */
