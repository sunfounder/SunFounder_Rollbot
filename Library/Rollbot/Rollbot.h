#ifndef Rollbot_h
#define Rollbot_h

#include <Arduino.h>
//Define the notations  
#define NOTE_CL1 131
#define NOTE_CL2 147
#define NOTE_CL3 165
#define NOTE_CL4 175
#define NOTE_CL5 196
#define NOTE_CL6 221
#define NOTE_CL7 248

#define NOTE_C0 -1
#define NOTE_C1 262
#define NOTE_C2 294
#define NOTE_C3 330
#define NOTE_C4 350
#define NOTE_C5 393
#define NOTE_C6 441
#define NOTE_C7 495

#define NOTE_CH1 525
#define NOTE_CH2 589
#define NOTE_CH3 661
#define NOTE_CH4 700
#define NOTE_CH5 786
#define NOTE_CH6 882
#define NOTE_CH7 990

#define NOTE_DL1 147
#define NOTE_DL2 165
#define NOTE_DL3 175
#define NOTE_DL4 196
#define NOTE_DL5 221
#define NOTE_DL6 248
#define NOTE_DL7 278

#define NOTE_D0 -1
#define NOTE_D1 294
#define NOTE_D2 330
#define NOTE_D3 350
#define NOTE_D4 393
#define NOTE_D5 441
#define NOTE_D6 495
#define NOTE_D7 556

#define NOTE_DH1 589
#define NOTE_DH2 661
#define NOTE_DH3 700
#define NOTE_DH4 786
#define NOTE_DH5 882
#define NOTE_DH6 990
#define NOTE_DH7 1112

#define NOTE_EL7 312
#define NOTE_EL1 165
#define NOTE_EL2 175
#define NOTE_EL3 196
#define NOTE_EL4 221
#define NOTE_EL5 248
#define NOTE_EL6 278

#define NOTE_E0 -1
#define NOTE_E1 330
#define NOTE_E7 624
#define NOTE_E2 350
#define NOTE_E3 393
#define NOTE_E4 441
#define NOTE_E5 495
#define NOTE_E6 556

#define NOTE_EH7 1248
#define NOTE_EH1 661
#define NOTE_EH2 700
#define NOTE_EH3 786
#define NOTE_EH4 882
#define NOTE_EH5 990
#define NOTE_EH6 1112

#define NOTE_G0 -1
#define NOTE_GL1 196
#define NOTE_GL2 221
#define NOTE_GL3 234
#define NOTE_GL4 262
#define NOTE_GL5 294
#define NOTE_GL6 330
#define NOTE_GL7 371

#define NOTE_G1 393
#define NOTE_G2 441
#define NOTE_G3 495
#define NOTE_G4 556
#define NOTE_G5 624
#define NOTE_G6 661
#define NOTE_G7 742

#define NOTE_GH1 700
#define NOTE_GH2 786
#define NOTE_GH3 882
#define NOTE_GH4 935
#define NOTE_GH5 1049
#define NOTE_GH6 1178
#define NOTE_GH7 1322

#define   latchPin      11
#define   clockPin      13
#define   dataPin       12      //signals of 74HC595 control
#define   MOTOR_L_DIR   4
#define   MOTOR_L_PWM   5       //signals of the left motor control
#define   MOTOR_R_PWM   6
#define   MOTOR_R_DIR   7       //signals of the right motor control

/*********Class of motor driver***********/
class RollbotMotors
{
  public:
    RollbotMotors();
    void Motordrive(int speed_dir, int speed_left, int speed_right);
    void Motorstop();
  private:
    void MotorSetSpeed(int speed_dir, int speed_left, int speed_right);
    int Min0, Min1, Min2, Max0, Max1, Max2;  
};
/*********Class of OLED control***********/
class RollbotOLED 
{
  public:
    void OLED_Init();
    void IIC_SetPos(unsigned int x, unsigned int y);
    void ShowCN_3216(unsigned int x, unsigned int y, unsigned int N, const int *p);
    void ShowCN_1616(unsigned int x, unsigned int y, unsigned int N, const int *p);
	void ShowCN_1216(unsigned int x, unsigned int y, unsigned int N,const  int *p);
    void ShowCN_168(unsigned int x, unsigned int y, unsigned int N, const int *p);
	void ShowCN_816(unsigned int x, unsigned int y, unsigned int N, const int *p);
	void ShowCN_616(unsigned int x, unsigned int y, unsigned int N, const int *p);
    void ShowPIC(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const int *p);
	void SelectFace(unsigned int i,const int *SmilingFace,const int *LongFace,const int *NormalFace);
    void Clear_Screen(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int dat1);
    void Fill_Screen(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int dat1);
    void NumDisplay(int i,const  int *Direction,const  int *Foward,const  int *Left,const  int *Right,const  int *Back,const  int *TimeNumber);
	void Clear_NumDisplay(const  int *Direction, const  int *Foward, const  int *Left, const  int *Right, const  int *Back, const  int *TimeNumber);
	void Follow_NumDisplay(unsigned int DirectionFlag, const  int *Foward, const  int *TimeNumber);
    void PowerDisplay(int Power);
    void DownloadDisplay();	
    void SignalDisplay();
    void BluetoothDisplay();
    void OLED_SignalDisplay(int Flag0,int Flag1,int Flag2,int Flag3,int Flag4);
    void Button_Display(int i, const  int *SmilingFace, const  int *LongFace, const  int *NormalFace, const  int *StartDebug, const  int *Direction, const  int *Foward, const  int *Left, const  int *Right, const  int *Back, const  int *TimeNumber, const  int *SignalNumber);
    void Button_DisplayMaze(const  int *StartDebug,const  int *Maze,const  int *New);
	void Button_Follow(const  int *StartDebug,const int *Bee);
	void DisplayMaze(int i ,const  int *LRBS);
	void OLED_Display(const int *Rollbot,const  int *Sunfounder,const  int *StartDebug);
	void SelectBee(unsigned int i,const int *BeeOne,const int *BeeTwo,const int *BeeThree,const int *BeeFour);
  private:
    void WriteCommand(unsigned int ins);
    void WriteData(unsigned int dat);
};
/*********Class of LED control***********/
class RollbotLED
{
  public:
    RollbotLED();
    void DataOut(int val);
};
/*********Class of buzzer driver***********/
class RollbotBuzzer//line-following
{
  public:
    RollbotBuzzer(int pin);
    void MiniBuzzer(int *tune, float *duration, int Length);
  private:
    int tonePin;//the pin connected to buzzer
};
/*********Class of reading sensors***********/
class RollbotReadSensor : public RollbotMotors
{
  public:
    int data[5] = {0};          //Define the array of analog value of the sensor
    int OLED_Flag[5] = {0};     //Define the array of signals for the OLED
    int threshold = 0;          //Define the reference value of the car 
    void Read_Data();
    void Data_Print();
    int Read_BlackFlag();
	int Read_WhiteFlag();
	int Read_MazeFlag();
    void ThresholdCheck(int speed_dir, int ms);
  private:
    int Min0, Min1, Min2, Max0, Max1, Max2;
};
/*********Class of reading buttons***********/
class RollbotButton	: public RollbotOLED
{
  public:
    RollbotButton(int KeyPin);
    int Time;
    void Button(int i, const  int *SmilingFace, const  int *LongFace, const  int *NormalFace, const  int *StartDebug, const  int *Direction, const  int *Foward, const  int *Left, const  int *Right, const  int *Back, const  int *TimeNumber, const  int *SignalNumber);
	void ButtonMaze(const  int *StartDebug,const  int *Maze,const  int *New);
	void ButtonNewMaze(const  int *StartDebug,const int *Bee);
 private:
    int _KeyPin;
};

#endif


