#include "stm32f1xx_hal.h"
#include "test_uart.h"
#include <string.h>

extern UART_HandleTypeDef huart3;

#define LENGTH_RX_BUFFER	100

volatile char Rx_Data;

volatile uint8_t uart2Flag;
volatile unsigned char rx_buffer[LENGTH_RX_BUFFER];
volatile unsigned char rx_head=0, rx_tail=0;

void UART_Receive_IT(void)
{
  HAL_UART_Receive_IT(&huart3, (uint8_t *)&Rx_Data, 1);  
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  HAL_UART_Transmit(&huart3, (uint8_t *)&Rx_Data, 1, 100);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
        if( (rx_head+1==rx_tail) || ((rx_head==LENGTH_RX_BUFFER-1) && (rx_tail==0)) )
        {
            volatile char temp = Rx_Data; // rx_buffer[] full, 마지막 수신 문자 버림
        }
        else
        {
            rx_buffer[rx_head] = Rx_Data;
            rx_head = (rx_head==LENGTH_RX_BUFFER-1) ? 0 : rx_head+1;
        }
        HAL_UART_Receive_IT(&huart3, (uint8_t *)&Rx_Data, 1);
    }
}

int  UART_RxCheck(void)
{
	return (rx_head != rx_tail) ? 1 : 0;
}

uint8_t UART_RxChar(void)
{
    unsigned char data;

    while( rx_head==rx_tail );	// 수신 문자가 없음

    data = rx_buffer[rx_tail];
    rx_tail = (rx_tail==LENGTH_RX_BUFFER-1) ? 0 : rx_tail + 1;

    return data;
}

void UART_RxString(uint8_t *RxBuff)
{
    //while (UART_RxCheck())
    char getData=0;
    uint16_t rxCount=0;

    getData = UART_RxChar();
    while (!((getData == '\n') || (getData == '\r')))  // 리턴 확인. 리턴문자가 올때까지 loop
    {
        *RxBuff = getData;
        RxBuff++;
        rxCount++;
        getData = UART_RxChar();

        if(rxCount >= LENGTH_RX_BUFFER-3) 
          break;
    }
    *RxBuff = '\n';
    RxBuff++;
    *RxBuff = '\0'; // 문자열 끝 NULL 추가.
}

//void UART_TxChar(UART_HandleTypeDef *huart, uint8_t txData )
void UART_TxChar(uint8_t txData )
{
  UART_HandleTypeDef *huart = &huart3;
    while((__HAL_UART_GET_FLAG(&huart3, UART_FLAG_TXE)) == RESET); // 전송 가능 확인
    huart->Instance->DR = txData;
}

//void UART_TxString(UART_HandleTypeDef *huart, uint8_t *pData)
void UART_TxString(uint8_t *pData)
{
    while(*pData)
    {
         UART_TxChar(*pData++);
    }
}
