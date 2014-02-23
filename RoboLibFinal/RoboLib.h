#ifndef RoboLib_h
#define RoboLib_h

#include "Arduino.h"
#include "PS2X_lib.h"
#include "SabertoothSimplified.h"

//******************** PS2 controller ********************//
#define PS2_CLK 13
#define PS2_CMD 11
#define PS2_ATTN 10
#define PS2_DAT 12
#define pressures true
#define rumble true
extern int error; 
extern byte type;
extern byte vibrate;
void PS2_setup();
//**********************************************************************//

// these constants are temporaryily defined for the purpose of testing
extern char mode;    //Seesaw, Pole walk, Swing, Jungle gym, Run, Drive adjust
extern bool registers[8];
const int SER_Pin = 8;   //pin 14 on the 75HC595
const int RCLK_Pin = 9;  //pin 12 on the 75HC595
const int SRCLK_Pin = 10; //pin 11 on the 75HC595
extern PS2X ps2x; // create PS2 Controller Class
// these constants are temporaryily defined for the purpose of testing

//Edit pin names as per requirement
#define pin1 1
#define pin2 2
#define pin3 3
#define pin4 4
#define pin5 5
#define pin6 6
#define pin7 7
#define pin8 8
#define pin9 9
#define pin10 10
#define pin11 11
#define pin12 12
#define pin13 13
#define pin14 14
#define pin15 15
#define pin16 16
#define pin17 17
#define pin18 18
#define pin19 19
#define pin20 20
#define pin21 21
#define pin22 22
#define pin23 23
#define pin24 24
#define pin25 25
#define pin26 26
#define pin27 27
#define pin28 28
#define pin29 29
#define pin30 30
#define pin31 31
#define pin32 32
#define pin33 33
#define pin34 34
#define pin35 35
#define pin36 36
#define pin37 37
#define pin38 38
#define pin39 39
#define pin40 40
#define pin41 41
#define pin42 42
#define pin43 43
#define pin44 44
#define pin45 45
#define pin46 46
#define pin47 47
#define pin48 48
#define pin49 49
#define pin50 50
#define pin51 51
#define pin52 52
#define pin53 53
#define pin54 54

void arduConfig();
void clearRegisters();
void setRegisterPin(int,int);
void writeRegisters();
void setModeLED(char);

void ssLoop();
void poleLoop();
void swingLoop();
void gymLoop();
void runLoop();
void adjLoop();

#endif