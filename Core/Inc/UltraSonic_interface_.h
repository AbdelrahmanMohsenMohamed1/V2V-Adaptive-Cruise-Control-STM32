

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"

// Function to measure the time duration of a pulse (Time Of Flight)
void ICU_VoidGet_TON( uint32_t*Copy_u32_TON_microSec) ;

// Function to introduce a delay in microseconds
void delay (uint16_t time) ;

// Function to initialize the Ultrasonic sensor
void UltraSonic_INIT(void) ;
// Function to get the distance measured by the Ultrasonic sensor in centimeters
void UltraSonic_Get_Distance(float*Distance_CM) ;


