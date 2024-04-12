

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"


void ICU_VoidGet_TON( uint32_t*Copy_u32_TON_microSec) ;
void delay (uint16_t time) ;
void UltraSonic_INIT(void) ;
void UltraSonic_Get_Distance(float*Distance_CM) ;
