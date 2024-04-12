/*
 * LED_program.c
 *
 * Created: 4/1/2024 11:52:44 PM
 *  Author: Ali Azzouz & Tarek Alaa
 * Description: Source file for LED interface functions
 */ 

//include LIB files
#include "BIT_MATH.h"

// Include the GPIO header file
#include "stm32f1xx_hal.h"

//include LED Header files
#include "LED_interface.h"
#include "LED_config.h"

void LED_voidTurnOn(uint8_t copy_u8LedNum)
{
	// Set GPIO pin to high state to turn on LED
	HAL_GPIO_WritePin(GPIOA, copy_u8LedNum, GPIO_PIN_SET);
}
void LED_voidTurnOff(uint8_t copy_u8LedNum)
{
	// Set GPIO pin to low state to turn off LED
	HAL_GPIO_WritePin(GPIOA, copy_u8LedNum, GPIO_PIN_RESET);
}
void LED_voidToggle(uint8_t copy_u8LedNum)
{
	// Toggle GPIO pins to change LED state
	HAL_GPIO_TogglePin(GPIOA, copy_u8LedNum);
}