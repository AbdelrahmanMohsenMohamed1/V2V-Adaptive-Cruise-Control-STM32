
/*
 * LCD_config.h
 *
 * Created: 4/1/2024 11:52:44 PM
 *  Author: Ali Azzouz & Tarek Alaa
 * Description: Configuration file for LCD GPIO pins
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

// Define the ports used for LCD data and control signals
#define LCD_Data_Port 			GPIOA
#define LCD_Ctrl_Port 			GPIOA

// Define the pins used for LCD control signals
#define LCD_RS_Pin				GPIO_PIN_0 // Register Select pin
#define LCD_EN_Pin				GPIO_PIN_1 // Enable pin

// Define the pins used for LCD data signals (4-bit mode)
#define LCD_Pin4   				GPIO_PIN_2 // Data pin 4
#define LCD_Pin5   				GPIO_PIN_3 // Data pin 5
#define LCD_Pin6   				GPIO_PIN_4 // Data pin 6
#define LCD_Pin7   				GPIO_PIN_5 // Data pin 7



#endif /* LCD_CONFIG_H_ */
