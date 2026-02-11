#ifndef __ENC_MOTOR_H
#define __ENC_MOTOR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#define DEBUG

#define FORWARD         0
#define BACKWARD        1
#define CHANGE_DIR      2
#define INCREASE        3
#define DECREASE        4
#define FORWARD_STOP    5
#define INCREASE_BACK   6
#define DECREASE_BACK 7
#define NICE_STOP     8
  
#define LEFTMOTOR  0
#define RIGHTMOTOR 1
  
#define CAN_ENC_OFFSET 2147483647
  
typedef struct __RevMotorData {
  uint8_t pulse;
  uint8_t speed;
  uint8_t direction;
  uint8_t enable; 
} RevMotorData;    

typedef struct __MotorData {
  uint32_t delaytime;
  uint8_t bStop;
  uint32_t motorSpeed; 
  uint8_t motorDir;
} MotorData;

extern void setData4PWMMotors(uint8_t mnum, uint8_t pulse, uint8_t speed, int8_t direction, uint8_t enable);
extern uint8_t getDelayTime();
extern uint8_t GetReduceSpeed(uint8_t mnum, float scale);

extern void RunPWM(uint8_t mnum);

extern MotorData emotor[2];

#ifdef __cplusplus
}
#endif

#endif /* __ENC_MOTOR_H */