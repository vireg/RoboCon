#ifndef RoboLib_h
#define RoboLib_h

#include "Arduino.h"
#include <digitalWriteFast.h>
#include "PS2X_lib.h"
#include "SabertoothSimplified.h"

//Black	        GND
//Yellow	Attn
//Orange	Cmd
//Brown	        Data (Pullup, 5V)
//Blue	        Clk
//Pink	        Power	3.3V

//******************** Main code ********************//
#define commsee 50
#define commswing 100
#define commpole 150
#define commgym 200
#define commsigd 250
#define commpin 2
extern unsigned int mode;    //Seesaw, Pole walk, Swing, Jungle gym, Run, Drive adjust
extern bool registers[8];
extern bool sigBot;
extern bool swpull,holdauto;
extern int sigNo;
extern bool pwmAdjust;
#define modeled1 2
#define modeled2 3
#define modeled3 4
#define modeled4 5
#define modeled5 6
#define modeled6 7
extern bool magnetON;
//**********************************************************************//

//****************** PID ********************//
#define pwmMin -63
#define pwmMax 63
extern double ITerm,kp,ki,kd;
extern int errorPrevious;
extern bool track;
//////////////////////////////////Line Follower//////////////////////////
#define th1 100
#define th2 550
#define line_1 A12
#define line_2 A11
#define line_3 A10
#define line_4 A9
#define line_5 A8
#define line_6 A7
#define line_7 A1
#define line_8 A2
#define line_9 A3
#define line_10 A4
#define line_11 A5
#define line_12 A6

//#define line_7 A11
//extern int line_val0;
extern int line_v1;
extern int line_v2;
extern int line_v3;
extern int line_v4;
extern int line_v5;
extern int line_v6;
extern int line_v7;
extern int line_v8;
extern int line_v9;
extern int line_v10;
extern int line_v11;
extern int line_v12;
extern bool override;
extern bool lineaction;
//******************** PS2 controller ********************//
#define PS2_CLK 38
#define PS2_DAT 40
#define PS2_CMD 42
#define PS2_ATTN 44
#define pressures true
#define rumble true
extern int error; 
extern byte type;
extern byte vibrate;
extern PS2X ps2x; // create PS2 Controller Class
void PS2_setup();
//**********************************************************************//

//******************** Pneumatics ********************//
#define ver_hall_1      39  //vertical piston hall sensor 1
#define ver_hall_2      41 //vertical piston hall sensor 2
#define ver_hall_3      43  //vertical piston hall sensor 3
#define ver_hall_4      45  //vertical piston hall sensor 4

#define hor_hall_1      47  //horizontal piston hall sensor 1
#define hor_hall_2      49  //horizontal piston hall sensor 2
#define hor_hall_3      51  //horizontal piston hall sensor 3
#define hor_hall_4      53  //horizontal piston hall sensor 4

#define ver_cylinder_ext    37//vertical cylinder extend pin
#define ver_cylinder_ret    27//vertical cylinder retract pin
#define hor_cylinder_ext    35//horizontal cylinder extend pin
#define hor_cylinder_ret    31//orizontal cylinder retract pin
#define arm_cylinder_ext    33  //arm cylinder extend pin
#define arm_cylinder_ret    29  //arm cylinder retract pin

extern int ver_cylinder_pos;
extern int hor_cylinder_pos;
extern int arm_cylinder_pos;
extern int ver_cylinder_target;
extern int hor_cylinder_target;
extern int arm_cylinder_target;
extern int ver_cylinder_status;
extern int hor_cylinder_status;
extern int arm_cylinder_status;
//**********************************************************************//

// these constants are temporaryily defined for the purpose of testing
//const int SER_Pin = 8;   //pin 14 on the 75HC595
//const int RCLK_Pin = 9;  //pin 12 on the 75HC595
//const int SRCLK_Pin = 10; //pin 11 on the 75HC595
///////////////////////////////////Holding Motor Pins/////////////////////
//#define holding_motor_a        11 //holding motor driver pin a
//#define holding_motor_b        12//holding motor driver pin b
//#define holding_motor_e        13//holding motor driver pin enable
#define pwm        13
#define holdir        11
///////////////////////////////////Clamping pins//////////////////////////
#define carriage_clamp_1        38///Carriage clamping magnet
#define carriage_clamp_2        36//Carriage clamping magnet
#define autobot_holder          25//autobot holding magnet
#define swing_pulling           23//swing pulling mechanism

//holding motor variables
extern int holding_motor_pwm;
extern int holding_motor_status;
// these constants are temporaryily defined for the purpose of testing

void arduConfig();
void clearRegisters();
void setRegisterPin(int,int);
void writeRegisters();
void setModeLED(int);

void ver_cylinder_goto(int);
void hor_cylinder_goto(int);

void signalChild(int);

#endif
