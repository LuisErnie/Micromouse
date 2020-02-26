/** ###################################################################
**     Filename  : Events.h
**     Project   : Project
**     Processor : MC9S12C32MFA25
**     Component : Events
**     Version   : Driver 01.04
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 3/19/2019, 6:50 PM
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Motor_R_EN.h"
#include "Motor_L_EN.h"
#include "Motor_R_Drive.h"
#include "Motor_L_Drive1.h"
#include "Motor_L_Drive2.h"
#include "Motor_L_Drive4.h"
#include "Motor_L_Drive8.h"
#include "Motor_L_DutyTimer.h"
#include "Motor_R_DutyTimer.h"
#include "MotorR_DriveTimer.h"
#include "MotorL_DriveTimer.h"
#include "PID.h"
#include "ADC.h"
#include "LCD_RS.h"
#include "LCD_EN.h"

#pragma CODE_SEG DEFAULT


void ADC_OnEnd(void);
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

void PID_OnInterrupt(void);
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

void MotorL_DriveTimer_OnInterrupt(void);
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

void MotorR_DriveTimer_OnInterrupt(void);
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

void Motor_R_DutyTimer_OnInterrupt(void);
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

void Motor_L_DutyTimer_OnInterrupt(void);
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

/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
