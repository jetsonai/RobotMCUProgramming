
/* USER CODE BEGIN Includes */


#include "stm32f1xx_hal.h"

#include "CAN2Motor.h"
#include "CAN_Unit.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "MotorCtl.h"

static uint8_t RunningMode;

#define RUN_DRIVING     10
#define RUN_FCW         11
#define RUN_RCW         12
#define RUN_ERROR       13

#define RXDATA_L_pulse		0
#define RXDATA_L_speed		1
#define RXDATA_L_direction	2
#define RXDATA_L_enable		3
#define RXDATA_R_pulse		4
#define RXDATA_R_speed		5
#define RXDATA_R_direction	6
#define RXDATA_R_enable		7

RevMotorData revDataDec;

#define MSG_ID_LEFT     1
#define MSG_ID_RIGHT     2

void CanToMotorConverter(void);
//void Can2SafetyDriving(void);
//void SendData4CanToPWM(void);
void setRevData2Motor(int motorNum, RevMotorData * revData);

static void convert10(uint32_t hexanum, uint8_t *decnum);
//static void convert16_10(uint32_t hexanum1, uint32_t hexanum2, uint16_t *decnum) ;

void InitDriving(void)
{
  //void setData4PWMMotors(uint8_t mnum, uint8_t pulse, uint8_t speed, int8_t direction, uint8_t enable)
  setData4PWMMotors(LEFTMOTOR, 100, 0, 0, 0);
  setData4PWMMotors(RIGHTMOTOR, 100, 0, 0, 0);
  //setData4PWMMotors(LEFTMOTOR, 100, 10, 1, 1);
  //setData4PWMMotors(RIGHTMOTOR, 100, 10, 1, 1);
  Start_CAN();
  
  RunningMode = RUN_DRIVING;

}

void Can2Driving(void)
{
  uint8_t rxDataValue[8];
  uint32_t rxMsgID;  
  RevMotorData revDataL; 
  RevMotorData revDataR; 
  
  if(getRxMessageHeader( &rxMsgID,rxDataValue) == 1)
  {     
    switch(rxMsgID) 
    {
    case 0x01:       






    break;
      
    default:
      setData4PWMMotors(LEFTMOTOR, 100, 10, 1, 1);
      setData4PWMMotors(RIGHTMOTOR, 100, 10, 1, 1);      
      break;      
    }

  }  
}

void setRevData2Motor(int motorNum, RevMotorData * revData)
{


}


int SendEnc2CAN(uint32_t txMsgID, int32_t enc1, int32_t enc2)
{







}

void CanSendStatus(void)
{
    int32_t left_enc = 0x01;
    int32_t right_enc = 0x01;
    SendEnc2CAN(0x11, left_enc, right_enc);
}

static void convert10(uint32_t hexanum, uint8_t *decnum) {
    int lenv = 2;
    int pos = 0;
    uint16_t tempnum=0;
    char tempv[32];
    
    sprintf(tempv,"%2x", hexanum);  
    
    for(int i = lenv-1; i>=0;i--) {
        int num1 = tempv[i];
        if(num1 >=48 && num1 <=57) { //0~9
            tempnum += (num1-48) * pow(16, pos);
        } else if(num1 >=65 && num1 <=70) { //A~F
            tempnum += (num1-(65-10)) * pow(16, pos);
        } else if(num1 >=97 && num1 <=102) { //a~f
            tempnum += (num1-(97-10)) * pow(16, pos);
        }    
        pos++;
    }  
    *decnum = tempnum;
}



int fillMessage4Data(uint8_t* data, uint8_t pos, float value, float factor)
{
    float fval = value / factor;
    //printf("fillMessage4Data value : %f fator %f from pos %d \n", value, factor, pos);
    
    union endi {
        uint16_t sv;
        uint8_t un[2];
    } ev;

    //Sig1
    uint16_t nval = (uint16_t)fval;
    ev.sv = nval;
    
    data[pos+1] = ev.un[0];
    data[pos] = ev.un[1];

    return 0;
}


/* USER CODE END Includes */