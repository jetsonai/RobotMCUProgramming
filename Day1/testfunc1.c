#include "stm32f1xx_hal.h"
#include "testfunc1.h"
#include <stdio.h>
#include <string.h>

uint8_t TestAppMode = TESTAPP_ONOFF_ALL;
uint8_t bLedOn = PIN_SET_OFF;
uint8_t bStartBlink = PIN_SET_OFF;
uint8_t bStartShift = PIN_SET_OFF;
uint8_t bStartShiftRound = PIN_SET_OFF;
uint8_t blinkNum = 0;
uint8_t directLeft = 1;
uint8_t bBlock = 0;

void BlinkStart(uint8_t bStart);
void printbin(uint8_t input);
void setLedBin(uint8_t input);

void doTurnOnProc(void);
void doTurnOffProc(void);

uint8_t TestLed = 0;
void DoTest1Led(void);
void DoTest2Led(void);

//-----------------------------------------
// # GPIO All LED on/off
void setBtnTest_AllLedOn(void)
{






    HAL_Delay(10);
}

//-------------------------------------------
//-----------------------------------------
// # Blink Test
void BlinkStart(uint8_t bStart)
{





}

void doBlinkTest(void)
{





   HAL_Delay(100);
}

//-----------------------------------------
// # Set Blink Test
void setBlinkTest(void)
{
    uint8_t bBtnOn = ReadButton(TURN_ON_BTN);
    if(bBtnOn == BTN_STATE_ON) {
      if(bStartBlink == PIN_SET_OFF) {
        BlinkStart(PIN_SET_ON);
      }
    }
    uint8_t bBtnOff = ReadButton(TURN_OFF_BTN);
    if(bBtnOff == BTN_STATE_ON) {
      if(bStartBlink == PIN_SET_ON) {
        BlinkStart(PIN_SET_OFF);
      }
    } 
    HAL_Delay(10);
}

//-------------------------------------------
//-------------------------------------------
// # LED Shift Test
uint8_t ledvar = 1;

void printbin(uint8_t input)
{
  int mask;
  for(int i =  7; i >=0 ; i--)
  {
    mask = 1<<i;
    printf("%d", input & mask? 1 : 0);
  }
  printf("\n");
}

void setLedBin(uint8_t input)
{
  int mask;
  setAllLed(PIN_SET_OFF);
  for (int i = 7; i >= 0; i--)
  {
      mask = 1 << i;
      if(input & mask)
        SetLedOn(i, PIN_SET_ON);
  }
}
      
void setLedShiftTest(uint8_t bOn)
{ 
  bStartShift = bOn;
  ledvar = 1;
  if(bStartShift == PIN_SET_OFF)
  {
      setAllLed(PIN_SET_OFF);
  }

}

void doLedShiftTest(void)
{
  if(bStartShift == PIN_SET_ON)
  {
      printf("LED : %d\n", ledvar);
      printbin(ledvar);
      setLedBin(ledvar);
      
      if (ledvar < 128) {
          ledvar <<= 1;
      }  
      else {
           ledvar = 1; 
      }

      HAL_Delay(100);   
  }
}

//-----------------------------------------
// # Set LedShiftTest by ReadButton
void setLedShiftTest_ReadButton(void)
{
    uint8_t bBtnOn = ReadButton(TURN_ON_BTN);
    if(bBtnOn == BTN_STATE_ON) {
      if(bStartShift == PIN_SET_OFF) {
        setLedShiftTest(PIN_SET_ON);
      }
    }
    uint8_t bBtnOff = ReadButton(TURN_OFF_BTN);
    if(bBtnOff == BTN_STATE_ON) {
      if(bStartShift == PIN_SET_ON) {
        setLedShiftTest(PIN_SET_OFF);
      }
    } 
    HAL_Delay(10);
}

//-------------------------------------------

uint8_t ReadButton(uint32_t Btn_Pin)
{
  uint8_t ret = BTN_STATE_OFF;
  switch(Btn_Pin)
  {
  case TURN_ON_BTN:
    ret = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);
    break;
  case TURN_OFF_BTN:
    ret = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
    break;
  }
  //HAL_Delay(100);
   return ret;
}

void SetLedOn(uint32_t LED_Pin, uint8_t bOn )
{
  switch(LED_Pin)
  {
  case 0:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, (GPIO_PinState)bOn);
    break;
  case 1:
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (GPIO_PinState)bOn);
    break;
  case 2:
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (GPIO_PinState)bOn);
    break;
  case 3:
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (GPIO_PinState)bOn);
    break;   
  case 4:
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (GPIO_PinState)bOn);
    break;
  case 5:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, (GPIO_PinState)bOn);
    break;
  case 6:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, (GPIO_PinState)bOn);
    break;
  case 7:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, (GPIO_PinState)bOn);
    break;     
  }
}


void setAllLed(uint8_t bOn)
{
  SetLedOn(0, bOn);
  SetLedOn(1, bOn);
  SetLedOn(2, bOn);
  SetLedOn(3, bOn);
  SetLedOn(4, bOn);
  SetLedOn(5, bOn);
  SetLedOn(6, bOn);
  SetLedOn(7, bOn);
}



//---------------------------------------------------------