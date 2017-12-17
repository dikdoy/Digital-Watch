#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "hardwareinit.h"
#include "device.h"
#include "stdint.h"

void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOE_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOE, reserve_out3_Pin|reserve_out4_Pin|reserve_out5_Pin|reserve_out6_Pin
	                          |reserve_out7_Pin|reserve_out1_Pin|reserve_out2_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOD, ld4_Pin|ld3_Pin|ld5_Pin|ld6_Pin
	                          |RS_Pin|RW_Pin|E_Pin|reserve_lcd_Pin
	                          |D4_Pin|D5_Pin|D6_Pin|D7_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD4_Pin|LD5_Pin|LD6_Pin
	                          |Buzzer_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pins : reserve_out3_Pin reserve_out4_Pin reserve_out5_Pin reserve_out6_Pin
	                           reserve_out7_Pin reserve_out1_Pin reserve_out2_Pin */
	  GPIO_InitStruct.Pin = reserve_out3_Pin|reserve_out4_Pin|reserve_out5_Pin|reserve_out6_Pin
	                          |reserve_out7_Pin|reserve_out1_Pin|reserve_out2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	  /*Configure GPIO pins : Mode_Pin Advance_Pin Light_Pin Alarm_Pin
	                           reserve_in1_Pin reserve_in2_Pin reserve_in3_Pin reserve_in4_Pin
	                           reserve_in5_Pin */
	  GPIO_InitStruct.Pin = Mode_Pin|Advance_Pin|Light_Pin|Alarm_Pin
	                          |reserve_in1_Pin|reserve_in2_Pin|reserve_in3_Pin|reserve_in4_Pin
	                          |reserve_in5_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	  /*Configure GPIO pins : ld4_Pin ld3_Pin ld5_Pin ld6_Pin
	                           RS_Pin RW_Pin E_Pin reserve_lcd_Pin
	                           D4_Pin D5_Pin D6_Pin D7_Pin */
	  GPIO_InitStruct.Pin = ld4_Pin|ld3_Pin|ld5_Pin|ld6_Pin
	                          |RS_Pin|RW_Pin|E_Pin|reserve_lcd_Pin
	                          |D4_Pin|D5_Pin|D6_Pin|D7_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	  /*Configure GPIO pins : LD3_Pin LD4_Pin LD5_Pin LD6_Pin
	                           Buzzer_Pin */
	  GPIO_InitStruct.Pin = LD3_Pin|LD4_Pin|LD5_Pin|LD6_Pin
	                          |Buzzer_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
