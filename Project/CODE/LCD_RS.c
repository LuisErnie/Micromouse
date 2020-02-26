/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : LCD_RS.c
**     Project   : Project
**     Processor : MC9S12C32MFA25
**     Component : BitIO
**     Version   : Component 02.075, Driver 03.15, CPU db: 2.87.402
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 04/09/19, 14:59
**     Abstract  :
**         This component "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Note: This component is set to work in Output direction only.
**         Methods of this component are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings  :
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       26            |  PA0
**             ----------------------------------------------------
**
**         Port name                   : A
**
**         Bit number (in port)        : 0
**         Bit mask of the port        : $0001
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PORTA     [$0000]
**         Port control register       : DDRA      [$0002]
**
**         Optimization for            : speed
**     Contents  :
**         GetVal - bool LCD_RS_GetVal(void);
**         PutVal - void LCD_RS_PutVal(bool Val);
**         ClrVal - void LCD_RS_ClrVal(void);
**         SetVal - void LCD_RS_SetVal(void);
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE LCD_RS. */

#include "LCD_RS.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"

#pragma DATA_SEG LCD_RS_DATA           /* Select data segment "LCD_RS_DATA" */
#pragma CODE_SEG LCD_RS_CODE
#pragma CONST_SEG LCD_RS_CONST         /* Constant section for this module */
/*
** ===================================================================
**     Method      :  LCD_RS_GetVal (component BitIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**         Note: This component is set to work in Output direction only.
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
/*
bool LCD_RS_GetVal(void)

**  This method is implemented as a macro. See LCD_RS.h file.  **
*/

/*
** ===================================================================
**     Method      :  LCD_RS_PutVal (component BitIO)
**
**     Description :
**         This method writes the new output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val             - Output value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
**     Returns     : Nothing
** ===================================================================
*/
void LCD_RS_PutVal(bool Val)
{
  if (Val) {
    setReg8Bits(PORTA, 0x01U);         /* BIT0=0x01U */
  } else { /* !Val */
    clrReg8Bits(PORTA, 0x01U);         /* BIT0=0x00U */
  } /* !Val */
}

/*
** ===================================================================
**     Method      :  LCD_RS_ClrVal (component BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void LCD_RS_ClrVal(void)

**  This method is implemented as a macro. See LCD_RS.h file.  **
*/

/*
** ===================================================================
**     Method      :  LCD_RS_SetVal (component BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void LCD_RS_SetVal(void)

**  This method is implemented as a macro. See LCD_RS.h file.  **
*/


/* END LCD_RS. */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/