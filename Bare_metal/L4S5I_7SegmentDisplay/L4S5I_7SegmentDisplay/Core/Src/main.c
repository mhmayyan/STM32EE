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
#include "stm32l4s5xx.h"

void SystemInit(void)
{
#if defined(USER_VECT_TAB_ADDRESS)
  /* Configure the Vector Table location -------------------------------------*/
  SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET;
#endif

  /* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << 20U)|(3UL << 22U));  /* set CP10 and CP11 Full Access */
#endif
}

int main(void)
{
	RCC->AHB2ENR |= 5; // enable GPIOC and GPIOA
	GPIOC->MODER &= ~0xFF; // GPIOC 0-3 output
	GPIOC->MODER |= 0x55; // GPIOC 0-3 output
	GPIOA->MODER &= ~0xFFFF; // GPIOA 0-7 output
	GPIOA->MODER |= 0x5555; // GPIOA 0-3 output
	for(volatile uint32_t rpt=0; rpt<0x7FFFF; rpt++);
	GPIOC->ODR |= 0xF; // turn off all segments
	GPIOA->ODR |= 0xFF; // turn off all segments
	const uint8_t digits[] = {0x3f, 0x30, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
	uint32_t indx=0;

	while (1)
	{
		indx=0;
		for (uint32_t loop = 0; loop < 0xFFF; ++loop) {
			GPIOC->ODR |= 0xF; // turn off all segments
			GPIOC->ODR &= ~(1<<(3-indx)); // turn on only one digit
			GPIOA->ODR |= 0xFF; // turn off all segments
			GPIOA->ODR &= ~digits[indx]; // display digit
			indx = indx==4 ? 0 : indx+1;
			for(volatile uint32_t rpt=0; rpt<0xFF; rpt++);
		}
		indx=0;
		for (uint32_t loop = 0; loop < 0xFFF; ++loop)
		{
			GPIOC->ODR |= 0xF; // turn off all segments
			GPIOC->ODR &= ~(1<<(3-indx)); // turn on only one digit
			GPIOA->ODR |= 0xFF; // turn off all segments
			GPIOA->ODR &= ~digits[indx+4]; // display digit
			indx = indx==4 ? 0 : indx+1;
			for(volatile uint32_t rpt=0; rpt<0xFF; rpt++);
		}
	}
}


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
