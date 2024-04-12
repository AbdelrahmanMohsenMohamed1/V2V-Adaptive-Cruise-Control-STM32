/*
 * HC05_Bluetooth.h
 *
 *  Created on: Apr 1, 2024
 *      Author: Abdelrahman
 */

#ifndef INC_HC05_BLUETOOTH_H_
#define INC_HC05_BLUETOOTH_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
    HC05_Pol,    /*!< HC-05 module in polling mode */
    HC05_Int     /*!< HC-05 module in interrupt mode */
} HC05_Mode_t;

/* Exported constants --------------------------------------------------------*/
extern UART_HandleTypeDef huart1;
#define HC05_UART_PORT    huart1 /*!< UART peripheral used for HC-05 communication */
#define HC05_RecCharNum   4      /*!< Number of characters to receive */

/* Exported functions prototypes ---------------------------------------------*/

/**
  * @brief  Initializes the HC-05 module.
  * @param  Copy_enumHC05_Mode: Mode of operation (HC05_Pol or HC05_Int).
  * @retval HAL_StatusTypeDef: HAL status.
  */
HAL_StatusTypeDef H_HC05_Init(HC05_Mode_t Copy_enumHC05_Mode);

/**
  * @brief  Receives data from HC-05 module using polling method.
  * @param  Copy_u8_Char: Pointer to store received character.
  * @retval HAL_StatusTypeDef: HAL status.
  */
HAL_StatusTypeDef H_HC05_Recieve_Polling(uint8_t *Copy_u8_Char);

/**
  * @brief  Receives data from HC-05 module using interrupt method.
  * @param  Copy_u8_Char: Pointer to store received character.
  * @retval HAL_StatusTypeDef: HAL status.
  */
HAL_StatusTypeDef H_HC05_Recieve_Interrupt(uint8_t *Copy_u8_Char);

/**
  * @brief  Sets callback function for timer TIM0.
  * @param  copy_Pfunc: Pointer to callback function.
  * @retval HAL_StatusTypeDef: HAL status.
  */
HAL_StatusTypeDef TIM0_voidSetCallBack(void (*copy_Pfunc)(void));

#endif /* INC_HC05_BLUETOOTH_H_ */
