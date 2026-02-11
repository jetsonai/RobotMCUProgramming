
/* USER CODE BEGIN Includes */

#include "CAN_Unit.h"
#include "stm32f1xx_hal_can.h"
#include "PRINTF.h"

extern CAN_HandleTypeDef hcan;

CAN_RxHeaderTypeDef RxMessage;
CAN_TxHeaderTypeDef TxMessage;
CAN_FilterTypeDef sFilterConfig;

uint8_t txData[8]; // send buffer
uint8_t rxData[8]; // recv buffer
uint32_t txMailbox;

volatile uint8_t can1_rx_flag = 0;

void Start_CAN(void)
{
  HAL_CAN_Start(&hcan);
  
  CAN_Filter_Config();
}

void CAN_Filter_Config(void)
{
  sFilterConfig.FilterMaskIdHigh = 0x7F0 << 5;
  sFilterConfig.FilterIdHigh = 0x000; 
  sFilterConfig.FilterMaskIdLow = 0x7F0 << 5;
  sFilterConfig.FilterIdLow = 0x000;  
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;

  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO1;  
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterActivation = ENABLE;
  //##-2- Configure the CAN Filter ###########################################

  HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);
  
  HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO1_MSG_PENDING);


}

uint8_t setTxMessageHeader(uint32_t msg_ID, uint8_t * dataValue)
{
  uint8_t res = 0;
  uint8_t i;






  if(state == HAL_OK)
    res = 1;
  else {
    HAL_CAN_StateTypeDef statetype = HAL_CAN_GetState(&hcan);
    uint32_t err = HAL_CAN_GetError(&hcan);
    PRINTF("FAIL TO SEND TX statetype:%d err:%d\n", statetype, err);
    res = 0;
  }
  
  return res;
}

 void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{


}

uint8_t getRxMessageHeader(uint32_t * msg_ID, uint8_t * dataValue)
{ 
  uint8_t res = can1_rx_flag;



  return res;
}  


/* USER CODE END Includes */