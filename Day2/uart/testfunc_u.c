#include "stm32f1xx_hal.h"
#include "testfunc_u.h"
#include "test_uart.h"
#include <stdio.h>
#include <string.h>

uint8_t bLedOn = PIN_SET_OFF;
uint8_t bStartBlink = PIN_SET_OFF;
uint8_t bStartShift = PIN_SET_OFF;
uint8_t bStartShiftRound = PIN_SET_OFF;
uint8_t blinkNum = 0;
uint8_t directLeft = 1;
uint8_t bBlock = 0;


extern UART_HandleTypeDef  huart3;

char inputString[256];
char outputString[256];
int outStrCount=0;
  
void UartTestStart(void)
{




}

void doUartTest2(void)
{


}


//---------------------------------------------------------