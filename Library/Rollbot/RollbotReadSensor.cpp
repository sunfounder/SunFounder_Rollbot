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

/*********Read data of the sensors***********/
void RollbotReadSensor::Read_Data()
{
  data[0] = analogRead(A0);               
  data[1] = analogRead(A1);
  data[2] = analogRead(A2);
  data[3] = analogRead(A3);
  data[4] = analogRead(A7);                 
  OLED_Flag[0] = map(data[0], 50, 500, 3, 6);    
  OLED_Flag[1] = map(data[1], 50, 500, 3, 6);
  OLED_Flag[2] = map(data[2], 50, 500, 3, 6);
  OLED_Flag[3] = map(data[3], 50, 500, 3, 6);
  OLED_Flag[4] = map(data[4], 50, 500, 3, 6);    
}
/*********Print data of the sensors***********/
void RollbotReadSensor::Data_Print()
{
   Read_Data();
   Serial.print("data[0]");
   Serial.println(data[0]);
   Serial.print("data[1]");
   Serial.println(data[1]);
   Serial.print("data[2]");
   Serial.println(data[2]);
   Serial.print("data[3]");
   Serial.println(data[3]);
   Serial.print("data[4]");
   Serial.println(data[4]);
}   
/**********Read position of the car***********/
int RollbotReadSensor::Read_MazeFlag()
{
  Read_Data();
//  if ((data[0] < threshold) && (data[1] < threshold) && (data[2] > threshold) && (data[3] > threshold) && (data[4] > threshold)) return -3;
  if ((data[0] > threshold) && (data[1] < threshold) && (data[2] > threshold) && (data[3] > threshold) && (data[4] > threshold)) return -2;
  else if ((data[0] > threshold) && (data[1] < threshold) && (data[2] < threshold) && (data[3] > threshold) && (data[4] > threshold)) return -1;    
  else if ((data[0] > threshold) && (data[1] > threshold) && (data[2] < threshold) && (data[3] > threshold) && (data[4] > threshold)) return 0;  
  else if ((data[0] > threshold) && (data[1] > threshold) && (data[2] < threshold) && (data[3] < threshold) && (data[4] > threshold)) return 1;    
  else if ((data[0] > threshold) && (data[1] > threshold) && (data[2] > threshold) && (data[3] < threshold) && (data[4] > threshold)) return 2;
//  else if ((data[0] > threshold) && (data[1] > threshold) && (data[2] > threshold) && (data[3] < threshold) && (data[4] < threshold)) return 3;
  else if ((data[0] > threshold) && (data[1] > threshold) && (data[2] > threshold) && (data[3] > threshold) && (data[4] > threshold)) return 3;//全白
}
int RollbotReadSensor::Read_BlackFlag()
{
	while(1)
	{
	  Read_Data();
	  if ((data[0] < threshold) && (data[1] > threshold) && (data[2] > threshold) && (data[3] > threshold) && (data[4] > threshold)) return -4;
	  else if ((data[0] < threshold) && (data[1] < threshold) && (data[2] > threshold) && (data[3] > threshold) && (data[4] > threshold)) return -3;
	  else if ((data[0] > threshold) && (data[1] < threshold) && (data[2] > threshold) && (data[3] > threshold) && (data[4] > threshold)) return -2;
	  else if ((data[0] > threshold) && (data[1] < threshold) && (data[2] < threshold) && (data[3] > threshold) && (data[4] > threshold)) return -1;    
	  else if ((data[0] > threshold) && (data[1] > threshold) && (data[2] < threshold) && (data[3] > threshold) && (data[4] > threshold)) return 0;     
	  else if ((data[0] > threshold) && (data[1] > threshold) && (data[2] < threshold) && (data[3] < threshold) && (data[4] > threshold)) return 1;  
	  else if ((data[0] > threshold) && (data[1] > threshold) && (data[2] > threshold) && (data[3] < threshold) && (data[4] > threshold)) return 2;
	  else if ((data[0] > threshold) && (data[1] > threshold) && (data[2] > threshold) && (data[3] < threshold) && (data[4] < threshold)) return 3;
	  else if ((data[0] > threshold) && (data[1] > threshold) && (data[2] > threshold) && (data[3] > threshold) && (data[4] < threshold)) return 4; 
	  else if ((data[0] < threshold) && (data[1] < threshold) && (data[2] < threshold) && (data[3] < threshold)) return 5;
	  else if ((data[1] < threshold) && (data[2] < threshold) && (data[3] < threshold) && (data[4] < threshold)) return 5;
	  else if ((data[0] > threshold) && (data[1] > threshold) && (data[2] > threshold) && (data[3] > threshold) && (data[4] > threshold)) return 6;
	}
}
int RollbotReadSensor::Read_WhiteFlag()
{
  Read_Data();
  if ((data[0] > (threshold + 100)) && (data[1] < (threshold + 100)) && (data[2] < (threshold + 100)) && (data[3] < (threshold + 100)) && (data[4] < (threshold + 100))) return -4;
  else if ((data[0] > (threshold + 100)) && (data[1] > (threshold + 100)) && (data[2] < (threshold + 100)) && (data[3] < (threshold + 100)) && (data[4] < (threshold + 100))) return -3;
  else if ((data[0] < (threshold + 100)) && (data[1] > (threshold + 100)) && (data[2] < (threshold + 100)) && (data[3] < (threshold + 100)) && (data[4] < (threshold + 100))) return -2;
  else if ((data[0] < (threshold + 100)) && (data[1] > (threshold + 100)) && (data[2] > (threshold + 100)) && (data[3] < (threshold + 100)) && (data[4] < (threshold + 100))) return -1;    
  else if ((data[0] < (threshold + 100)) && (data[1] < (threshold + 100)) && (data[2] > (threshold + 100)) && (data[3] < (threshold + 100)) && (data[4] < (threshold + 100))) return 0;     
  else if ((data[0] < (threshold + 100)) && (data[1] < (threshold + 100)) && (data[2] > (threshold + 100)) && (data[3] > (threshold + 100)) && (data[4] < (threshold + 100))) return 1;     
  else if ((data[0] < (threshold + 100)) && (data[1] < (threshold + 100)) && (data[2] < (threshold + 100)) && (data[3] > (threshold + 100)) && (data[4] < (threshold + 100))) return 2;
  else if ((data[0] < (threshold + 100)) && (data[1] < (threshold + 100)) && (data[2] < (threshold + 100)) && (data[3] > (threshold + 100)) && (data[4] > (threshold + 100))) return 3;
  else if ((data[0] < (threshold + 100)) && (data[1] < (threshold + 100)) && (data[2] < (threshold + 100)) && (data[3] < (threshold + 100)) && (data[4] > (threshold + 100))) return 4;
}
/*********Read the reference value for signals***********/
void RollbotReadSensor::ThresholdCheck(int speed_dir, int ms)
{
  Motordrive(speed_dir,-100, 100); 
  delay(ms);
  Motordrive(speed_dir,0, 0);
  Read_Data();
  Min0 = data[0];
  Max0 = data[0];
  for (int i = 1; i < 5; i++)       
  {
    if (data[i] < Min0)
      Min0 = data[i];
    if (data[i] > Max0)
      Max0 = data[i];
  }
  delay(ms);
  Motordrive(speed_dir,100, -100); 
  delay(ms);
  Motordrive(speed_dir,0, 0);
  Read_Data();
  Min1 = data[0];
  Max1 = data[0];
  for (int i = 1; i < 5; i++)       
  {
    if (data[i] < Min1)
      Min1 = data[i];
    if (data[i] > Max1)
      Max1 = data[i];
  }
  delay(ms);
  Motordrive(speed_dir,100, -100); 
  delay(ms);
  Motordrive(speed_dir,0, 0);
  Read_Data();
  Min2 = data[0];
  Max2 = data[0];
  for (int i = 1; i < 5; i++)     
  {
    if (data[i] < Min2)
      Min2 = data[i];
    if (data[i] > Max2)
      Max2 = data[i];
  }
  delay(ms);
  Motordrive(speed_dir,-100, 100); 
  delay(ms);
  Motordrive(speed_dir,0, 0);
  threshold = (int)(((Min0 + Min1 + Min2) / 3 + (Max0 + Max1 + Max2) / 3) / 2);//110
}
