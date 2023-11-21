/*
 * uart.c
 *
 *  Created on: 2018. 7. 22.
 *      Author: Jeong
 */

#include "stm32f4xx.h"

#include "uart.h"

UARTQUEUE WifiQueue;
UARTQUEUE MonitorQueue;

void InitUartQueue(pUARTQUEUE pQueue)
{
	pQueue->data = pQueue->head = pQueue->tail = 0;
}

void PutDataToUartQueue(UART_HandleTypeDef *huart, uint8_t data)
{
	pUARTQUEUE pQueue = (huart->Instance == USART1 ? &WifiQueue:&MonitorQueue);
	if (pQueue->data == QUEUE_BUFFER_LENGTH)
		GetDataFromUartQueue(huart);
	pQueue->Buffer[pQueue->head++] = data;
	if (pQueue->head == QUEUE_BUFFER_LENGTH) pQueue->head = 0;
	pQueue->data++;
}

void GetDataFromUartQueue(UART_HandleTypeDef *huart)
{
	UART_HandleTypeDef *dst = (huart->Instance == USART1 ? &hMonitor:&hWifi);
	pUARTQUEUE pQueue = (huart->Instance == USART1 ? &WifiQueue:&MonitorQueue);
	if (HAL_UART_Transmit(dst, pQueue->Buffer + pQueue->tail, 1, 3000) != HAL_OK)
	{
	    Error_Handler();
	}
	pQueue->tail++;
	if (pQueue->tail == QUEUE_BUFFER_LENGTH) pQueue->tail = 0;
	pQueue->data--;
	HAL_Delay(1);
}

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart6, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
		   __io_putchar( *ptr++ );
	return len;
}
