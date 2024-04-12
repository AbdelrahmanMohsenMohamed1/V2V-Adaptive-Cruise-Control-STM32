/*
 * LED_config.h
 *
 * Created: 4/1/2024 11:52:44 PM
 *  Author: Ali Azzouz & Tarek Alaa
 * Description: Configuration file for LED GPIO pins
 */ 

#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

/* Pin assignments for LEDS */
#define RIGHT_LED_PIN   GPIO_PIN_6
#define LEFT_LED_PIN    GPIO_PIN_7

/* Port assignments for LEDS */
#define RIGHT_LED_PORT  GPIOA
#define LEFT_LED_PORT   GPIOA

#endif /* LED_INTERFACE_H_ */