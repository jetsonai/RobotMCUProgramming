#ifndef _UART_TEST
#define _UART_TEST

void UART_Receive_IT(void);
void UART_TxChar(uint8_t txData );
int  UART_RxCheck(void);
void UART_RxString(uint8_t *RxBuff);
//void UART_TxString(UART_HandleTypeDef *huart, uint8_t *pData);
void UART_TxString(uint8_t *pData);

#endif //_UART_TEST