/*
 * HC05_Bluetooth.c
 *
 *  Created on: Apr 1, 2024
 *      Author: Abdelrahman
 */



/* Includes ------------------------------------------------------------------*/
#include "HC05_Bluetooth.h"

/* Private variables ---------------------------------------------------------*/
uint8_t RxData[20] = {0}; /**< Buffer to store received data */
static void (*PRV_PfuncUARTCallBack)(void) = NULL; /**< Pointer to function for UART callback */

/* Functions -----------------------------------------------------------------*/

/**
  * @brief  Initialize HC-05 module.
  * @param  Copy_enumHC05_Mode: HC05 mode (HC05_Pol or HC05_Int)
  * @retval HAL_StatusTypeDef: HAL status
  */
HAL_StatusTypeDef H_HC05_Init(HC05_Mode_t Copy_enumHC05_Mode)
{
    HAL_StatusTypeDef Local_enumRetValue = HAL_OK;

    switch(Copy_enumHC05_Mode)
    {
    case HC05_Pol:
        /* Polling mode */
        Local_enumRetValue = HAL_UART_Receive(&HC05_UART_PORT, &RxData[0], HC05_RecCharNum, 200);
        if(Local_enumRetValue != HAL_OK)
        {
            Local_enumRetValue = HAL_ERROR;
        }
        break;

    case HC05_Int:
        /* Interrupt mode */
        Local_enumRetValue = HAL_UART_Receive_IT(&HC05_UART_PORT, &RxData[0], HC05_RecCharNum);
        if(Local_enumRetValue != HAL_OK)
        {
            Local_enumRetValue = HAL_ERROR;
        }
        break;

    default:
        /* Invalid mode */
        break;
    }

    return Local_enumRetValue;
}

/**
  * @brief  Receive from HC-05 module (Polling mode).
  * @param  Copy_u8_Char: Pointer to store received character
  * @retval HAL_StatusTypeDef: HAL status
  */
HAL_StatusTypeDef H_HC05_Recieve_Polling(uint8_t* Copy_u8_Char)
{
    HAL_StatusTypeDef Local_enumRetValue = HAL_OK;
    uint8_t Local_u8Counter = 0;

    Local_enumRetValue = HAL_UART_Receive(&HC05_UART_PORT, &RxData[0], HC05_RecCharNum, 100);
    if(Local_enumRetValue != HAL_OK)
    {
        Local_enumRetValue = HAL_ERROR;
    }
    else
    {
        /* Copy received characters to the buffer */
        for(Local_u8Counter = 0; Local_u8Counter < HC05_RecCharNum; Local_u8Counter++)
        {
            Copy_u8_Char[Local_u8Counter] = RxData[Local_u8Counter];
        }
    }

    return Local_enumRetValue;
}

/**
  * @brief  Receive from HC-05 module (Interrupt mode).
  * @param  Copy_u8_Char: Pointer to store received character
  * @retval HAL_StatusTypeDef: HAL status
  */
HAL_StatusTypeDef H_HC05_Recieve_Interrupt(uint8_t* Copy_u8_Char)
{
    HAL_StatusTypeDef Local_enumRetValue = HAL_OK;

    Local_enumRetValue = HAL_UART_Receive_IT(&HC05_UART_PORT, &RxData[0], HC05_RecCharNum);
    if(Local_enumRetValue != HAL_OK)
    {
        Local_enumRetValue = HAL_ERROR;
    }

    return Local_enumRetValue;
}

/**
  * @brief  Set callback function for UART interrupt.
  * @param  copy_Pfunc: Pointer to callback function
  * @retval HAL_StatusTypeDef: HAL status
  */
HAL_StatusTypeDef H_HC05_voidSetCallBack(void (*copy_Pfunc)(void))
{
    HAL_StatusTypeDef Local_enumRetValue = HAL_OK;

    if(copy_Pfunc != NULL)
    {
        PRV_PfuncUARTCallBack = copy_Pfunc;
    }
    else
    {
        Local_enumRetValue = HAL_ERROR;
    }

    return Local_enumRetValue;
}

/**
  * @brief  Callback function for UART Rx complete interrupt.
  * @param  huart: Pointer to UART handle
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        /* Re-enable interrupt receive */
        HAL_UART_Receive_IT(&HC05_UART_PORT, &RxData[0], HC05_RecCharNum);
    }
}
