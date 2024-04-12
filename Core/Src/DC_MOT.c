/*
 * DC_MOT.c
 *
 *  Created on: Apr 2, 2024
 *      Author: clt
 */


#include "DC_MOT.h"


void DC_Motor_Init(void)
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1); //start PWM on TIM3 channel 1
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1); //start PWM on TIM4 channel 1
	TIM3->CCR1 = 0;
	TIM4->CCR1 = 0;
}
void DC_Motor_SetSpeed(uint8_t dutyCycle)
{
	TIM3->CCR1 = dutyCycle;
	TIM4->CCR1 = dutyCycle;
}
void Decrease_speed_Gradually(uint8_t speed)
{
	for(uint8_t i=speed;i>=0;i--)
	{
		DC_Motor_SetSpeed(i);
		HAL_Delay(250);
	}
}
void increase_speed_Gradually(uint8_t speed)
{
	uint8_t i=0;
	for(i=0; i<=speed ;i++)
	{
		DC_Motor_SetSpeed(i);
		HAL_Delay(200);
	}
}

void DC_Motor_SetDirection(uint8_t direction)
{
	switch (direction)
	{
	case 1: //Forward
		HAL_GPIO_WritePin(GPIOB, IN1_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, IN2_PIN_15, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOB, IN4_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, IN3_PIN_3, GPIO_PIN_RESET);

		break;
	case 2: // Backward

		HAL_GPIO_WritePin(GPIOA, IN2_PIN_15, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, IN3_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, IN1_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, IN4_PIN_4, GPIO_PIN_RESET);


		break;
	case 3: // Left
		HAL_GPIO_WritePin(GPIOB, IN3_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, IN4_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, IN1_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, IN2_PIN_15, GPIO_PIN_RESET);

		break;
	case 4: // Right

		HAL_GPIO_WritePin(GPIOB, IN3_PIN_3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, IN4_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, IN1_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, IN2_PIN_15, GPIO_PIN_RESET);

		break;
	default:
		break;

	}
}


void DC_Motor_STOP(void)
{
	TIM3->CCR1 = 0;
	TIM4->CCR1 = 0;
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1); // Close TIM3
	//HAL_GPIO_WritePin(GPIOA, ENA_PIN_6, GPIO_PIN_RESET);  //EN1 PIN ENABLE LOW
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);  //Close TIM4
	//HAL_GPIO_WritePin(GPIOB, ENA_PIN_6, GPIO_PIN_RESET);  //EN1 PIN ENABLE LOW
}
