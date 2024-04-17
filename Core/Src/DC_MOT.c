/*
 * DC_MOT.c
 *
 *  Created on: Apr 2, 2024
 *      Author: clt
 */


#include "DC_MOT.h"

void DC_Motor1_Start(void)
{

	   HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	   HAL_GPIO_WritePin(GPIOA, ENA_PIN_6, GPIO_PIN_SET);  //EN1 PIN ENABLE HIGH
}

void DC_Motor2_Start(void)
{

	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_GPIO_WritePin(GPIOB, ENA_PIN_6, GPIO_PIN_SET);  //EN2 PIN ENABLE HIGH
}
void DC_Motor1_SetSpeed(uint8_t dutyCycle)
{
	/*
	 * the eqution is
	 * percentage=(inputValue-mininput)/(maxinput-mininput)
	 * outputvalue=percentage*(maxoutput-minoutput)+minoutput

	uint16_t Duty_Cycle_Percentage=dutyCycle/100;
	uint16_t Mapping_OutputValue=Duty_Cycle_Percentage*(255);*/

	//uint16_t Duty_Cycle_Percentage =(dutyCycle*65535)/100;

//This register is used to store the capture value when the TIM3 channel 1 is configured in input capture mode.
	TIM3->CCR1 = dutyCycle;
}
void DC_Motor2_SetSpeed(uint8_t dutyCycle)
{
	/*
	 * the eqution is
	 * percentage=(inputValue-mininput)/(maxinput-mininput)
	 * outputvalue=percentage*(maxoutput-minoutput)+minoutput

	uint16_t Duty_Cycle_Percentage=dutyCycle/100;
	uint16_t Mapping_OutputValue=Duty_Cycle_Percentage*(255);*/

	uint16_t Duty_Cycle_Percentage =(dutyCycle*255)/100;

	TIM4->CCR1 = Duty_Cycle_Percentage;
}
void DC_Motor_SetSpeed(uint8_t dutyCycle)
{
	uint16_t Duty_Cycle_Percentage =(dutyCycle*99)/100;
	TIM3->CCR1 = Duty_Cycle_Percentage;
	TIM4->CCR1 = Duty_Cycle_Percentage;
}
void Decrease_speed_Gradually(uint8_t speed)
{
	uint16_t Duty_Cycle_Percentage =(speed*99)/100;

	for(uint16_t i=Duty_Cycle_Percentage;i>=0;i--)
	{
		DC_Motor_SetSpeed(i);
		HAL_Delay(250);

	}
}
void increase_speed_Gradually(uint8_t speed)
{
	uint16_t Duty_Cycle_Percentage =(speed*99)/100;
	for(uint16_t i=0;i<=Duty_Cycle_Percentage;i++)
		{
			DC_Motor_SetSpeed(i);
			HAL_Delay(250);
		}
}

void DC_Motor_SetDirection(uint8_t direction)
{
switch (direction)
{
           case 1: //Forward
        	   HAL_GPIO_WritePin(GPIOB, IN1_PIN_5, GPIO_PIN_SET);
        	   HAL_GPIO_WritePin(GPIOB, IN4_PIN_4, GPIO_PIN_SET);
        	   HAL_GPIO_WritePin(GPIOA, IN2_PIN_15, GPIO_PIN_RESET);
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
void DC_Motor1_STOP(void)
{
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1); // Close TIM3
	 HAL_GPIO_WritePin(GPIOA, ENA_PIN_6, GPIO_PIN_RESET);  //EN1 PIN ENABLE LOW
}
void DC_Motor2_STOP(void)
{

	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);  //Close TIM4
	 HAL_GPIO_WritePin(GPIOB, ENA_PIN_6, GPIO_PIN_RESET);  //EN1 PIN ENABLE LOW
}
