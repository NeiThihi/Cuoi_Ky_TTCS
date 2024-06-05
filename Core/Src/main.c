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
#include "liquidcrystal_i2c.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "DHT.h"
#include <stdlib.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define	LOW									0
#define	HIGH								1
#define BTN_PRESS							1
/* USER CODE END PD */

// khai bao led red
#define ledred_Pin GPIO_PIN_1
#define ledred_GPIO_Port GPIOA
// khai bao led green
#define ledblue_Pin GPIO_PIN_4
#define ledblue_GPIO_Port GPIOA
// khai bao led blue
#define ledgreen_Pin GPIO_PIN_0
#define ledgreen_GPIO_Port GPIOB
//L298N_in1
#define L298N_in1_Pin GPIO_PIN_5
#define L298N_in1_GPIO_Port GPIOB
// L2988N_in2
#define L298N_in2_Pin GPIO_PIN_7
#define L298N_in2_GPIO_Port GPIOB
/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  *
  */

void Read_DataDHT(void);
DHT_DataTypedef DHT11_Data;
float temp, humi;
int i = 0;
long last = 0;

char status[3];
uint8_t nhiet_do;
uint8_t ok = 0;
uint8_t flag = 1;
uint8_t co = 1;

// ham dieu khien ngat
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_GPIO_TogglePin(L298N_in1_GPIO_Port,L298N_in1_Pin);
	HAL_GPIO_WritePin(L298N_in2_GPIO_Port,L298N_in2_Pin, LOW);
	HAL_GPIO_TogglePin(ledred_GPIO_Port,ledred_Pin);
	HAL_GPIO_TogglePin(ledgreen_GPIO_Port,ledgreen_Pin);
	HAL_GPIO_TogglePin(ledblue_GPIO_Port,ledblue_Pin);
	//HAL_GPIO_TogglePin(coi_GPIO_Port,coi_Pin);
//	for(int i = 0; i <=1; i++){

//	}
	if(ok == 0){
		ok = 1;
	}else{
		ok = 0;
	}

	if(flag==0){
		flag = 1;
	}else{
		flag = 0;
	}

	if(co==0){
			co = 1;
		}else{
			co = 0;
		}
}

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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  HD44780_Init(2);
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
   HD44780_Clear();
   HD44780_SetCursor(2,0);
   HD44780_PrintStr("HELLO C.A.T");
   HD44780_SetCursor(1,1);
   HD44780_PrintStr("Chao_moi_nguoi");


  while (1)
  {

	  Read_DataDHT();


	  if(nhiet_do >=35 && flag == 1){
	          HAL_GPIO_WritePin(ledred_GPIO_Port,ledred_Pin, HIGH);
	          HAL_GPIO_WritePin(ledgreen_GPIO_Port,ledgreen_Pin, HIGH);
	          HAL_GPIO_WritePin(ledblue_GPIO_Port,ledblue_Pin, HIGH);
	          HAL_GPIO_WritePin(L298N_in1_GPIO_Port,L298N_in1_Pin, HIGH);
	          HAL_GPIO_WritePin(L298N_in2_GPIO_Port,L298N_in2_Pin, LOW);
	          ok = 1;
	  }else if (nhiet_do < 35 && co == 1){
	      HAL_GPIO_WritePin(ledred_GPIO_Port,ledred_Pin, LOW);
	      HAL_GPIO_WritePin(ledgreen_GPIO_Port,ledgreen_Pin, LOW);
	      HAL_GPIO_WritePin(ledblue_GPIO_Port,ledblue_Pin, LOW);
	      HAL_GPIO_WritePin(L298N_in1_GPIO_Port,L298N_in1_Pin, LOW);
	      HAL_GPIO_WritePin(L298N_in2_GPIO_Port,L298N_in2_Pin, LOW);
	      ok = 0;
	         }

    if(ok == 1){
    	status[0]='O';
    	status[1]='N';
    	status[2]=' ';

    }else if(ok == 0){
    	status[0]='O';
    	status[1]='F';
    	status[2]='F';
    }
    HD44780_SetCursor(13,0);
    HD44780_PrintStr(status);

  }


  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */

void Read_DataDHT(void){

	DHT_GetData(&DHT11_Data);
	temp = DHT11_Data.Temperature;
	humi = DHT11_Data.Humidity;

	last = HAL_GetTick();

	nhiet_do = temp;
	float T  = temp;
	float H  = humi;
	char DHT11[20];
	while(1){
		if(HAL_GetTick() - last >= 1200){

					i++;
					//in ra lcd nhiet do
					   HD44780_Clear();
					   HD44780_SetCursor(1,0);
					   HD44780_PrintStr("C.A.T");
					   HD44780_SetCursor(9,0);
					   HD44780_PrintStr("Fan:");

					   // doi so thanh ky tu
					   	gcvt(T, 2, DHT11);
					   // in nhiet do ra lcd
					   	HD44780_SetCursor(0,1);
					   	HD44780_PrintStr("TEMP: ");
					   	HD44780_SetCursor(5,1);
					   	HD44780_PrintStr(DHT11);

					   	// doi so thanh ky tu
					   	gcvt(H, 2, DHT11);
					   	// in nhiet do ra lcd
					   	HD44780_SetCursor(9,1);
					   	HD44780_PrintStr("Humi: ");
					   	HD44780_SetCursor(14,1);
					   	HD44780_PrintStr(DHT11);

					last = HAL_GetTick();
					break;
				}
	}
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */ // nt nhan user
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */ // led board
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA10 */ // nut nhan A10
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // ledred A1
    GPIO_InitStruct.Pin = ledred_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(ledred_GPIO_Port, &GPIO_InitStruct);

    // ledgreen A4
   GPIO_InitStruct.Pin = ledgreen_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
   HAL_GPIO_Init(ledgreen_GPIO_Port, &GPIO_InitStruct);
   // ledblue A4
   GPIO_InitStruct.Pin = ledblue_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
   HAL_GPIO_Init(ledblue_GPIO_Port, &GPIO_InitStruct);
   // L2998N_in1
   GPIO_InitStruct.Pin = L298N_in1_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
   HAL_GPIO_Init(L298N_in1_GPIO_Port, &GPIO_InitStruct);
   // L28N_in2
   GPIO_InitStruct.Pin = L298N_in2_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
   HAL_GPIO_Init(L298N_in2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
