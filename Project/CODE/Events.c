/** ###################################################################
**     Filename  : Events.c
**     Project   : Lab_4
**     Processor : MC9S12C32CFA25
**     Component : Events
**     Version   : Driver 01.04
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 2/12/2019, 6:44 PM
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"
int toggle1, toggle2;

extern byte motorSeq[8];
extern int motorL;
extern int motorR;
extern int steps;
extern int dirR;
extern int dirL;
extern byte sensors[3];
extern int error;
extern int Kp, Ki;

/* User includes (#include below this line is not maintained by Processor Expert) */

#pragma CODE_SEG DEFAULT

void Motor_L_WriteBits(byte seq) {
  Motor_L_Drive1_PutVal(seq & 8);
  Motor_L_Drive2_PutVal(seq & 4);
  Motor_L_Drive4_PutVal(seq & 2);
  Motor_L_Drive8_PutVal(seq & 1); 
}

void Motor_R_WriteBits(byte seq) {
  Motor_R_Drive_PutVal(seq); 
}

/*
** ===================================================================
**     Event       :  Motor_R_DutyTimer_OnInterrupt (module Events)
**
**     Component   :  Motor_R_DutyTimer [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Motor_R_DutyTimer_OnInterrupt(void)
{
  /* Write your code here ... */
  if(toggle2){
    Motor_R_WriteBits(0);
    toggle2=0;
  }else{
    Motor_R_WriteBits(motorSeq[motorR]);
    toggle2=1;
  }
}

/*
** ===================================================================
**     Event       :  Motor_L_DutyTimer_OnInterrupt (module Events)
**
**     Component   :  Motor_L_DutyTimer [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Motor_L_DutyTimer_OnInterrupt(void)
{
  /* Write your code here ... */
  if(toggle1){
    Motor_L_WriteBits(0);
    toggle1=0;
  }else{
    Motor_L_WriteBits(motorSeq[motorL]);
    toggle1=1;
  }
}

/*
** ===================================================================
**     Event       :  MotorL_DriveTimer_OnInterrupt (module Events)
**
**     Component   :  MotorL_DriveTimer [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void MotorL_DriveTimer_OnInterrupt(void)
{
  /* Write your code here ... */
  if(dirL==1){   
    motorL = motorL > 7 ? 0 : motorL + 1;
  }
  if(dirL==-1){
    motorL = motorL < 0 ? 7 : motorL - 1;
  }
}

/*
** ===================================================================
**     Event       :  MotorR_DriveTimer_OnInterrupt (module Events)
**
**     Component   :  MotorR_DriveTimer [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void MotorR_DriveTimer_OnInterrupt(void)
{
  /* Write your code here ... */
  if(dirR==1){   
    motorR = motorR > 7 ? 0 : motorR + 1;
  }
  if(dirR==-1){
    motorR = motorR < 0 ? 7 : motorR - 1;
  }
  steps = steps <= 0 ? 0: steps - 1;
}

/*
** ===================================================================
**     Event       :  ADC_OnEnd (module Events)
**
**     Component   :  ADC [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ADC_OnEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  PID_OnInterrupt (module Events)
**
**     Component   :  PID [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PID_OnInterrupt(void)
{
 /* Write your code here ... */
  Kp=50;  //Proportional Gain
  
  //compute error move forward
  if(sensors[0]<30 && sensors[2]<30){    
    error = (sensors[0] - sensors[2])/2;
  }else if(sensors[0]>30){
    error = (20 - sensors[2])/2;
  } else if(sensors[2]>30){
    error = (sensors[0] - 20)/2;
  }
  
  if(error!=0){
    MotorR_DriveTimer_SetPeriodUS(4000-Kp*error);
    MotorL_DriveTimer_SetPeriodUS(4000+Kp*error); 
  }else{
    MotorR_DriveTimer_SetPeriodUS(4000);
    MotorL_DriveTimer_SetPeriodUS(4000);
  } 
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
