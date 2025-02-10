/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */
  /* initially, turn on NS green, EW red, and ped_red. Turn off all other LEDs */
  /*all other LEDs were turned OFF by MX_GPIO_Init()*/
  HAL_GPIO_WritePin(GPIOC, NS_G_Pin|EW_R_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(PedRed_GPIO_Port, PedRed_Pin, GPIO_PIN_SET);
  uint32_t timeTracker = HAL_GetTick()+20000, waitingPeriod=0, debouncePressPedSw=0, debounceReleasePedSw=0;
  typedef enum {
    s0,
    s1,
    s2,
    s3,
	s4,
    s5,
    s6,
    s7,
	s8,
	s9,
  } stateName;
  typedef struct {
    stateName state;
    uint32_t waitTime; 
  } stateDef;
  stateDef states[]={
  {s0,15e3},
  {s1,3e3},
  {s2,3e3},
  {s3,15e3},
  {s4,3e3},
  {s5,15e3},
  {s6,3e3},
  {s7,3e3},
  {s8,15e3},
  {s9,3e3}
  };
  stateName stateIndx = s0;
  typedef enum {
  REQUISTED,
  UNREQUISTED,
  } pedStatus;
  pedStatus pedSwitch=UNREQUISTED;
  bool acceptNewPedReq=1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	/******************************************************/
    /******************* read pedButton *******************/
    if(acceptNewPedReq && !debouncePressPedSw && !HAL_GPIO_ReadPin(PedButton_GPIO_Port, PedButton_Pin))
    {
      //debounce
    	debouncePressPedSw = HAL_GetTick();
    }
    if(debouncePressPedSw && HAL_GetTick() - debouncePressPedSw > 50)
    {
    	// if button is still pressed
    	if(!HAL_GPIO_ReadPin(PedButton_GPIO_Port, PedButton_Pin))
    	{
    		pedSwitch = REQUISTED;
    		acceptNewPedReq=0;
    	}
    	debouncePressPedSw=0;
    }
    // PedSw must be released for a debounce period
    if(!acceptNewPedReq && HAL_GPIO_ReadPin(PedButton_GPIO_Port, PedButton_Pin))
    {
    	if(!debounceReleasePedSw) debounceReleasePedSw =  HAL_GetTick();
    	if(HAL_GetTick() - debounceReleasePedSw > 50)
    	{
    		acceptNewPedReq = 1;
    		debounceReleasePedSw=0;
    	}
    }
    /******************************************************/
    /****************** change state **********************/
    if(HAL_GetTick() - timeTracker > waitingPeriod)
    {
    	timeTracker = HAL_GetTick();
      switch(stateIndx)
      {
        case s0: // NSG
          // turn off all other LEDs
          HAL_GPIO_WritePin(PedGreen_GPIO_Port, PedGreen_Pin, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(GPIOC,NS_G_Pin|NS_Y_Pin|NS_R_Pin|EW_G_Pin|EW_Y_Pin|EW_R_Pin, GPIO_PIN_RESET);
          // turn ON NS_G_Pin, EW_R_Pin, and PedRed_Pin
          HAL_GPIO_WritePin(GPIOC,
        		  NS_G_Pin
//				  |
//				  NS_Y_Pin
//				  |
//				  NS_R_Pin
//				  |
//				  EW_G_Pin
//				  |
//				  EW_Y_Pin
				  |
				  EW_R_Pin
        		  , GPIO_PIN_SET);
          HAL_GPIO_WritePin(PedRed_GPIO_Port, PedRed_Pin, GPIO_PIN_SET);
          // set current waiting period
          waitingPeriod = states[stateIndx].waitTime;
          // set next state
          stateIndx=s1; // next
          break;
        case s1: // NSY
          // turn off all other LEDs
            HAL_GPIO_WritePin(PedGreen_GPIO_Port, PedGreen_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOC,NS_G_Pin|NS_Y_Pin|NS_R_Pin|EW_G_Pin|EW_Y_Pin|EW_R_Pin, GPIO_PIN_RESET);
          // turn ON NS_G_Pin, EW_R_Pin, and PedRed_Pin
            HAL_GPIO_WritePin(GPIOC,
//          		  NS_G_Pin
//  				  |
  				  NS_Y_Pin
//  				  |
//  				  NS_R_Pin
//  				  |
//  				  EW_G_Pin
//  				  |
//  				  EW_Y_Pin
  				  |
  				  EW_R_Pin
          		  , GPIO_PIN_SET);
          HAL_GPIO_WritePin(PedRed_GPIO_Port, PedRed_Pin, GPIO_PIN_SET);
          // set current waiting period
          waitingPeriod = states[stateIndx].waitTime;
          // set next state
          stateIndx=s2; // next
          break;
        case s2: // NSR
          // turn off all other LEDs
            HAL_GPIO_WritePin(PedGreen_GPIO_Port, PedGreen_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOC,NS_G_Pin|NS_Y_Pin|NS_R_Pin|EW_G_Pin|EW_Y_Pin|EW_R_Pin, GPIO_PIN_RESET);
          // turn ON NS_G_Pin, EW_R_Pin, and PedRed_Pin
            HAL_GPIO_WritePin(GPIOC,
//          		  NS_G_Pin
//  				  |
//  				  NS_Y_Pin
//  				  |
  				  NS_R_Pin
//  				  |
//  				  EW_G_Pin
//  				  |
//  				  EW_Y_Pin
  				  |
  				  EW_R_Pin
          		  , GPIO_PIN_SET);
            HAL_GPIO_WritePin(PedRed_GPIO_Port, PedRed_Pin, GPIO_PIN_SET);
          // set current waiting period
          waitingPeriod = states[stateIndx].waitTime;
          // set next state
          // check ped switch
          if(pedSwitch == REQUISTED) {stateIndx=s3;} // next
          else {stateIndx=s5;} // next
          break;
        case s5: // EWG
            // turn off all other LEDs
              HAL_GPIO_WritePin(PedGreen_GPIO_Port, PedGreen_Pin, GPIO_PIN_RESET);
              HAL_GPIO_WritePin(GPIOC,NS_G_Pin|NS_Y_Pin|NS_R_Pin|EW_G_Pin|EW_Y_Pin|EW_R_Pin, GPIO_PIN_RESET);
            // turn ON NS_G_Pin, EW_R_Pin, and PedRed_Pin
              HAL_GPIO_WritePin(GPIOC,
  //          		  NS_G_Pin
  //  				  |
  //  				  NS_Y_Pin
  //  				  |
    				  NS_R_Pin
    				  |
    				  EW_G_Pin
  //  				  |
  //  				  EW_Y_Pin
//    				  |
//    				  EW_R_Pin
            		  , GPIO_PIN_SET);
              HAL_GPIO_WritePin(PedRed_GPIO_Port, PedRed_Pin, GPIO_PIN_SET);
          // set current waiting period
          waitingPeriod = states[stateIndx].waitTime;
          // set next state
          stateIndx=s6; // next
          break;
        case s6: // EWY
            // turn off all other LEDs
              HAL_GPIO_WritePin(PedGreen_GPIO_Port, PedGreen_Pin, GPIO_PIN_RESET);
              HAL_GPIO_WritePin(GPIOC,NS_G_Pin|NS_Y_Pin|NS_R_Pin|EW_G_Pin|EW_Y_Pin|EW_R_Pin, GPIO_PIN_RESET);
            // turn ON NS_G_Pin, EW_R_Pin, and PedRed_Pin
              HAL_GPIO_WritePin(GPIOC,
  //          		  NS_G_Pin
  //  				  |
  //  				  NS_Y_Pin
  //  				  |
    				  NS_R_Pin
//    				  |
//    				  EW_G_Pin
    				  |
    				  EW_Y_Pin
//    				  |
//    				  EW_R_Pin
            		  , GPIO_PIN_SET);
              HAL_GPIO_WritePin(PedRed_GPIO_Port, PedRed_Pin, GPIO_PIN_SET);
		  // set current waiting period
		  waitingPeriod = states[stateIndx].waitTime;
			// set next state
			stateIndx=s7; // next
          break;
        case s7: // EWR
            // turn off all other LEDs
              HAL_GPIO_WritePin(PedGreen_GPIO_Port, PedGreen_Pin, GPIO_PIN_RESET);
              HAL_GPIO_WritePin(GPIOC,NS_G_Pin|NS_Y_Pin|NS_R_Pin|EW_G_Pin|EW_Y_Pin|EW_R_Pin, GPIO_PIN_RESET);
            // turn ON NS_G_Pin, EW_R_Pin, and PedRed_Pin
              HAL_GPIO_WritePin(GPIOC,
  //          		  NS_G_Pin
  //  				  |
  //  				  NS_Y_Pin
  //  				  |
    				  NS_R_Pin
//    				  |
//    				  EW_G_Pin
//    				  |
//    				  EW_Y_Pin
    				  |
    				  EW_R_Pin
            		  , GPIO_PIN_SET);
              HAL_GPIO_WritePin(PedRed_GPIO_Port, PedRed_Pin, GPIO_PIN_SET);
          // set current waiting period
          waitingPeriod = states[stateIndx].waitTime;
		  // set next state
		  // check ped switch
		  if(pedSwitch == REQUISTED) {stateIndx=s8;} // next
		  else {stateIndx=s0;} // next
          break;
        case s3: // PedG
        case s8: // PedG
            // turn off all other LEDs
            HAL_GPIO_WritePin(PedRed_GPIO_Port, PedRed_Pin, GPIO_PIN_RESET);
              HAL_GPIO_WritePin(GPIOC,NS_G_Pin|NS_Y_Pin|NS_R_Pin|EW_G_Pin|EW_Y_Pin|EW_R_Pin, GPIO_PIN_RESET);
            // turn ON NS_G_Pin, EW_R_Pin, and PedRed_Pin
              HAL_GPIO_WritePin(GPIOC,
  //          		  NS_G_Pin
  //  				  |
  //  				  NS_Y_Pin
  //  				  |
    				  NS_R_Pin
//    				  |
//    				  EW_G_Pin
//    				  |
//    				  EW_Y_Pin
    				  |
    				  EW_R_Pin
            		  , GPIO_PIN_SET);
              HAL_GPIO_WritePin(PedGreen_GPIO_Port, PedGreen_Pin, GPIO_PIN_SET);
          // set current waiting period
          waitingPeriod = states[stateIndx].waitTime;
          // set next state
          stateIndx = stateIndx==s3 ? s4 : s9;
          pedSwitch=UNREQUISTED;
          break;
        case s4: // All red
        case s9: // All red
            // turn off all other LEDs
              HAL_GPIO_WritePin(PedGreen_GPIO_Port, PedGreen_Pin, GPIO_PIN_RESET);
              HAL_GPIO_WritePin(GPIOC,NS_G_Pin|NS_Y_Pin|NS_R_Pin|EW_G_Pin|EW_Y_Pin|EW_R_Pin, GPIO_PIN_RESET);
            // turn ON NS_G_Pin, EW_R_Pin, and PedRed_Pin
              HAL_GPIO_WritePin(GPIOC,
  //          		  NS_G_Pin
  //  				  |
  //  				  NS_Y_Pin
  //  				  |
    				  NS_R_Pin
//    				  |
//    				  EW_G_Pin
//    				  |
//    				  EW_Y_Pin
    				  |
    				  EW_R_Pin
            		  , GPIO_PIN_SET);
              HAL_GPIO_WritePin(PedRed_GPIO_Port, PedRed_Pin, GPIO_PIN_SET);
          // set current waiting period
          waitingPeriod = states[stateIndx].waitTime;
		  // set next state
//          stateIndx=s0;
          stateIndx = stateIndx==s9 ? s0 : s5;
          break;
        default:
            break;
      }
    }
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

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, NS_G_Pin|NS_Y_Pin|NS_R_Pin|EW_G_Pin
                          |EW_Y_Pin|EW_R_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PedRed_GPIO_Port, PedRed_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PedGreen_GPIO_Port, PedGreen_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PedButton_Pin */
  GPIO_InitStruct.Pin = PedButton_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PedButton_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : NS_G_Pin NS_Y_Pin NS_R_Pin EW_G_Pin
                           EW_Y_Pin EW_R_Pin */
  GPIO_InitStruct.Pin = NS_G_Pin|NS_Y_Pin|NS_R_Pin|EW_G_Pin
                          |EW_Y_Pin|EW_R_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PedRed_Pin */
  GPIO_InitStruct.Pin = PedRed_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PedRed_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PedGreen_Pin */
  GPIO_InitStruct.Pin = PedGreen_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PedGreen_GPIO_Port, &GPIO_InitStruct);

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
