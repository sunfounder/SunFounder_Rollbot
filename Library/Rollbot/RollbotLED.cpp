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

/*********LED constructor***********/
RollbotLED::RollbotLED()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
/*********Output of data control***********/
void RollbotLED::DataOut(int val)
{
  for (int i = 0;i < 8;i++) 
  {
      if(val&0x80)
        digitalWrite(dataPin,1);
      else
        digitalWrite(dataPin,0);  
      val<<=1; 
      digitalWrite(clockPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(clockPin, LOW);    
  }
  digitalWrite(latchPin,LOW);
  delayMicroseconds(10);
  digitalWrite(latchPin,HIGH); 
}
