/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : PID.h
**     Project   : Project
**     Processor : MC9S12C32MFA25
**     Component : TimerInt
**     Version   : Component 02.159, Driver 01.20, CPU db: 2.87.402
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 04/16/19, 19:57
**     Abstract  :
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings  :
**         Timer name                  : TIM_Counter (16-bit)
**         Compare name                : TC4
**         Counter shared              : Yes
**
**         High speed mode
**             Prescaler               : divide-by-32
**             Clock                   : 750000 Hz
**           Initial period/frequency
**             Xtal ticks              : 440000
**             microseconds            : 55000
**             milliseconds            : 55
**             seconds (real)          : 0.055
**             Hz                      : 18
**
**         Runtime setting             : none
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : TCNT      [$0044]
**              Mode                   : TIOS      [$0040]
**              Run                    : TSCR1     [$0046]
**              Prescaler              : TSCR2     [$004D]
**
**         Compare registers
**              Compare                : TC4       [$0058]
**
**         Flip-flop registers
**              Mode                   : TCTL1     [$0048]
**     Contents  :
**         Enable  - byte PID_Enable(void);
**         Disable - byte PID_Disable(void);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __PID
#define __PID

/* MODULE PID. */

#include "Cpu.h"

#pragma CODE_SEG PID_CODE


byte PID_Enable(void);
/*
** ===================================================================
**     Method      :  PID_Enable (component TimerInt)
**
**     Description :
**         This method enables the component - it starts the timer.
**         Events may be generated (<DisableEvent>/<EnableEvent>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte PID_Disable(void);
/*
** ===================================================================
**     Method      :  PID_Disable (component TimerInt)
**
**     Description :
**         This method disables the component - it stops the timer. No
**         events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void PID_Interrupt(void);
/*
** ===================================================================
**     Method      :  PID_Interrupt (component TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

#pragma CODE_SEG DEFAULT

/* END PID. */

#endif /* ifndef __PID */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/