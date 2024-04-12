/*
 * BUZZER_program.c
 *
 * Created: 4/1/2024 11:52:44 PM
 *  Author: Ali Azzouz & Tarek Alaa
 * Description: Source file for BUZZER interface functions
 */ 

//include LIB files
#include "BIT_MATH.h"

// Include the GPIO header file
#include "stm32f1xx_hal.h"

//include BUZZER Header files
#include "BUZZER_interface.h"
#include "BUZZER_config.h"

void BUZZER_voidTurnOn(void)
{
	// Set GPIO pin to high state to turn on BUZZER
	HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
}
void BUZZER_voidTurnOff(void)
{
	// Set GPIO pin to low state to turn off LED
	HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}
void BUZZER_voidToggle(void)
{
	// Toggle GPIO pins to change LED state
	HAL_GPIO_TogglePin(BUZZER_PORT, BUZZER_PIN);
}
