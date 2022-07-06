/*
 * UART.c
 *
 *  Created on: Jun 8, 2020
 *      Author: Jeefo
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

void Debug_Send(char* data){
	int size;
	int timeout = 5;
	size = strlen(data);
	HAL_UART_Transmit(&huart3, data, size, timeout);
	//HAL_UART_Transmit_IT(&huart3, data, size);
	//HAL_UART_Receive_IT(&huart1, data, size);
}
