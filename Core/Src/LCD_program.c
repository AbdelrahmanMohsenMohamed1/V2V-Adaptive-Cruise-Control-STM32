/*
 * LED_program.c
 *
 * Created: 4/1/2024 11:52:44 PM
 *  Author: Ali Azzouz & Tarek Alaa
 * Description: Source file for LCD interface functions
 */ 

//include LIB files
#include "BIT_MATH.h"

// Include the GPIO header file
#include "stm32f1xx_hal.h"

//include LCD Header files
#include "LCD_interface.h"
#include "LCD_config.h"

void LCD_voidInit(void)
{
	/* 4-bit initialization */
	HAL_Init(); // Initialize hardware abstraction layer
	HAL_Delay(40); // Delay for 40 milliseconds
	LCD_voidWriteCmd(0x33); // Send command 0x33 to LCD
	LCD_voidWriteCmd(0x32); // Send command 0x32 to LCD
	LCD_voidWriteCmd(0x28); // Send command 0x28 to LCD
	HAL_Delay(1); // Delay for 1 millisecond
	LCD_voidWriteCmd(0x0E); // Send command 0x0E to LCD
	HAL_Delay(1); // Delay for 1 millisecond
	LCD_voidWriteCmd(0x01); // Send command 0x01 to LCD
	HAL_Delay(2); // Delay for 2 milliseconds
}

void LCD_voidWriteCmd(uint8_t copy_u8Cmd)
{
	// Set RS and RW pins for command mode
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_RS_Pin, GPIO_PIN_SET); /* command */
	
	// Write high nibble of command to data pins
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin4, (GET_BIT(copy_u8Cmd, 4)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin5, (GET_BIT(copy_u8Cmd, 5)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin6, (GET_BIT(copy_u8Cmd, 6)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin7, (GET_BIT(copy_u8Cmd, 7)));

	// Enable pulse
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_RESET); // Disable enable pin
	HAL_Delay(5);

	// Write low nibble of command to data pins
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin4, (GET_BIT(copy_u8Cmd, 0)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin5, (GET_BIT(copy_u8Cmd, 1)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin6, (GET_BIT(copy_u8Cmd, 2)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin7, (GET_BIT(copy_u8Cmd, 3)));

	// Enable pulse
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_RESET); // Disable enable pin
	HAL_Delay(5);
}

void LCD_voidWriteChar(uint8_t copy_u8Char)
{
	// Set RS pin for data mode
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_RS_Pin, GPIO_PIN_SET); /* data */
	
	// Write high nibble of character to data pins
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin7, (GET_BIT(copy_u8Char, 7)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin6, (GET_BIT(copy_u8Char, 6)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin5, (GET_BIT(copy_u8Char, 5)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin4, (GET_BIT(copy_u8Char, 4)));

	// Enable pulse
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_RESET); // Disable enable pin
	HAL_Delay(5);

	// Write low nibble of character to data pins
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin7, (GET_BIT(copy_u8Char, 3)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin6, (GET_BIT(copy_u8Char, 2)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin5, (GET_BIT(copy_u8Char, 1)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin4, (GET_BIT(copy_u8Char, 0)));

	// Enable pulse
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_RESET); // Disable enable pin
	HAL_Delay(5);
}

void LCD_voidClearScreen(void)
{
	LCD_voidWriteCmd(0x01); // Send clear screen command
	HAL_Delay(2); // Delay for 2 milliseconds
}

void LCD_voidSetCursor(uint8_t copy_u8Row, uint8_t copy_u8Col)
{
	LCD_voidWriteCmd((128 + (copy_u8Row * 64) + copy_u8Col)); // Set cursor position
}

void LCD_voidWriteString(const uint8_t *copy_cu8pString)
{
	uint8_t local_u8i = 0;
	do
	{
		LCD_voidWriteChar(copy_cu8pString[local_u8i]); // Write each character in the string
		local_u8i++;
	} while (copy_cu8pString[local_u8i] != '\0'); // Continue until null terminator is reached
}

void LCD_voidWriteNum(uint32_t copy_u32Num)
{
	if (0 == copy_u32Num)
	{
		LCD_voidWriteChar((copy_u32Num % 10) + 48); // Write digit as character
	}
	else
	{
		uint32_t reverse = 1;
		while (copy_u32Num != 0)
		{
			reverse = (reverse * 10) + (copy_u32Num % 10);
			copy_u32Num /= 10;
		}
		while (reverse != 1)
		{
			LCD_voidWriteChar((reverse % 10) + 48); // Write digit as character
			reverse /= 10;
		}
	}
}

void LCD_voidCreateChar(uint8_t copy_u8AddressData, uint8_t *copy_u8charArr)
{
	LCD_voidWriteCmd(0x40 | (copy_u8AddressData * 8)); // Set CGRAM address
	for (uint8_t i = 0; i < 8; i++)
	{
		LCD_voidWriteChar(copy_u8charArr[i]); // Write custom character data
	}
	LCD_voidWriteCmd(0x80); // Return to DDRAM address
}
