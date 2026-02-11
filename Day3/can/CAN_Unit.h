#ifndef __CAN_UNIT_H
#define __CAN_UNIT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx_hal_can.h"
  
extern CAN_HandleTypeDef hcan;

extern CAN_RxHeaderTypeDef RxMessage;
extern CAN_TxHeaderTypeDef TxMessage;
extern CAN_FilterTypeDef sFilterConfig;

extern uint8_t txData[8]; // send buffer
extern uint8_t rxData[8]; // recv buffer
extern uint32_t txMailbox;

extern volatile uint8_t can1_rx_flag;
  
/* USER CODE END Includes */
extern void Start_CAN(void);
extern void CAN_Filter_Config(void);

//return success : 1, fail : 0
//msg_ID CAN Msg ID
//dataValue : TxData
extern uint8_t setTxMessageHeader(uint32_t msg_ID, uint8_t * dataValue);

//return CAN received: 1, Not : 0
//msg_ID CAN Msg ID
//dataValue : RxData
//extern uint16_t getRxMessageHeader(uint8_t * dataValue);
extern uint8_t getRxMessageHeader(uint32_t * msg_ID, uint8_t * dataValue);

#ifdef __cplusplus
}
#endif

#endif /* __CAN_UNIT_H */