/*
 * LED_interface.h
 *
 * Created: 4/1/2024 11:52:44 PM
 *  Author: Ali Azzouz & Tarek Alaa
 *	Description: Header file for LED interface functions
 */ 

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/* 
 * Function: LED_voidTurnOn
 * -------------------------
 * Turns on the specified LED.
 *
 * Parameters: copy_u8LedNum: The number of the LED to turn on.
 */
void LED_voidTurnOn(uint8_t copy_u8LedNum);

/* 
 * Function: LED_voidTurnOff
 * -------------------------
 * Turns off the specified LED.
 *
 * Parameters: copy_u8LedNum: The number of the LED to turn off.
 */
void LED_voidTurnOff(uint8_t copy_u8LedNum);

/* 
 * Function: LED_voidToggle
 * -------------------------
 * Toggles the specified LED.
 *
 * Parameters: copy_u8LedNum: The number of the LED to toggle.
 */
void LED_voidToggle(uint8_t copy_u8LedNum);

#endif /* LED_INTERFACE_H_ */