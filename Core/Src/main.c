/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "HC05_Bluetooth.h"
#include "LCD_interface.h"
#include "BUZZER_interface.h"
#include "LED_interface.h"
#include "DC_MOT.h"
#include "UltraSonic_interface_.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MOTOR_MAX_SPEED 100
#define MOTOR_MIN_SPEED 0
#define ENGINE_ON       1
#define ENGINE_OFF      0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART3_UART_Init(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void BLE_Read_Task    (void  * argument);
void V2V_Task         (void  * argument);
void ACC_Task         (void  * argument);
void Action_Task      (void  * argument);
void Display_Task     (void  * argument);

EventGroupHandle_t EG_Action = NULL;
EventBits_t        EG_Value  = 0;
#define EG_ENGINE_START    (1<<0)
#define EG_ENGINE_STOP     (1<<1)
#define EG_SPEED_UP        (1<<2)
#define EG_SPEED_DOWN      (1<<3)

EventGroupHandle_t EG_V2V = NULL;
EventBits_t        EG_V2VValue  = 0;
#define EG_DIS_LESS_10     (1<<0)
#define EG_DIS_LESS_5      (1<<1)

int8_t Duty = 0;
uint8_t ACC_State = 0;
uint8_t User_Control = 0;
uint8_t Engine_State = 0;
float Distance = 0;
uint8_t Counter = 0;
uint8_t u8FlagLess10=1;
uint8_t u8FlagLess5= 1;
uint8_t u8LCDFlagInit=0;
uint8_t u8CLRState=0;

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_TIM1_Init();
	MX_TIM3_Init();
	MX_USART1_UART_Init();
	MX_TIM4_Init();
	MX_USART3_UART_Init();
	/* USER CODE BEGIN 2 */
	EG_Action = xEventGroupCreate();
	EG_V2V = xEventGroupCreate();
	xTaskCreate(BLE_Read_Task, NULL, 100 , NULL , 1 , NULL);
	xTaskCreate(V2V_Task, NULL, 100 , NULL , 2 , NULL);
	xTaskCreate(ACC_Task, NULL, 100 , NULL , 3 , NULL);
	xTaskCreate(Action_Task, NULL, 100 , NULL , 4 , NULL);
	xTaskCreate(Display_Task, NULL, 50 , NULL , 5 , NULL);
	UltraSonic_INIT();
	DC_Motor_Init();

	vTaskStartScheduler();
	//mqBLE = xQueueCreate(4 , 1);
	/* USER CODE END 2 */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of defaultTask */

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* Start scheduler */

	/* We should never get here as control is now taken by the scheduler */
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief TIM1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM1_Init(void)
{

	/* USER CODE BEGIN TIM1_Init 0 */

	/* USER CODE END TIM1_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_IC_InitTypeDef sConfigIC = {0};

	/* USER CODE BEGIN TIM1_Init 1 */

	/* USER CODE END TIM1_Init 1 */
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 64-1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 65535;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
	sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	sConfigIC.ICFilter = 0;
	if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM1_Init 2 */

	/* USER CODE END TIM1_Init 2 */

}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM3_Init(void)
{

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 32-1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 100-1;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */
	HAL_TIM_MspPostInit(&htim3);

}

/**
 * @brief TIM4 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM4_Init(void)
{

	/* USER CODE BEGIN TIM4_Init 0 */

	/* USER CODE END TIM4_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	/* USER CODE BEGIN TIM4_Init 1 */

	/* USER CODE END TIM4_Init 1 */
	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 32-1;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 100-1;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM4_Init 2 */

	/* USER CODE END TIM4_Init 2 */
	HAL_TIM_MspPostInit(&htim4);

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief USART3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART3_UART_Init(void)
{

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 9600;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART3_Init 2 */

	/* USER CODE END USART3_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
			|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_15, GPIO_PIN_RESET);

	/*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA7 */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
			|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB1 PB15 */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void Display_Task     (void  * argument)
{
	while(1)
	{
		if(Engine_State == 1)
		{
			if((Distance < 10.0) && u8CLRState == 0 )
			{
				u8CLRState = 1;
				LCD_voidClear();
			}
			else if(Distance > 10.0)
			{
				u8CLRState = 0;
			}
			if(u8LCDFlagInit == 0)
			{
				LCD_voidInit();
				u8LCDFlagInit = 1;
			}
			// Display ( Distance & Duty & ACC State On LCD)
			LCD_voidSetCursor(0, 0);
			LCD_voidWriteString((uint8_t*)"Speed:");
			LCD_voidWriteNum(Duty);
			LCD_voidWriteString((uint8_t*)"%");
			LCD_voidSetCursor(1, 9);
			LCD_voidWriteString((uint8_t*)"ACC:");
			if(ACC_State==1)
			{
				LCD_voidWriteString((uint8_t*)" ON");
			}
			else
			{
				LCD_voidWriteString((uint8_t*)"OFF");
			}
			LCD_voidSetCursor(1, 0);
			LCD_voidWriteString((uint8_t*)"Dist:");
			LCD_voidWriteNum(Distance);



		}
		vTaskDelay(500);
	}
}
void BLE_Read_Task    (void  * argument)
{
	HAL_StatusTypeDef RetValue = HAL_ERROR;
	uint8_t BLE_Rer_Arr[4]={0};
	while(1)
	{
		RetValue =  H_HC05_Recieve_Polling  (&BLE_Rer_Arr[0]);
		if(RetValue == HAL_OK)
		{
			switch(BLE_Rer_Arr[0])
			{
			case 'S' :
				switch(BLE_Rer_Arr[1])
				{
				case '1':
					xEventGroupSetBits(EG_Action,EG_SPEED_UP);
					break;
				case '0':
					xEventGroupSetBits(EG_Action,EG_SPEED_DOWN);
					break;
				}
				break;

				case 'E' :

					switch(BLE_Rer_Arr[1])
					{
					case '1':
						xEventGroupSetBits(EG_Action,EG_ENGINE_START );
						break;
					case '0':
						xEventGroupSetBits(EG_Action,EG_ENGINE_STOP );
						break;
					}
					break;
			}
		}
		else
		{

		}
		vTaskDelay(10);
	}
}

void V2V_Task (void  * argument)
{
	uint8_t Local_8uLess10Mssg[4] = {'1','0','\r','\n'};
	uint8_t Local_8uLess5Mssg [4] = {'0','5','\r','\n'};
	while(1)
	{
		EG_V2VValue = xEventGroupWaitBits(EG_V2V,
				( EG_DIS_LESS_10 | EG_DIS_LESS_5) ,
				1, // Auto Clear
				0, // Or Between bits not wait for all of the events
				portMAX_DELAY);
		if(EG_V2VValue & EG_DIS_LESS_10)
		{
			if(u8FlagLess10 == 1)
			{
				Counter++;
				HAL_UART_Transmit(&huart1, Local_8uLess10Mssg, 4, 100);
				u8FlagLess10=0;
			}
		}
		if(EG_V2VValue & EG_DIS_LESS_5)
		{
			if(u8FlagLess5 == 1)
			{
				HAL_UART_Transmit(&huart1, Local_8uLess5Mssg, 4, 100);
				Counter--;
				u8FlagLess5=0;
			}
		}
	}
}
void ACC_Task         (void  * argument)
{
	/*
	 * 1) Read UltaSonic Distance
	 * 2) if Distance > 10cm --> ACC Off and go waiting state
	 * 3) if Distance < 10cm --> ACC on (Regulate the speed & change ACC Status & Yellow Led ON)
	 * 4) if Distance < 5cm  --> Stop The Car & Red Led ON & Buzzer ON
	 */
	while(1)
	{
		if(ENGINE_ON == Engine_State)
		{
			UltraSonic_Get_Distance(&Distance);
			if(Distance > 10 )
			{
				ACC_State = 0;
				u8FlagLess10 = 1;
				u8FlagLess5 =  1;
			}
			else if(Distance <= 10.0 && Distance > 5.0)
			{
				ACC_State = 1;
				Duty = 20;
				DC_Motor_SetSpeed(Duty);
				u8FlagLess5 =  1;
				xEventGroupSetBits(EG_V2V, EG_DIS_LESS_10);
			}
			else if(Distance < 5.0)
			{
				ACC_State = 1;
				Duty = MOTOR_MIN_SPEED;
				DC_Motor_SetSpeed(Duty);
				xEventGroupSetBits(EG_V2V, EG_DIS_LESS_5);
			}
			else
			{

			}
		}
		vTaskDelay(250);
	}
}
void Action_Task      (void  * argument)
{
	while(1)
	{
		EG_Value = xEventGroupWaitBits(EG_Action,
				(EG_ENGINE_START | EG_ENGINE_STOP | EG_SPEED_UP | EG_SPEED_DOWN) ,
				1, // Auto Clear
				0, // Or Between bits not wait for all of the events
				portMAX_DELAY);

		if(EG_Value & EG_ENGINE_START)
		{
			// Start Motor with Duty 50%
			DC_Motor_Init();
			Engine_State = ENGINE_ON;
		}
		if(EG_Value & EG_ENGINE_STOP)
		{
			// Stop Motor Duty 0%
			Duty =0;
			DC_Motor_STOP();
			Engine_State = ENGINE_OFF;
		}
		if(EG_Value & EG_SPEED_UP)
		{
			if(ENGINE_ON == Engine_State)
			{
				Duty+=10;
				if(MOTOR_MAX_SPEED < Duty)
				{
					Duty=MOTOR_MAX_SPEED;
					DC_Motor_SetSpeed(Duty);
				}
				else
				{
					DC_Motor_SetSpeed(Duty);
				}
			}
		}
		if(EG_Value & EG_SPEED_DOWN)
		{
			if(ENGINE_ON == Engine_State)
			{
				Duty-=10;
				if(MOTOR_MIN_SPEED > Duty)
				{
					Duty = MOTOR_MIN_SPEED;
					DC_Motor_SetSpeed(Duty);
				}
				else
				{
					DC_Motor_SetSpeed(Duty);
				}
			}
		}
	}
}

/* USER CODE END 4 */


/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
