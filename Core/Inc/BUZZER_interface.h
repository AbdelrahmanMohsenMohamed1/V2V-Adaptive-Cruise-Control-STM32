/*
 * LED_interface.h
 *
 * Created: 4/1/2024 11:52:44 PM
 *  Author: Ali Azzouz & Tarek Alaa
 *	Description: Header file for BUZZER interface functions
 */ 

#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_

/* 
 * Function: BUZZER_voidTurnOn
 * -------------------------
 * Turns on the specified BUZZER.
 *
 * Parameters: void
 */
void BUZZER_voidTurnOn(void);

/* 
 * Function: BUZZER_voidTurnOff
 * -------------------------
 * Turns off the specified BUZZER.
 *
 * Parameters: void
 */
void BUZZER_voidTurnOff(void);

/* 
 * Function: BUZZER_voidToggle
 * -------------------------
 * Toggles the specified BUZZER.
 *
 * Parameters: void
 */
void BUZZER_voidToggle(void);

#endif /* BUZZER_INTERFACE_H_ */