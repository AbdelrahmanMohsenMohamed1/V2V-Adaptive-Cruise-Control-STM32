/*
 * UltraSonic_program_.c
 *
 *  Created on: Apr 3, 2024
 *      Author: sayr3
 */



#include <UltraSonic_interface_.h>
#include "cmsis_os.h"

extern TIM_HandleTypeDef htim1;


volatile uint16_t TIMEON = 0;
volatile uint8_t  State = 0;
const uint16_t velocity = 343;


void delay (uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while (__HAL_TIM_GET_COUNTER (&htim1) < time);
}




/**
 * @brief This function handles TIM1 capture compare interrupt.
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	/* USER CODE BEGIN voidTIM1_CC_IRQn 0 */

	if (State == 0) {

		TIM1->CNT = 0x0;
		TIM1->CCR1 = 0x0;


		//Input Capture Edge Select falling edge
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim1 ,TIM_CHANNEL_1 ,TIM_INPUTCHANNELPOLARITY_FALLING) ;
		State++;

	}
	else if (State == 1) {

		TIMEON = TIM1->CCR1;


		//Input Capture Edge Select rising edge
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim1 ,TIM_CHANNEL_1 ,TIM_INPUTCHANNELPOLARITY_RISING) ;

		State++;


	}
	else {
		/*nothing**/
	}


}

/* USER CODE BEGIN 1 */
void ICU_VoidGet_TON( uint32_t*Copy_u32_TON_microSec) {



	if (State == 2) {

		State = 0;

		*Copy_u32_TON_microSec = (TIMEON );



	}
	else {
		/*nothing*/
	}


}

void UltraSonic_INIT(void) {

	HAL_NVIC_EnableIRQ(TIM1_CC_IRQn) ;
	HAL_TIM_IC_Start_IT(&htim1 ,TIM_CHANNEL_1) ;

}

void UltraSonic_Get_Distance(float*Distance_CM) {


	uint32_t TON_microSec =0 ;


	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	vTaskDelay(3);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
	vTaskDelay(10);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
	// Sense ECHO to measure distance

	ICU_VoidGet_TON( &TON_microSec) ;
	*Distance_CM = (velocity * TON_microSec/10000.0 )/ 2.0;    // CENTIMETER

}
