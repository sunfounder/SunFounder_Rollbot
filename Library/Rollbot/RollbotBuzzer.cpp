/* -----------------------------------------------------------------------------
  Author             : Allen
  Check              : Amy
  Version            : V1.0
  Date               : 17/06/2016
  Description        : The smart car follows lines
  Company Website    : http://www.sunfounder.com
   ---------------------------------------------------------------------------*/
#include "Rollbot.h"

/******************************************************************************
                Music - Internal function - Only for underlying calling
******************************************************************************/

RollbotBuzzer::RollbotBuzzer(int pin)
{
    pinMode(pin,OUTPUT);//Set the pin to buzzer as output  
    tonePin=pin;
}
void RollbotBuzzer::MiniBuzzer(int *tune,float *duration,int Length)
{
    for(int x=0;x<Length;x++)//the number of notation cycling
    {
      tone(tonePin,tune[x]);//The function plays the arrarys (each notation) in the tune[] list in turn
      delay(400*duration[x]);//duration is the time each notation lasts. 
	                         //400 means the longer time, the slower tempo, and vice versa
      noTone(tonePin);//Exit the current notation and move on to the next 
    }
}
