/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Motor_L_EN.h
**     Project   : Project
**     Processor : MC9S12C32MFA25
**     Component : BitsIO
**     Version   : Component 02.102, Driver 03.14, CPU db: 2.87.402
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 3/19/2019, 7:45 PM
**     Abstract  :
**         This component "BitsIO" implements a multi-bit input/output.
**         It uses selected pins of one 1-bit to 8-bit port.
**     Settings  :
**         Port name                   : T
**
**         Bit mask of the port        : $0003
**         Number of bits/pins         : 2
**         Single bit numbers          : 0 to 1
**         Values range                : 0 to 3
**
**         Initial direction           : Output (direction can be changed)
**         Safe mode                   : yes
**         Initial output value        : 0 = 000H
**         Initial pull option         : off
**
**         Port data register          : PTT       [$0240]
**         Port control register       : DDRT      [$0242]
**
**             ----------------------------------------------------
**                   Bit     |   Pin   |   Name
**             ----------------------------------------------------
**                    0      |    1    |   PT0_PWM0_IOC0
**                    1      |    2    |   PT1_PWM1_IOC1
**             ----------------------------------------------------
**
**         Optimization for            : speed
**     Contents  :
**         GetDir - bool Motor_L_EN_GetDir(void);
**         SetDir - void Motor_L_EN_SetDir(bool Dir);
**         GetVal - byte Motor_L_EN_GetVal(void);
**         PutVal - void Motor_L_EN_PutVal(byte Val);
**         GetBit - bool Motor_L_EN_GetBit(byte Bit);
**         PutBit - void Motor_L_EN_PutBit(byte Bit, bool Val);
**         SetBit - void Motor_L_EN_SetBit(byte Bit);
**         ClrBit - void Motor_L_EN_ClrBit(byte Bit);
**         NegBit - void Motor_L_EN_NegBit(byte Bit);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef Motor_L_EN_H_
#define Motor_L_EN_H_

/* MODULE Motor_L_EN. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma CODE_SEG Motor_L_EN_CODE
/*
** ===================================================================
**     Method      :  Motor_L_EN_GetVal (component BitsIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pins and returns it
**           b) direction = Output : returns the last written value
**     Parameters  : None
**     Returns     :
**         ---        - Input value (0 to 3)
** ===================================================================
*/
byte Motor_L_EN_GetVal(void);

/*
** ===================================================================
**     Method      :  Motor_L_EN_PutVal (component BitsIO)
**
**     Description :
**         This method writes the new output value.
**           a) direction = Input  : sets the new output value;
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes the value to the
**                                   appropriate pins
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val        - Output value (0 to 3)
**     Returns     : Nothing
** ===================================================================
*/
void Motor_L_EN_PutVal(byte Val);

/*
** ===================================================================
**     Method      :  Motor_L_EN_GetBit (component BitsIO)
**
**     Description :
**         This method returns the specified bit of the input value.
**           a) direction = Input  : reads the input value from pins
**                                   and returns the specified bit
**           b) direction = Output : returns the specified bit
**                                   of the last written value
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to read (0 to 1)
**     Returns     :
**         ---        - Value of the specified bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
** ===================================================================
*/
bool Motor_L_EN_GetBit(byte Bit);

/*
** ===================================================================
**     Method      :  Motor_L_EN_PutBit (component BitsIO)
**
**     Description :
**         This method writes the new value to the specified bit
**         of the output value.
**           a) direction = Input  : sets the value of the specified
**                                   bit; this operation will be
**                                   shown on output after the
**                                   direction has been switched to
**                                   output (SetDir(TRUE);)
**           b) direction = Output : directly writes the value of the
**                                   bit to the appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit (0 to 1)
**         Val        - New value of the bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
**     Returns     : Nothing
** ===================================================================
*/
void Motor_L_EN_PutBit(byte Bit, bool Val);

/*
** ===================================================================
**     Method      :  Motor_L_EN_ClrBit (component BitsIO)
**
**     Description :
**         This method clears (sets to zero) the specified bit
**         of the output value.
**         [ It is the same as "PutBit(Bit,FALSE);" ]
**           a) direction = Input  : sets the specified bit to "0";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   beenswitched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "0" to the
**                                   appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to clear (0 to 1)
**     Returns     : Nothing
** ===================================================================
*/
void Motor_L_EN_ClrBit(byte Bit);

/*
** ===================================================================
**     Method      :  Motor_L_EN_SetBit (component BitsIO)
**
**     Description :
**         This method sets (sets to one) the specified bit of the
**         output value.
**         [ It is the same as "PutBit(Bit,TRUE);" ]
**           a) direction = Input  : sets the specified bit to "1";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "1" to the
**                                   appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to set (0 to 1)
**     Returns     : Nothing
** ===================================================================
*/
void Motor_L_EN_SetBit(byte Bit);

/*
** ===================================================================
**     Method      :  Motor_L_EN_NegBit (component BitsIO)
**
**     Description :
**         This method negates (inverts) the specified bit of the
**         output value.
**           a) direction = Input  : inverts the specified bit;
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly inverts the value
**                                   of the appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to invert (0 to 31)
**     Returns     : Nothing
** ===================================================================
*/
void Motor_L_EN_NegBit(byte Bit);

/*
** ===================================================================
**     Method      :  Motor_L_EN_GetDir (component BitsIO)
**
**     Description :
**         This method returns direction of the component.
**     Parameters  : None
**     Returns     :
**         ---        - Direction of the component (FALSE or TRUE)
**                      FALSE = Input, TRUE = Output
** ===================================================================
*/
#define Motor_L_EN_GetDir() ( \
    (bool)((getReg8(DDRT) & 0x01U))    /* Return pin direction, 0==GPI, nonzero==GPO */ \
  )

/*
** ===================================================================
**     Method      :  Motor_L_EN_SetDir (component BitsIO)
**
**     Description :
**         This method sets direction of the component.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Dir        - Direction to set (FALSE or TRUE)
**                      FALSE = Input, TRUE = Output
**     Returns     : Nothing
** ===================================================================
*/
void Motor_L_EN_SetDir(bool Dir);

#pragma CODE_SEG DEFAULT

/* END Motor_L_EN. */
#endif /* #ifndef __Motor_L_EN_H_ */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/