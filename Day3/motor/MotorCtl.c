
/* USER CODE BEGIN Includes */

#include <stdlib.h>
#include "MotorCtl.h"
#include "stm32f1xx_hal.h"
#include "PRINTF.h"

#define LEFTMOTOR  0
#define RIGHTMOTOR 1

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
//gear ratio 1:298, encoder pulse : 7ppr
const double ratio = 360./298./14.;
double Kp = 30.;

void SetMotorDir(uint8_t mnum, GPIO_PinState bSet);
void MX_TIM_SetPulse(uint8_t mnum, uint8_t dir, uint32_t pulse);
void SetPulse4FanPWM(uint8_t mnum, uint8_t dir, uint32_t pulseVal);
void doMotor(uint8_t mnum, uint8_t dir, uint32_t vel);

//모터 제어 명령
void doMotor(uint8_t mnum, uint8_t dir, uint32_t vel)
{


}


void MX_TIM_SetPulse(uint8_t mnum, uint8_t dir, uint32_t pulse)
{
  TIM_OC_InitTypeDef sConfigOC;

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = pulse;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  
  if(mnum == 0) {
    if(dir == 1) {
      HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
    } else if(dir == 0) {
      HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
    }
  }  
  else if(mnum == 1) {
    if(dir == 1) {
      HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
    } else if(dir == 0) {
      HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
    }
  }
}

//PWM 설정
void SetPulse4FanPWM(uint8_t mnum, uint8_t dir, uint32_t pulseVal)
{    








}

uint8_t GetReduceSpeed(uint8_t mnum, float scale)
{
  return (uint8_t)(emotor[mnum].motorSpeed * scale);
}

uint32_t CaltotalPulse4Pos(uint16_t degree)
{
  uint32_t tpp = (uint32_t)( degree / 360.0 * Pulse4Revolutions);
  return tpp;
}

void setData4PWMMotors(uint8_t mnum, uint8_t pulse, uint8_t speed, int8_t direction, uint8_t enable)
{
  emotor[mnum].motorDir = direction;
  emotor[mnum].motorSpeed = pulse;
  emotor[mnum].delaytime = speed;

  if(enable == 1 )
    emotor[mnum].motorSpeed = 0;

#if 0  //20201221 kate
  emotor[mnum].encoderPos = 0;
  emotor[mnum].curRevolution = 0;
  emotor[mnum].bStop = 0;
#endif
}

uint8_t getDelayTime()
{
  return emotor[0].delaytime;
}

void RunPWM(uint8_t mnum)
{

    doMotor(mnum, emotor[mnum].motorDir, emotor[mnum].motorSpeed);
}

