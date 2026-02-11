#ifndef __CAN_PWM_H
#define __CAN_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

  
//void setRevData2Motor(RevMotorData * revData);
void setData4PWM2(uint8_t pulse, uint8_t total_pulse, uint8_t speed, int8_t direction, uint8_t enable, uint16_t position);
void setRxData2Motor(uint8_t * rxData);

void CanToPWMConverter(void);
void SendData4CanToPWM(void);
void SaveLeftWheelData(void);
void SendMultiData4CanToPWM(void);
void InitDriving(void);

void TestSendData4Can(void);
int SendEnc2CAN(uint32_t txMsgID, int32_t enc1, int32_t enc2);

int CanTestDriver(uint8_t testCase);

/* USER CODE END Includes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_PWM_H */