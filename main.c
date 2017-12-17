/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "device.h"
#include "hardwareinit.h"
#include "uart.h"
#include "seos.h"
#include "lcd.h"

char tampung [100];
int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	SCH_init(250);
	lcd_init();

	while(1){
		lcd_gotoxy(0,1);lcd_putstr(tampung);
		if(HAL_GPIO_ReadPin(Light_GPIO_Port,Light_Pin)==GPIO_PIN_RESET)
		{
			HAL_GPIO_WritePin(reserve_out1_GPIO_Port,reserve_out1_Pin,GPIO_PIN_SET);
			HAL_Delay(3000);
			HAL_GPIO_WritePin(reserve_out1_GPIO_Port,reserve_out1_Pin,GPIO_PIN_RESET);
		}
		/* User code here      -----------------------------------------------*/
		//		HAL_GPIO_TogglePin(led0_GPIO_Port,led0_Pin);
		//		HAL_Delay(1000);
		/* User code here      -----------------------------------------------*/
	}
}

