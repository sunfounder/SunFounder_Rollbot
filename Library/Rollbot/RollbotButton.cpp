/* -----------------------------------------------------------------------------
  Author             : Allen
  Check              : Amy
  Version            : V1.0
  Date               : 17/06/2016
  Description        : The smart car follows lines
  Company Website    : http://www.sunfounder.com
   ---------------------------------------------------------------------------*/
/* Include ------------------------------------------------------------------*/
#include "Rollbot.h"

/*********Button constructor***********/
RollbotButton::RollbotButton(int KeyPin)
{
    pinMode(KeyPin, INPUT);  
    _KeyPin=KeyPin;
}
/*********Reading button value***********/
void RollbotButton::Button(int i, const  int *SmilingFace, const  int *LongFace, const  int *NormalFace, const  int *StartDebug, const  int *Direction, const  int *Foward, const  int *Left, const  int *Right, const  int *Back, const  int *TimeNumber, const  int *SignalNumber)
{
  if (digitalRead(_KeyPin) == 0)               
  { 
    delay(5);                             
    if (digitalRead(_KeyPin) == 0)             
    {
      Time = 0;
      while (!digitalRead(_KeyPin))            
      {
        Time++;                       
        delay(50);
      }
      Button_Display(i,SmilingFace,LongFace,NormalFace,StartDebug,Direction,Foward,Left,Right, Back,TimeNumber,SignalNumber);
    }
  }     
}
void RollbotButton::ButtonMaze(const  int *StartDebug,const  int *Maze,const  int *New)
{
	if (digitalRead(_KeyPin) == 0)               
	  { 
		delay(5);                             
		if (digitalRead(_KeyPin) == 0)             
		{
		  Time = 0;
		  while (!digitalRead(_KeyPin))            
		  {
			Time++;                       
			delay(50);
		  }
		  Button_DisplayMaze(StartDebug,Maze,New);
		}
	  } 
}
void RollbotButton::ButtonNewMaze(const  int *StartDebug,const int *Bee)
{
	if (digitalRead(_KeyPin) == 0)               
	  { 
		delay(5);                             
		if (digitalRead(_KeyPin) == 0)             
		{
		  Time = 0;
		  while (!digitalRead(_KeyPin))            
		  {
			Time++;                       
			delay(50);
		  }
		}
		Button_Follow(StartDebug,Bee);
	  } 
}
