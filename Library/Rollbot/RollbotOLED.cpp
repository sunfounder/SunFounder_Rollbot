/* -----------------------------------------------------------------------------
  Author             : Allen
  Check              : Amy
  Version            : V1.0
  Date               : 17/06/2016
  Description        : The smart car follows lines
  Company Website    : http://www.sunfounder.com
   ---------------------------------------------------------------------------*/
/* Include ------------------------------------------------------------------*/
#include <avr/pgmspace.h>
#include "Rollbot.h"
#include <Wire.h>

/*********OLED command writing***********/
void RollbotOLED::WriteCommand(unsigned int ins)
{
  Wire.beginTransmission(0x78 >> 1);//0x78 >> 1
  Wire.write(0x00);//0x00
  Wire.write(ins);
  Wire.endTransmission();
}
/*********OLED data writing***********/
void RollbotOLED::WriteData(unsigned int dat)
{
  Wire.beginTransmission(0x78 >> 1);//0x78 >> 1
  Wire.write(0x40);//0x40
  Wire.write(dat);
  Wire.endTransmission();
}
/*********OLED initialization***********/
void RollbotOLED::OLED_Init()
{
  Wire.begin();

  WriteCommand(0xAE);//display off

  WriteCommand(0x00);//set lower column address
  WriteCommand(0x10);//set higher column address

  WriteCommand(0x40);//set the start line of display

  WriteCommand(0xB0);//set page address

  WriteCommand(0x81);
  WriteCommand(0xCF);//0~255��

  WriteCommand(0xA1);//set segment remap

  WriteCommand(0xA6);//normal / reverse

  WriteCommand(0xA8);//multiplex ratio
  WriteCommand(0x3F);//duty = 1/64

  WriteCommand(0xC8);//Com scan direction

  WriteCommand(0xD3);//set display offset
  WriteCommand(0x00);

  WriteCommand(0xD5);//set osc division
  WriteCommand(0x80);

  WriteCommand(0xD9);//set pre-charge period
  WriteCommand(0xF1);

  WriteCommand(0xDA);//set COM pins
  WriteCommand(0x12);

  WriteCommand(0xDB);//set VCOMH
  WriteCommand(0x40);

  WriteCommand(0x8D);//set charge pump enable
  WriteCommand(0x14);

  WriteCommand(0xAF);//display ON
}
void RollbotOLED::IIC_SetPos(unsigned int x, unsigned int y)
{
  WriteCommand(0xb0 + y);
  WriteCommand(((x & 0xf0) >> 4) | 0x10); //|0x10
  WriteCommand((x & 0x0f) | 0x00); //|0x01
}
/*********32*16 character display***********/
void RollbotOLED::ShowCN_3216(unsigned int x, unsigned int y, unsigned int N,const int *p)
{
  unsigned char wm = 0;
  unsigned int adder = 64 * N;
  IIC_SetPos(x , y);
  for (wm = 0; wm < 32; wm++)
  {
    WriteData(pgm_read_byte(&p[adder]));
    adder += 1;
  }
  IIC_SetPos(x, y + 1);
  for (wm = 0; wm < 32; wm++)
  {
    WriteData(pgm_read_byte(&p[adder]));
    adder += 1;
  }
}
/*********16*16 character display***********/
void RollbotOLED::ShowCN_1216(unsigned int x, unsigned int y, unsigned int N,const  int *p)
{
  unsigned char wm = 0;
  unsigned int adder = 24 * N;
  IIC_SetPos(x , y);
  for (wm = 0; wm < 12; wm++)
  {
    WriteData(pgm_read_byte(&p[adder]));
    adder += 1;
  }
  IIC_SetPos(x, y + 1);
  for (wm = 0; wm < 12; wm++)
  {
    WriteData(pgm_read_byte(&p[adder]));
    adder += 1;
  }
}
/*********16*16 character display***********/
void RollbotOLED::ShowCN_1616(unsigned int x, unsigned int y, unsigned int N,const  int *p)
{
  unsigned char wm = 0;
  unsigned int adder = 32 * N;
  IIC_SetPos(x , y);
  for (wm = 0; wm < 16; wm++)
  {
    WriteData(pgm_read_byte(&p[adder]));
    adder += 1;
  }
  IIC_SetPos(x, y + 1);
  for (wm = 0; wm < 16; wm++)
  {
    WriteData(pgm_read_byte(&p[adder]));
    adder += 1;
  }
}
/*********6*16 character display***********/
void RollbotOLED::ShowCN_616(unsigned int x, unsigned int y, unsigned int N,const  int *p)
{
  unsigned char wm = 0;
  unsigned int adder = 12 * N;
  IIC_SetPos(x , y);
  for (wm = 0; wm < 6; wm++)
  {
    WriteData(pgm_read_byte(&p[adder]));
    adder += 1;
  }
  IIC_SetPos(x, y + 1);
  for (wm = 0; wm < 6; wm++)
  {
    WriteData(pgm_read_byte(&p[adder]));
    adder += 1;
  }
}
/*********8*16 character display***********/
void RollbotOLED::ShowCN_816(unsigned int x, unsigned int y, unsigned int N,const  int *p)
{
  unsigned char wm = 0;
  unsigned int adder = 16 * N;
  IIC_SetPos(x , y);
  for (wm = 0; wm < 8; wm++)
  {
    WriteData(pgm_read_byte(&p[adder]));
    adder += 1;
  }
  IIC_SetPos(x, y + 1);
  for (wm = 0; wm < 8; wm++)
  {
    WriteData(pgm_read_byte(&p[adder]));
    adder += 1;
  }
}
/*********16*8 character display***********/
void RollbotOLED::ShowCN_168(unsigned int x, unsigned int y, unsigned int N,const  int *p)
{
  unsigned char wm = 0;
  unsigned int adder = 16 * N;
  IIC_SetPos(x , y);
  for (wm = 0; wm < 16; wm++)
  {
    WriteData(pgm_read_byte(&p[adder]));
    adder += 1;
  }
}
/*********Image display***********/
void RollbotOLED::ShowPIC(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const int *p)
{
  unsigned int adder = 0;
  unsigned char x, y;
  for (y = y0; y < y1; y++)
  {
    for (x = x0; x < x1; x++)
    {
      IIC_SetPos(x, y);
      WriteData(pgm_read_byte(&p[adder]));
	  adder += 1;
    }
  }
}
void RollbotOLED::SelectFace(unsigned int i,const int *SmilingFace,const int *LongFace,const int *NormalFace)
{
	if(i==1)
	{
		ShowPIC(32,2,96,8,SmilingFace);
	}
	else if(i==2)
	{
		ShowPIC(32,2,96,8,NormalFace);
	}
	else if(i==3)
	{
		ShowPIC(32,2,96,8,LongFace);
	}
}
void RollbotOLED::SelectBee(unsigned int i,const int *BeeOne,const int *BeeTwo,const int *BeeThree,const int *BeeFour)
{
	if(i==1)
	{
		ShowPIC(0,2,128,8,BeeOne);
	}
	else if(i==2)
	{
		ShowPIC(0,2,128,8,BeeTwo);
		
	}
	else if(i==3)
	{
		ShowPIC(0,2,128,8,BeeThree);
	}
	else if(i==4)
	{
		ShowPIC(0,2,128,8,BeeFour);
	}
}
/*********Screen clearing***********/
void RollbotOLED::Clear_Screen(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int dat1)
{
  unsigned char x, y;
  for (y = y0; y < y1; y++)
  {
    WriteCommand(0xB0 + y);  /*set page address*/
    WriteCommand(0x02);    /*set lower column address*/
    WriteCommand(0x10);    /*set higher column address*/
    for (x = x0; x < x1; x++)
    {
      WriteData(dat1);
    }
  }
}
/*********Display of partial screen control***********/
void RollbotOLED::Fill_Screen(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int dat1)
{
  unsigned char x, y;
  for (y = y0; y < y1; y++)
  {
    for (x = x0; x < x1; x++)
    {
      IIC_SetPos(x, y);
      WriteData(dat1);
    }
  }
}

/*********Display of digital control***********/
void RollbotOLED::NumDisplay(int i,const  int *Direction,const  int *Foward,const  int *Left,const  int *Right,const  int *Back,const  int *TimeNumber)
{
  if ((i <= 6) && (i > 0))
  {
    i = i + 1;
    while (i)
    {
      i--;
      ShowCN_1616(96, 2, 0, Foward);
      delay(50);
      Fill_Screen(96, 2, 112, 4, 0x00);
      delay(50);
      ShowCN_1616(96, 2, 0, Foward);
      ShowCN_1616(95, 4, i, TimeNumber);
	  delay(300);
    }
  }
  else if (i == 7)
  {
    ShowCN_1616(96, 2, 0, Foward);
    delay(50);
    Fill_Screen(96, 2, 112, 4, 0x00);
    delay(50);
  }
  else if (i == 8)
  {
    ShowCN_1616(96, 6, 0, Back);
    delay(50);
    Fill_Screen(96, 6, 112, 8, 0x00);
    delay(50);
  }
  else if (i == 9)
  {
    ShowCN_1616(80, 4, 0, Left);
    delay(50);
    Fill_Screen(80, 4, 96, 6, 0x00);
    delay(50);
  }
  else if (i == 10)
  {
    ShowCN_1616(112, 4, 0, Right);
    delay(50);
    Fill_Screen(112, 4, 128, 6, 0x00);
    delay(50);
  }
  else
  {
    ShowCN_1616(96, 2, 0, Foward);
    ShowCN_1616(80, 4, 0, Left);
    ShowCN_1616(112, 4, 0, Right);
    ShowCN_1616(96, 6, 0, Back);
    ShowCN_1616(95, 4, 0, TimeNumber);
  }
}

void RollbotOLED::Clear_NumDisplay(const  int *Direction, const  int *Foward, const  int *Left, const  int *Right, const  int *Back, const  int *TimeNumber)
{
	Clear_Screen(0, 2, 128, 8, 0x00);
    ShowCN_816(1, 4, 0, Direction);
    ShowCN_816(9, 4, 1, Direction);
    ShowCN_816(17, 4, 2, Direction);
    ShowCN_816(25, 4, 3, Direction);
    ShowCN_816(33, 4, 4, Direction);
    ShowCN_816(41, 4, 5, Direction);
    ShowCN_816(49, 4, 6, Direction);
    ShowCN_816(57, 4, 7, Direction);
    ShowCN_816(65, 4, 8, Direction);
    ShowCN_816(73, 4, 9, Direction);
    ShowCN_1616(96, 2, 0, Foward);
    ShowCN_1616(80, 4, 0, Left);
    ShowCN_1616(112, 4, 0, Right);
    ShowCN_1616(96, 6, 0, Back);
    ShowCN_1616(95, 4, 0, TimeNumber);
}
void RollbotOLED::Follow_NumDisplay(unsigned int DirectionFlag, const  int *Foward, const  int *TimeNumber)
{
	ShowCN_1616(96, 2, 0, Foward);
    delay(30);
    Fill_Screen(96, 2, 112, 4, 0x00);
    delay(30);
    ShowCN_1616(96, 2, 0, Foward);
    ShowCN_1616(95, 4, DirectionFlag, TimeNumber);
}

/*********Electricity quantity display***********/
void RollbotOLED::PowerDisplay(int Power)
{
  IIC_SetPos(107, 0);
  WriteData(0xc0);
  WriteData(0x40);
  WriteData(0x40);
  WriteData(0x78);

  WriteData(0x08);
  if (Power > 840)
  {
    WriteData(0xe8);
    WriteData(0xe8);
    WriteData(0xe8);
    WriteData(0xe8);
  }
  else
  {
    WriteData(0x08);
    WriteData(0x08);
    WriteData(0x08);
    WriteData(0x08);
  }
  WriteData(0x08);

  if (Power > 800)
  {
    WriteData(0xe8);
    WriteData(0xe8);
    WriteData(0xe8);
    WriteData(0xe8);
  }
  else
  {
    WriteData(0x08);
    WriteData(0x08);
    WriteData(0x08);
    WriteData(0x08);
  }

  WriteData(0x08);

  if (Power > 760)
  {
    WriteData(0xe8);
    WriteData(0xe8);
    WriteData(0xe8);
    WriteData(0xe8);
  }
  else
  {
    WriteData(0x08);
    WriteData(0x08);
    WriteData(0x08);
    WriteData(0x08);
  }

  WriteData(0x08);

  WriteData(0xf8);

  IIC_SetPos(107, 1);
  WriteData(0x03);
  WriteData(0x02);
  WriteData(0x02);
  WriteData(0x1e);

  WriteData(0x10);
  if (Power > 840)
  {
    WriteData(0x17);
    WriteData(0x17);
    WriteData(0x17);
    WriteData(0x17);
  }
  else
  {
    WriteData(0x10);
    WriteData(0x10);
    WriteData(0x10);
    WriteData(0x10);
  }

  WriteData(0x10);

  if (Power > 800)
  {
    WriteData(0x17);
    WriteData(0x17);
    WriteData(0x17);
    WriteData(0x17);
  }
  else
  {
    WriteData(0x10);
    WriteData(0x10);
    WriteData(0x10);
    WriteData(0x10);
  }

  WriteData(0x10);

  if (Power > 760)
  {
    WriteData(0x17);
    WriteData(0x17);
    WriteData(0x17);
    WriteData(0x17);
  }
  else
  {
    WriteData(0x10);
    WriteData(0x10);
    WriteData(0x10);
    WriteData(0x10);
  }

  WriteData(0x10);

  WriteData(0x1f);

}

/*********Display of download***********/
void RollbotOLED::DownloadDisplay()
{
  IIC_SetPos(87, 0);
  WriteData(0x20);
  WriteData(0x30);
  WriteData(0x38);
  WriteData(0xfc);
  WriteData(0x38);
  WriteData(0x30);
  WriteData(0x20);
  WriteData(0x00);
  WriteData(0x00);
  WriteData(0x00);
  WriteData(0x00);
  WriteData(0xfc);
  IIC_SetPos(87, 1);
  WriteData(0x00);
  WriteData(0x00);
  WriteData(0x00);
  WriteData(0x3f);
  WriteData(0x00);
  WriteData(0x00);
  WriteData(0x00);
  WriteData(0x00);
  WriteData(0x04);
  WriteData(0x0c);
  WriteData(0x1c);
  WriteData(0x3f);
  WriteData(0x1c);
  WriteData(0x0c);
  WriteData(0x04);
}
/*********Signal display***********/
void RollbotOLED::SignalDisplay()
{
  IIC_SetPos(2, 0);
  WriteData(0x03);
  WriteData(0x05);
  WriteData(0x09);
  WriteData(0x11);
  WriteData(0x21);
  WriteData(0x41);
  WriteData(0xff);
  WriteData(0x41);
  WriteData(0x21);
  WriteData(0x11);
  WriteData(0x09);
  WriteData(0x05);
  WriteData(0x03);
  IIC_SetPos(8, 1);
  WriteData(0x7f);
  WriteData(0x00);
  WriteData(0x40);
  WriteData(0x00);
  WriteData(0x60);
  WriteData(0x00);
  WriteData(0x70);
  WriteData(0x00);
  WriteData(0x78);
  WriteData(0x00);
  WriteData(0x7c);
  WriteData(0x00);
  WriteData(0x7e);
  WriteData(0x00);
  WriteData(0x7f);
}
/*********Bluetooth display***********/
void RollbotOLED::BluetoothDisplay()
{
    IIC_SetPos(30, 0);
    WriteData(0x10);
    WriteData(0x20);
    WriteData(0x40);
    WriteData(0xfe);
    WriteData(0x82);
    WriteData(0x44);
    WriteData(0x28);
    WriteData(0x10);
    IIC_SetPos(30, 1);
    WriteData(0x04);
    WriteData(0x02);
    WriteData(0x01);
    WriteData(0x7f);
    WriteData(0x41);
    WriteData(0x22);
    WriteData(0x14);
    WriteData(0x08);
}
/*********Display of detection signals by the car***********/
void RollbotOLED::OLED_SignalDisplay(int Flag0,int Flag1,int Flag2,int Flag3,int Flag4)
{
  static int _signal1 = Flag0, _signal2 = Flag1, _signal3 = Flag2, _signal4 = Flag3, _signal5 = Flag4;
  if (_signal1 != Flag0)
  {
    _signal1 = Flag0;
    Fill_Screen(12, 2, 20, 6, 0x00);
    Fill_Screen(12, Flag0, 20, 6, 0xff);
  }
  if (_signal2 != Flag1)
  {
    _signal2 = Flag1;
    Fill_Screen(36, 2, 44, 6, 0x00);
    Fill_Screen(36, Flag1, 44, 6, 0xff);
  }
  if (_signal3 != Flag2)
  {
    _signal3 = Flag2;
    Fill_Screen(60, 2, 68, 6, 0x00);
    Fill_Screen(60, Flag2, 68, 6, 0xff);
  }
  if (_signal4 != Flag3)
  {
    _signal4 = Flag3;
    Fill_Screen(84, 2, 92, 6, 0x00);
    Fill_Screen(84, Flag3, 92, 6, 0xff);
  }
  if (_signal5 != Flag4)
  {
    _signal5 = Flag4;
    Fill_Screen(108, 2, 116, 6, 0x00);
    Fill_Screen(108, Flag4, 116, 6, 0xff);
  }
}
/*********Button modulation display***********/
void RollbotOLED::Button_Display(int i, const  int *SmilingFace, const  int *LongFace, const  int *NormalFace, const  int *StartDebug, const  int *Direction, const  int *Foward, const  int *Left, const  int *Right, const  int *Back, const  int *TimeNumber, const  int *SignalNumber)
{
  if(i==0)
  {
	Fill_Screen(0, 6, 32, 8, 0x00);
    delay(200);
    ShowCN_616(2, 6, 0, StartDebug);
    ShowCN_616(8, 6, 1, StartDebug);
    ShowCN_616(14, 6, 2, StartDebug);
    ShowCN_616(20, 6, 3, StartDebug);
    ShowCN_616(26, 6, 4, StartDebug);
    delay(200);
    Clear_Screen(0, 2, 128, 8, 0x00);
	SelectFace(2,SmilingFace,LongFace,NormalFace);
  }
  else if (i == 1)
  {
    Fill_Screen(0, 6, 32, 8, 0x00);
    delay(200);
    ShowCN_616(2, 6, 0, StartDebug);
    ShowCN_616(8, 6, 1, StartDebug);
    ShowCN_616(14, 6, 2, StartDebug);
    ShowCN_616(20, 6, 3, StartDebug);
    ShowCN_616(26, 6, 4, StartDebug);
    delay(200);
    Clear_Screen(0, 2, 128, 8, 0x00);
    ShowCN_816(1, 4, 0, Direction);
    ShowCN_816(9, 4, 1, Direction);
    ShowCN_816(17, 4, 2, Direction);
    ShowCN_816(25, 4, 3, Direction);
    ShowCN_816(33, 4, 4, Direction);
    ShowCN_816(41, 4, 5, Direction);
    ShowCN_816(49, 4, 6, Direction);
    ShowCN_816(57, 4, 7, Direction);
    ShowCN_816(65, 4, 8, Direction);
    ShowCN_816(73, 4, 9, Direction);
    ShowCN_1616(96, 2, 0, Foward);
    ShowCN_1616(80, 4, 0, Left);
    ShowCN_1616(112, 4, 0, Right);
    ShowCN_1616(96, 6, 0, Back);
    ShowCN_1616(95, 4, 0, TimeNumber);
  }
  else if (i == 2)
  {
    Fill_Screen(96, 6, 128, 8, 0x00);
    delay(200);
    ShowCN_616(98, 6, 5, StartDebug);
    ShowCN_616(104, 6, 6, StartDebug);
    ShowCN_616(110, 6, 7, StartDebug);
    ShowCN_616(116, 6, 8, StartDebug);
    ShowCN_616(122, 6, 9, StartDebug);
    delay(200);
    Clear_Screen(0, 2, 128, 8, 0x00);
    ShowCN_1616(8, 6, 0, SignalNumber);
    ShowCN_1616(32, 6, 1, SignalNumber);
    ShowCN_1616(56, 6, 2, SignalNumber);
    ShowCN_1616(80, 6, 3, SignalNumber);
    ShowCN_1616(104, 6, 4, SignalNumber);
  }
  else if (i == 3)
  {
    Fill_Screen(0, 6, 32, 8, 0x00);
    delay(200);
    ShowCN_616(2, 6, 0, StartDebug);
    ShowCN_616(8, 6, 1, StartDebug);
    ShowCN_616(14, 6, 2, StartDebug);
    ShowCN_616(20, 6, 3, StartDebug);
    ShowCN_616(26, 6, 4, StartDebug);
    delay(200);
    Clear_Screen(0, 2, 128, 8, 0x00);
    ShowCN_1616(8, 6, 0, SignalNumber);
    ShowCN_1616(32, 6, 1, SignalNumber);
    ShowCN_1616(56, 6, 2, SignalNumber);
    ShowCN_1616(80, 6, 3, SignalNumber);
    ShowCN_1616(104, 6, 4, SignalNumber);
  }
}
void RollbotOLED::Button_Follow(const  int *StartDebug,const int *Bee)
{
	Fill_Screen(0, 6, 32, 8, 0x00);
    delay(200);
    ShowCN_616(2, 6, 0, StartDebug);
    ShowCN_616(8, 6, 1, StartDebug);
    ShowCN_616(14, 6, 2, StartDebug);
    ShowCN_616(20, 6, 3, StartDebug);
    ShowCN_616(26, 6, 4, StartDebug);
	delay(200);
    Clear_Screen(0, 2, 128, 8, 0x00);
	ShowPIC(0,2,128,8,Bee);
}
void RollbotOLED::Button_DisplayMaze(const  int *StartDebug,const  int *Maze,const  int *New)
{
	Fill_Screen(0, 6, 32, 8, 0x00);
    delay(200);
    ShowCN_616(2, 6, 0, StartDebug);
    ShowCN_616(8, 6, 1, StartDebug);
    ShowCN_616(14, 6, 2, StartDebug);
    ShowCN_616(20, 6, 3, StartDebug);
    ShowCN_616(26, 6, 4, StartDebug);
    delay(200);
    Clear_Screen(0, 2, 128, 8, 0x00);
    ShowCN_616(2, 2, 0, Maze);
    ShowCN_616(8, 2, 1, Maze);
    ShowCN_616(14, 2, 2, Maze);
    ShowCN_616(20, 2, 3, Maze);
    ShowCN_616(26, 2, 4, Maze);
	ShowCN_616(2, 6, 0, New);
    ShowCN_616(8, 6, 1, New);
    ShowCN_616(14, 6, 2, New);
    ShowCN_616(20, 6, 3, New);
}
void RollbotOLED::DisplayMaze(int i ,const  int *LRBS)
{
	static int m = 0;
	static int n = 0;
	if(i == 1)
	{
		if(m < 32)
		{
			if(m<14)
			{
				ShowCN_616(32+m*7,2,0,LRBS);
			}
			else
			{
				ShowCN_616((m-14)*7+2,4,0,LRBS);
			}
			m++;
		}
		
	}
	else
	{
		if(n<15)
		{
			ShowCN_616(26+n*7,6,0,LRBS);
			n++;
		}
	}
}
/*********Interface display of the car***********/
void RollbotOLED::OLED_Display(const int *Rollbot,const  int *Sunfounder,const  int *StartDebug)
{
  ShowCN_1216(22, 4, 0, Rollbot);
  ShowCN_1216(34, 4, 1, Rollbot);
  ShowCN_1216(46, 4, 2, Rollbot);
  ShowCN_1216(58, 4, 3, Rollbot);
  ShowCN_1216(70, 4, 4, Rollbot);
  ShowCN_1216(82, 4, 5, Rollbot);
  ShowCN_1216(94, 4, 6, Rollbot);
  ShowPIC(40,2,88,4,Sunfounder);
  ShowCN_616(2, 6, 0, StartDebug);
  ShowCN_616(8, 6, 1, StartDebug);
  ShowCN_616(14, 6, 2, StartDebug);
  ShowCN_616(20, 6, 3, StartDebug);
  ShowCN_616(26, 6, 4, StartDebug);
  ShowCN_616(98, 6, 5, StartDebug);
  ShowCN_616(104, 6, 6, StartDebug);
  ShowCN_616(110, 6, 7, StartDebug);
  ShowCN_616(116, 6, 8, StartDebug);
  ShowCN_616(122, 6, 9, StartDebug);
}

