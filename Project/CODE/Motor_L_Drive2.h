/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Motor_L_Drive2.h
**     Project   : Project
**     Processor : MC9S12C32MFA25
**     Component : BitIO
**     Version   : Component 02.075, Driver 03.15, CPU db: 2.87.402
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 3/19/2019, 7:45 PM
**     Abstract  :
**         This component "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Methods of this component are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings  :
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       44            |  PM1_TxCAN
**             ----------------------------------------------------
**
**         Port name                   : M
**
**         Bit number (in port)        : 1
**         Bit mask of the port        : $0002
**
**         Initial direction           : Output (direction can be changed)
**         Safe mode                   : yes
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTM       [$0250]
**         Port control register       : DDRM      [$0252]
**
**         Optimization for            : speed
**     Contents  :
**         SetDir - void Motor_L_Drive2_SetDir(bool Dir);
**         GetVal - bool Motor_L_Drive2_GetVal(void);
**         PutVal - void Motor_L_Drive2_PutVal(bool Val);
**         ClrVal - void Motor_L_Drive2_ClrVal(void);
**         SetVal - void Motor_L_Drive2_SetVal(void);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef Motor_L_Drive2_H_
#define Motor_L_Drive2_H_

/* MODULE Motor_L_Drive2. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma CODE_SEG Motor_L_Drive2_CODE
/*
** ===================================================================
**     Method      :  Motor_L_Drive2_GetVal (component BitIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
#define Motor_L_Drive2_GetVal() ( \
    (bool)((getReg8(PTM) & 0x02U))     /* Return port data */ \
  )

/*
** ===================================================================
**     Method      :  Motor_L_Drive2_PutVal (component BitIO)
**
**     Description :
**         This method writes the new output value.
**           a) direction = Input  : sets the new output value;
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes the value to the
**                                   appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val             - Output value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
**     Returns     : Nothing
** ===================================================================
*/
void Motor_L_Drive2_PutVal(bool Val);

/*
** ===================================================================
**     Method      :  Motor_L_Drive2_ClrVal (component BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**           a) direction = Input  : sets the output value to "0";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "0" to the
**                                   appropriate pin
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define Motor_L_Drive2_ClrVal() ( \
    (void)clrReg8Bits(PTM, 0x02U)      /* PTM1=0x00U */, \
    (Shadow_M &= 0xFDU)                /* Set appropriate bit in shadow variable */ \
  )

/*
** ===================================================================
**     Method      :  Motor_L_Drive2_SetVal (component BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**           a) direction = Input  : sets the output value to "1";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "1" to the
**                                   appropriate pin
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define Motor_L_Drive2_SetVal() ( \
    (void)setReg8Bits(PTM, 0x02U)      /* PTM1=0x01U */, \
    (Shadow_M |= 0x02U)                /* Set appropriate bit in shadow variable */ \
  )

/*
** ===================================================================
**     Method      :  Motor_L_Drive2_SetDir (component BitIO)
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
void Motor_L_Drive2_SetDir(bool Dir);

#pragma CODE_SEG DEFAULT

/* END Motor_L_Drive2. */
#endif /* #ifndef __Motor_L_Drive2_H_ */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
