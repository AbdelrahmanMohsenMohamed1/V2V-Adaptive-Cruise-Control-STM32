/*
 * LCD_program.c
 *
 * Created: 4/1/2024 11:52:44 PM
 *  Author: Ali Azzouz & Tarek Alaa
 * Description: Source file for LCD interface functions
 */ 

//include LIB files
#include "BIT_MATH.h"

// Include the GPIO header file
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

//include LCD Header files
#include "LCD_interface.h"
#include "LCD_config.h"

void LCD_voidInit(void)
{
	// 4 bit initialisation

	//Wait for power-on initialization time (greater than 40ms)
	//vTaskDelay(50);

	//Send 0x33 command sequence for 4-bit mode
	LCD_voidWriteCommand(0x33);
	vTaskDelay(10);

	//Send 0x32 command sequence for 4-bit mode
	LCD_voidWriteCommand(0x32);
	vTaskDelay(10);

	//Set interface to 4-bit mode and 2 lines, 5x8 font
	LCD_voidWriteCommand(0x28);
	vTaskDelay(1);

	//Display on, cursor off, blink off
	LCD_voidWriteCommand(0x0C);
	vTaskDelay(1);

	//Entry mode set: increment cursor position, no display shift
	LCD_voidWriteCommand(0x06);
	vTaskDelay(1);

	//Clear the display
	LCD_voidWriteCommand(0x01);
	vTaskDelay(2);

	//Set cursor to the beginning of the first line
	LCD_voidWriteCommand(0x80);
}

void LCD_voidWriteCommand(uint8_t copy_u8Cmd)
{
	// Write high nibble of command to data pins
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin7, (GET_BIT(copy_u8Cmd, 7)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin6, (GET_BIT(copy_u8Cmd, 6)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin5, (GET_BIT(copy_u8Cmd, 5)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin4, (GET_BIT(copy_u8Cmd, 4)));

	// Set RS pin for command mode
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_RS_Pin, GPIO_PIN_RESET); /* command */

	// Enable pulse
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_SET);
	vTaskDelay(2);
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_RESET); // Disable enable pin
	vTaskDelay(2);

	// Write low nibble of command to data pins
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin7, (GET_BIT(copy_u8Cmd, 3)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin6, (GET_BIT(copy_u8Cmd, 2)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin5, (GET_BIT(copy_u8Cmd, 1)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin4, (GET_BIT(copy_u8Cmd, 0)));

	// Set RS pin for command mode
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_RS_Pin, GPIO_PIN_RESET); /* command */

	// Enable pulse
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_SET);
	vTaskDelay(2);
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_RESET); // Disable enable pin
	vTaskDelay(2);

	vTaskDelay(1);
}

void LCD_voidWriteData(uint8_t copy_u8Char)
{
	// Write high nibble of character to data pins
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin7, (GET_BIT(copy_u8Char, 7)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin6, (GET_BIT(copy_u8Char, 6)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin5, (GET_BIT(copy_u8Char, 5)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin4, (GET_BIT(copy_u8Char, 4)));

	// Set RS pin for data mode
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_RS_Pin, GPIO_PIN_SET);

	// Enable pulse
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_SET);
	vTaskDelay(2);
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_RESET); // Disable enable pin
	vTaskDelay(2);

	// Write low nibble of character to data pins
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin7, (GET_BIT(copy_u8Char, 3)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin6, (GET_BIT(copy_u8Char, 2)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin5, (GET_BIT(copy_u8Char, 1)));
	HAL_GPIO_WritePin(LCD_Data_Port, LCD_Pin4, (GET_BIT(copy_u8Char, 0)));

	// Set RS pin for data mode
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_RS_Pin, GPIO_PIN_SET);

	// Enable pulse
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_SET);
	vTaskDelay(2);
	HAL_GPIO_WritePin(LCD_Ctrl_Port, LCD_EN_Pin, GPIO_PIN_RESET); // Disable enable pin
	vTaskDelay(2);

	vTaskDelay(1);
}

void LCD_voidClear(void)
{
	LCD_voidWriteCommand(0x01); // Send clear screen command
	vTaskDelay(2); // Delay for 2 milliseconds
}

void LCD_voidSetCursor(uint8_t copy_u8Row, uint8_t copy_u8Col)
{
	LCD_voidWriteCommand((128 + (copy_u8Row * 64) + copy_u8Col)); // Set cursor position
}

void LCD_voidWriteString(const uint8_t *copy_cu8pString)
{
	uint8_t local_u8i = 0;
	do
	{
		LCD_voidWriteData(copy_cu8pString[local_u8i]); // Write each character in the string
		local_u8i++;
	} while (copy_cu8pString[local_u8i] != '\0'); // Continue until null terminator is reached
}

void LCD_voidWriteNum(uint32_t copy_u32Num)
{
	if (0 == copy_u32Num)
	{
		LCD_voidWriteData((copy_u32Num % 10) + 48); // Write digit as character
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
			LCD_voidWriteData((reverse % 10) + 48); // Write digit as character
			reverse /= 10;
		}
	}
}

void LCD_voidCreateChar(uint8_t copy_u8AddressData, uint8_t *copy_u8charArr)
{
	LCD_voidWriteCommand(0x40 | (copy_u8AddressData * 8)); // Set CGRAM address
	for (uint8_t i = 0; i < 8; i++)
	{
		LCD_voidWriteData(copy_u8charArr[i]); // Write custom character data
	}
	LCD_voidWriteCommand(0x80); // Return to DDRAM address
}
