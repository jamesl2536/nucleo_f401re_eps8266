/*
 * uart.h
 *
 *  Created on: 2018. 7. 22.
 *      Author: Jeong
 */

#ifndef UART_H_
#define UART_H_

#define hWifi    huart1
#define hMonitor huart2

#define QUEUE_BUFFER_LENGTH 1024

typedef struct
{
	int head, tail, data;
	uint8_t Buffer[QUEUE_BUFFER_LENGTH];
}UARTQUEUE, *pUARTQUEUE;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;

extern UARTQUEUE WifiQueue;
extern UARTQUEUE MonitorQueue;

void InitUartQueue(pUARTQUEUE pQueue);
void PutDataToUartQueue(UART_HandleTypeDef *huart, uint8_t data);
void GetDataFromUartQueue(UART_HandleTypeDef *huart);

#endif /* UART_H_ */
