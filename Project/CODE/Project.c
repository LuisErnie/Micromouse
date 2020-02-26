/** ###################################################################
**     Filename  : Project.c
**     Project   : Project
**     Processor : MC9S12C32CFA25
**     Version   : Driver 01.14
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 4/8/2019, 6:44 PM
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Project */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Motor_R_EN.h"
#include "Motor_L_EN.h"
#include "Motor_R_Drive.h"
#include "ADC.h"
#include "LCD_RS.h"
#include "LCD_EN.h"
#include "Motor_L_Drive1.h"
#include "Motor_L_Drive2.h"
#include "Motor_L_Drive2.h"
#include "Motor_L_Drive4.h"
#include "Motor_L_Drive8.h"
#include "Motor_L_DutyTimer.h"
#include "Motor_R_DutyTimer.h"
#include "MotorR_DriveTimer.h"
#include "MotorL_DriveTimer.h"
#include "PID.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include <stdio.h>
#include <stdlib.h>

byte motorSeq[8]={0x01,0x09,0x08,0x0C,0x04,0x06,0x02,0x03};
int motorL =0;
int motorR =0;
int steps =0;
int dirR =0;
int dirL =0;
byte sensors[3];
int walls[6][13];
int distance[6][13];
int yFinal=6, xFinal1=2, xFinal2=3;
int yCurrent=0, xCurrent=0;
int direction = 8;  //default direction facing north
int unitcell = 430;
int unitrotation = 230;
int moveComplete = 0;

int error;
int Kp;


/* User includes (#include below this line is not maintained by Processor Expert) */

/********************************Prototype Functions*********************************/

void initializeLCD();
void writeCom(byte command);
void writeData(byte data);
void clearLCD();
void pollSensors();
void displaySensors();
void displayData();
void displayEnd();
void powerMotors(int power);
void forward(int s);
void backward(int s);
void left();
void right();
void fullturn();
void initializeWalls();
void initializeDistance();
int calculateMinDistance(int i, int j);
void updateWalls();
void nextMove();

/*************************************LCD Functions**********************************/
void initializeLCD(){
  Cpu_Delay100US(160);
  writeCom(0x30);
  Cpu_Delay100US(45);
  writeCom(0x30);
  Cpu_Delay100US(2);
  writeCom(0x30);
  writeCom(0x02);
  writeCom(0x28);
  writeCom(0x0C);
  writeCom(0x01);
  writeCom(0x06);
  Cpu_Delay100US(100);   
}

void writeCom(unsigned char command){
  //send upper nibble
  unsigned char lower = command & 0x0f; //getting lower bits
  LCD_EN_ClrVal(); //sets to 0
  LCD_RS_ClrVal(); //sets to 0
  command = command >> 4; //shifting
  Motor_R_Drive_PutVal(command); 
  LCD_EN_SetVal(); //transmit bits to the LCD     
  LCD_EN_ClrVal();  //toggle enable bit to complete transmission
  //send lower nibble
  Motor_R_Drive_PutVal(lower);
  LCD_EN_SetVal();
  LCD_EN_ClrVal();
  Cpu_Delay100US(100); // delay
}

void writeData(unsigned char command){
  //send upper nibble
  unsigned char lower = command & 0x0F; //getting lower bits
  LCD_EN_ClrVal(); //sets to 0
  LCD_RS_SetVal(); //sets to 1, data is sent to data register, displaying on LCD
  command = command >> 4; //shifting
  Motor_R_Drive_PutVal(command); 
  LCD_EN_SetVal(); //transmit bits to the LCD     
  LCD_EN_ClrVal();  //toggle enable bit to complete transmission
  //send lower nibble
  Motor_R_Drive_PutVal(lower);
  LCD_EN_SetVal();
  LCD_EN_ClrVal();
  Cpu_Delay100US(100); // delay
}

void clearLCD(){
  writeCom(0x01);
}

/**********************************Sensor Functions**********************************/
void pollSensors(){ //sensors values as /10 inch
  int i=0;
  ADC_Measure(TRUE);
  ADC_GetValue8(sensors);
  for(i=0;i<3;i++){
    if(sensors[i]>50){
      sensors[i]=60-sensors[i]*9/25;
    }else{
      sensors[i]=120-sensors[i]*17/10;
    }   
  }
}

//take 100 form ADC as 2.25in for the 7in per side cells
void displaySensors (){
  writeData(sensors[0]/100+48);
  writeData(sensors[0]/10+48);
  writeData(sensors[0]%10+48);
  writeData(0x20);
  writeData(0x20);
  writeData(sensors[2]/100+48);
  writeData(sensors[2]/10+48);
  writeData(sensors[2]%10+48);
  writeCom(0xC0);
  writeData(0x20);
  writeData(0x20);
  writeData(sensors[1]/100+48);
  writeData(sensors[1]/10+48);
  writeData(sensors[1]%10+48);
}

void displayData(){
  //current direction
  if(direction == 1){
    writeData(0x57);
  }else if(direction == 2){
    writeData(0x4E);
  }else if(direction == 4){
    writeData(0x53);
  }else if(direction == 8){
    writeData(0x45);
  }
  writeData(0x20);
  writeData(0x58);  //current x coordinate
  writeData(xCurrent%10+48);
  writeData(0x20);
  writeData(0x59);  //current y coordinate
  writeData(yCurrent/10+48);
  writeData(yCurrent%10+48);  
  writeCom(0xC0);
  writeData(0x44);  //current distance to end of maze
  writeData(distance[xCurrent][yCurrent]/10+48);
  writeData(distance[xCurrent][yCurrent]%10+48);
  writeData(0x20);
  writeData(0x20);
  writeData(0x57);  //current walls on cell  
  writeData(walls[xCurrent][yCurrent]/10+48);
  writeData(walls[xCurrent][yCurrent]%10+48);  
}

void displayEnd(){
  Motor_L_DutyTimer_Disable();
  Motor_R_DutyTimer_Disable();
  MotorR_DriveTimer_Disable();
  MotorL_DriveTimer_Disable();
  powerMotors(0);
  initializeLCD();
  clearLCD();
  writeData(0x20);
  writeData(0x20);
  writeData(0x47);
  writeData(0x41);
  writeData(0x4D);
  writeData(0x45);
  writeData(0x20);
  writeData(0x20);
  writeCom(0xC0);
  writeData(0x20);
  writeData(0x20);
  writeData(0x4F);
  writeData(0x56);
  writeData(0x45);
  writeData(0x52);
  writeData(0x20);
  writeData(0x20);
}


/**********************************Motor Functions***********************************/
void powerMotors(int power){
  if(power==1){
    Motor_R_EN_PutVal(1);
    Motor_L_EN_PutVal(0x03);
  }else{
    Motor_R_EN_PutVal(0);
    Motor_L_EN_PutVal(0x00);
  }
}

void forward(int s){
   steps = s;
   while(steps){
    pollSensors();
    dirR=1;
    dirL=1;
   }
   dirR=0;
   dirL=0;
}

void backward(int s){
   steps = s;
   while(steps){
    pollSensors();
    dirR=-1;
    dirL=-1;
   }
   dirR=0;
   dirL=0;
}

void left(){
   steps = unitrotation;
   while(steps){
    dirR=1;
    dirL=-1;
   }
   dirR=0;
   dirL=0;
}
void right(){
   steps = unitrotation;
   while(steps){
    dirR=-1;
    dirL=1;
   }
   dirR=0;
   dirL=0;
}
void fullturn(){
   steps = unitrotation*2;
   while(steps){
    dirR=1;
    dirL=-1;
   }
   dirR=0;
   dirL=0;
}

/******************************Maze Algorithm Functions******************************/
void initializeWalls(){
  int i=0;
  int j=0;
  for(j=0;j<=yFinal*2;j++){
    for(i=0;i<=(xFinal1+xFinal2);i++){
      walls[i][j] = 0;
      if(i==0){
        walls[i][j] |= 1;
      }
      if(i==xFinal1+xFinal2){
        walls[i][j] |= 8;
      }
      if(j==0){
        walls[i][j] |= 2;
      }
      if(j==yFinal*2){
        walls[i][j] |= 4;
      }
    }
  }
}

void initializeDistance(){
  int i=0;
  int j=0;
  for(j=0;j<=yFinal*2;j++){
    for(i=0;i<=(xFinal1+xFinal2);i++){
      distance[i][j] = 0;
      if(i<=xFinal1 && j<=yFinal){
        distance[i][j] = (xFinal1 + yFinal) - (j + i);
      }
      if(i<=xFinal1 && j>yFinal){
        distance[i][j] = (xFinal1 + j) - (yFinal + i);
      }
      if(i>=xFinal2 && j<=yFinal){
        distance[i][j] = (i + yFinal) - (j + xFinal2);
      }
      if(i>=xFinal2 && j>yFinal){
        distance[i][j] = (i + j) - (yFinal + xFinal2);
      }
    }
  }
}

int calculateMinDistance(int i, int j){
  int minDistance = 255;
  //no walls to the west
  if(!(walls[i][j] & 1)){
    if(distance[i-1][j] < minDistance){
      minDistance = distance[i-1][j];
    }
  }
  //no walls to the north
  if(!(walls[i][j] & 2)){
    if(distance[i][j-1] < minDistance){
      minDistance = distance[i][j-1];
    }
  }
  //no walls to the south
  if(!(walls[i][j] & 4)){
    if(distance[i][j+1] < minDistance){
      minDistance = distance[i][j+1];
    }
  }
  //no walls to the east   
  if(!(walls[i][j] & 8)){
    if(distance[i+1][j] < minDistance){
      minDistance = distance[i+1][j];
    }
  }
  return minDistance;
}

void updateWalls(){
  int newWalls = 0;
  //robot facing west
  if(direction == 1){
    if(sensors[0] < 30){
      newWalls |= 4; // wall to south    
    }
    if(sensors[1] < 30){
      newWalls |= 1;  //wall to the west    
    }
    if(sensors[2] < 30){
      newWalls |= 2;  //wall to the north    
    }
  }
  //robot facing north 
  if(direction ==2){
    if(sensors[0] < 30){
      newWalls |= 1;  //wall to the west    
    }
    if(sensors[1] < 30){
      newWalls |= 2;  //wall to the north    
    }
    if(sensors[2] < 30){
      newWalls |= 8;  //wall to the east    
    }
  }
  //robot facing south
  if(direction == 4){
    if(sensors[0] < 30){
      newWalls |= 8;  //wall to the east    
    }
    if(sensors[1] < 30){
      newWalls |= 4;  // wall to south    
    }
    if(sensors[2] < 30){
      newWalls |= 1;  //wall to the west    
    }
  }
  //robot facing east
  if(direction == 8){
    if(sensors[0] < 30){
      newWalls |= 2;  //wall to the north    
    }
    if(sensors[1] < 30){
      newWalls |= 8;  //wall to the east    
    }
    if(sensors[2] < 30){
      newWalls |= 4;  // wall to south    
    }
  }
  walls[xCurrent][yCurrent] |= newWalls;
}

void nextMove(){
  int minDistance = 0;
  minDistance = calculateMinDistance(xCurrent, yCurrent);
  //robot facing west
  if(direction == 1){
    if(!(walls[xCurrent][yCurrent] & 1) && moveComplete == 0){        
      if(distance[xCurrent-1][yCurrent] == minDistance){  //no walls to the west
        forward(unitcell);
        xCurrent--;
        moveComplete=1;
      }
    }
    if(!(walls[xCurrent][yCurrent] & 2) && moveComplete == 0){
      if(distance[xCurrent][yCurrent-1] == minDistance){  //no walls to the north
        right();
        direction=2;
        moveComplete=1;
      }
    }
    if(!(walls[xCurrent][yCurrent] & 4) && moveComplete == 0){
      if(distance[xCurrent][yCurrent+1] == minDistance){  //no walls to the south
        left();
        direction=4;
        moveComplete=1;
      }
    }
    if(!(walls[xCurrent][yCurrent] & 8) && moveComplete == 0){
      if(distance[xCurrent+1][yCurrent] == minDistance){  //no walls to the east
        fullturn();
        direction=8;
        moveComplete=1;
      }
    }
  }
  //robot facing north 
  else if(direction ==2){
    if(!(walls[xCurrent][yCurrent] & 2) && moveComplete == 0){
      if(distance[xCurrent][yCurrent-1] == minDistance){  //no walls to the north
        forward(unitcell);
        yCurrent--;
        moveComplete=1;
      }
    }
    if(!(walls[xCurrent][yCurrent] & 8) && moveComplete == 0){
      if(distance[xCurrent+1][yCurrent] == minDistance){  //no walls to the east
        right();
        direction=8;
        moveComplete=1;
      }
    }
    if(!(walls[xCurrent][yCurrent] & 1) && moveComplete == 0){
      if(distance[xCurrent-1][yCurrent] == minDistance){  //no walls to the west
        left();
        direction=1;
        moveComplete=1;
      }
    }
    if(!(walls[xCurrent][yCurrent] & 4) && moveComplete == 0){
      if(distance[xCurrent][yCurrent+1] == minDistance){  //no walls to the south
        fullturn();
        direction=4;
        moveComplete=1;
      }
    }  
  }
  //robot facing south
  else if(direction == 4){
    if(!(walls[xCurrent][yCurrent] & 4) && moveComplete == 0){
      if(distance[xCurrent][yCurrent+1] == minDistance){  //no walls to the south
        forward(unitcell);
        yCurrent++;
        moveComplete=1;
      }
    }
    if(!(walls[xCurrent][yCurrent] & 1) && moveComplete == 0){
      if(distance[xCurrent-1][yCurrent] == minDistance){  //no walls to the west
        right();
        direction=1;
        moveComplete=1;
      }
    }
    if(!(walls[xCurrent][yCurrent] & 8) && moveComplete == 0){
      if(distance[xCurrent+1][yCurrent] == minDistance){  //no walls to the east
        left();
        direction=8;
        moveComplete=1;
      }
    }
    if(!(walls[xCurrent][yCurrent] & 2)  && moveComplete == 0){
      if(distance[xCurrent][yCurrent-1] == minDistance){  //no walls to the north
        fullturn();
        direction=2;
        moveComplete=1;
      }
    } 
  }
  //robot facing east
  else if(direction == 8){
    if(!(walls[xCurrent][yCurrent] & 8) && moveComplete == 0){
      if(distance[xCurrent+1][yCurrent] == minDistance){  //no walls to the east
        forward(unitcell);
        xCurrent++;
        moveComplete=1;
      }
    }
    if(!(walls[xCurrent][yCurrent] & 4) && moveComplete == 0){
      if(distance[xCurrent][yCurrent+1] == minDistance){  //no walls to the south
        right();
        direction=4;
        moveComplete=1;
      }
    }
    if(!(walls[xCurrent][yCurrent] & 2)  && moveComplete == 0){
      if(distance[xCurrent][yCurrent-1] == minDistance){  //no walls to the north
        left();
        direction=2;
        moveComplete=1;
      }
    }
    if(!(walls[xCurrent][yCurrent] & 1) && moveComplete == 0){
      if(distance[xCurrent-1][yCurrent] == minDistance){  //no walls to the west
        fullturn();
        direction=1;
        moveComplete=1;
      }
    }  
  }
}
 
void main(void){
  /* Write your local variable definition here */
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  //initializeWalls();
  //initializeDistance();
  Motor_L_DutyTimer_Enable();
  Motor_R_DutyTimer_Enable();
  MotorR_DriveTimer_Enable();
  MotorL_DriveTimer_Enable();
     
  while(!((xCurrent == xFinal1 || xCurrent == xFinal2) && yCurrent == yFinal)){
    Motor_L_DutyTimer_Disable();
    Motor_R_DutyTimer_Disable();
    MotorR_DriveTimer_Disable();
    MotorL_DriveTimer_Disable();
    powerMotors(0);
    initializeLCD();
    clearLCD();
    pollSensors();
    updateWalls();
    distance[xCurrent][yCurrent] = calculateMinDistance(xCurrent,yCurrent) + 1; //Update cell distance
    //displaySensors();
    displayData();  //display current cell data    
    Cpu_Delay100US(5000);
    Motor_L_DutyTimer_Enable();
    Motor_R_DutyTimer_Enable();
    MotorR_DriveTimer_Enable();
    MotorL_DriveTimer_Enable();
    powerMotors(1);
    moveComplete=0;
    nextMove();    
    /*forward(375);//375 = 7in unit square in steps based on wheels
    if(xCurrent <=5){
      xCurrent++;
    }else if(yCurrent<=12){
      xCurrent=0;
      yCurrent++;
    }else{
      yCurrent=0;
    }*/
    Cpu_Delay100US(5000);
  }
  displayEnd();
  while(TRUE){
    Motor_L_DutyTimer_Enable();
    Motor_R_DutyTimer_Enable();
    MotorR_DriveTimer_Enable();
    MotorL_DriveTimer_Enable();
    powerMotors(1);
    fullturn();
  }
    

  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END Project */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
