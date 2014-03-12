#include "Arduino.h"
#include "RoboLib.h"
#include "PS2X_lib.h"
#include "SabertoothSimplified.h"
#include <digitalWriteFast.h>

//******************** Main code ********************//
unsigned int mode = 0;    //Seesaw, Pole walk, Swing, Jungle gym, Run, Drive adjust
bool registers[8];
bool sigBot=false;
int sigNo=0;
//**********************************************************************//

//******************** PS2 controller ********************//
int error = 0; 
byte type = 0;
byte vibrate = 0;
PS2X ps2x; // create PS2 Controller Class
//**********************************************************************//

//******************** Pneumatics ********************//
int ver_cylinder_pos=0;
int hor_cylinder_pos=0;
int arm_cylinder_pos=1;
int ver_cylinder_target=0;
int hor_cylinder_target=0;
int arm_cylinder_target=1;
int ver_cylinder_status=0;
int hor_cylinder_status=0;
int arm_cylinder_status=0;
//**********************************************************************//

int holding_motor_pwm=150;
int holding_motor_status=0;

//////////******************************Legacy Code******************************//////////
//////////**********************************************************************//////////

/*
Configure pins of arduino as either INPUT/OUTPUT and initialize them as either HIGH/LOW. Comment out pins not in use.
*/
void arduConfig()
{
    pinMode(ver_hall_1,INPUT);
    pinMode(ver_hall_2,INPUT);
    pinMode(ver_hall_3,INPUT);
    pinMode(ver_hall_4,INPUT);
    pinMode(hor_hall_1,INPUT);
    pinMode(hor_hall_2,INPUT);
    pinMode(hor_hall_3,INPUT);
    pinMode(hor_hall_4,INPUT);
    pinMode(ver_cylinder_ext,OUTPUT);
    pinMode(ver_cylinder_ret,OUTPUT);
    pinMode(hor_cylinder_ext,OUTPUT);
    pinMode(hor_cylinder_ret,OUTPUT);
    pinMode(arm_cylinder_ext,OUTPUT);
    pinMode(arm_cylinder_ret,OUTPUT);
    pinMode(pin15,OUTPUT);
    pinMode(pin16,OUTPUT);
    pinMode(pin17,OUTPUT);
    pinMode(pin18,OUTPUT);
    pinMode(pin19,OUTPUT);
    pinMode(pin20,OUTPUT);
    pinMode(pin21,OUTPUT);
    pinMode(pin22,OUTPUT);
    pinMode(pin23,OUTPUT);
    pinMode(pin24,OUTPUT);
    pinMode(pin25,OUTPUT);
    pinMode(pin26,OUTPUT);
    pinMode(pin27,OUTPUT);
    pinMode(pin28,OUTPUT);
    pinMode(pin29,OUTPUT);
    pinMode(pin30,OUTPUT);
    pinMode(pin31,OUTPUT);
    pinMode(pin32,OUTPUT);
    pinMode(pin33,OUTPUT);
    pinMode(pin34,OUTPUT);
    pinMode(pin35,OUTPUT);
    pinMode(pin36,OUTPUT);
    pinMode(pin37,OUTPUT);
    pinMode(pin38,OUTPUT);
    pinMode(pin39,OUTPUT);
    pinMode(pin40,OUTPUT);
    pinMode(pin41,OUTPUT);
    pinMode(pin42,OUTPUT);
    pinMode(pin43,OUTPUT);
    pinMode(pin44,OUTPUT);
    pinMode(pin45,OUTPUT);
    pinMode(pin46,OUTPUT);
    pinMode(pin47,OUTPUT);
    pinMode(pin48,OUTPUT);
    pinMode(pin49,OUTPUT);
    pinMode(pin50,OUTPUT);
    pinMode(pin51,OUTPUT);
    pinMode(pin52,OUTPUT);
    pinMode(pin53,OUTPUT);
    pinMode(pin54,OUTPUT);
    
    digitalWrite(pin1,HIGH);
    digitalWrite(pin2,HIGH);
    digitalWrite(pin3,HIGH);
    digitalWrite(pin4,HIGH);
    digitalWrite(pin5,HIGH);
    digitalWrite(pin6,HIGH);
    digitalWrite(pin7,HIGH);
    digitalWrite(pin8,HIGH);
    digitalWrite(pin9,HIGH);
    digitalWrite(pin10,HIGH);
    digitalWrite(pin11,HIGH);
    digitalWrite(pin12,HIGH);
    digitalWrite(pin13,HIGH);
    digitalWrite(pin14,HIGH);
    digitalWrite(pin15,HIGH);
    digitalWrite(pin16,HIGH);
    digitalWrite(pin17,HIGH);
    digitalWrite(pin18,HIGH);
    digitalWrite(pin19,HIGH);
    digitalWrite(pin20,HIGH);
    digitalWrite(pin21,HIGH);
    digitalWrite(pin22,HIGH);
    digitalWrite(pin23,HIGH);
    digitalWrite(pin24,HIGH);
    digitalWrite(pin25,HIGH);
    digitalWrite(pin26,HIGH);
    digitalWrite(pin27,HIGH);
    digitalWrite(pin28,HIGH);
    digitalWrite(pin29,HIGH);
    digitalWrite(pin30,HIGH);
    digitalWrite(pin31,HIGH);
    digitalWrite(pin32,HIGH);
    digitalWrite(pin33,HIGH);
    digitalWrite(pin34,HIGH);
    digitalWrite(pin35,HIGH);
    digitalWrite(pin36,HIGH);
    digitalWrite(pin37,HIGH);
    digitalWrite(pin38,HIGH);
    digitalWrite(pin39,HIGH);
    digitalWrite(pin40,HIGH);
    digitalWrite(pin41,HIGH);
    digitalWrite(pin42,HIGH);
    digitalWrite(pin43,HIGH);
    digitalWrite(pin44,HIGH);
    digitalWrite(pin45,HIGH);
    digitalWrite(pin46,HIGH);
    digitalWrite(pin47,HIGH);
    digitalWrite(pin48,HIGH);
    digitalWrite(pin49,HIGH);
    digitalWrite(pin50,HIGH);
    digitalWrite(pin51,HIGH);
    digitalWrite(pin52,HIGH);
    digitalWrite(pin53,HIGH);
    digitalWrite(pin54,HIGH);
}

void PS2_setup()
{
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATTN, PS2_DAT, pressures, rumble);
  if(error == 0) Serial.println("Found Controller, configured successful");
  else if(error == 1) Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
  else if(error == 2) Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  else if(error == 3) Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
}
     
/////******************************************************************************************/////
void clearRegisters(){
  for(int i = 7; i>=0; i--){
     registers[i] = HIGH;
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////

/////******************************************************************************************/////
void setRegisterPin(int index, int value){
  registers[index-1] = value;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

/////******************************************************************************************/////
void writeRegisters(){
  digitalWrite(RCLK_Pin, LOW);
  for(int i = 7; i>=0; i--){
    digitalWrite(SRCLK_Pin, LOW);
    
    int val = registers[i];
    digitalWrite(SER_Pin, val);
    
    digitalWrite(SRCLK_Pin, HIGH);
  }
  digitalWrite(RCLK_Pin, HIGH);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

/////******************************************************************************************/////
void setModeLED(unsigned int modeLED)
{
  if(modeLED==0){
  setRegisterPin(1, LOW);
  setRegisterPin(2, HIGH);
  setRegisterPin(3, HIGH);
  setRegisterPin(4, HIGH);
  setRegisterPin(5, HIGH);
  setRegisterPin(6, HIGH);
  setRegisterPin(7, HIGH);
  setRegisterPin(8, HIGH);
  }
  else if(modeLED==1){
  setRegisterPin(1, HIGH);
  setRegisterPin(2, LOW);
  setRegisterPin(3, HIGH);
  setRegisterPin(4, HIGH);
  setRegisterPin(5, HIGH);
  setRegisterPin(6, HIGH);
  setRegisterPin(7, HIGH);
  setRegisterPin(8, HIGH);
  }
  else if(modeLED==2){
  setRegisterPin(1, HIGH);
  setRegisterPin(2, HIGH);
  setRegisterPin(3, LOW);
  setRegisterPin(4, HIGH);
  setRegisterPin(5, HIGH);
  setRegisterPin(6, HIGH);
  setRegisterPin(7, HIGH);
  setRegisterPin(8, HIGH);
  }
  else if(modeLED==3){
  setRegisterPin(1, HIGH);
  setRegisterPin(2, HIGH);
  setRegisterPin(3, HIGH);
  setRegisterPin(4, LOW);
  setRegisterPin(5, HIGH);
  setRegisterPin(6, HIGH);
  setRegisterPin(7, HIGH);
  setRegisterPin(8, HIGH);
  }
  else if(modeLED==4){
  setRegisterPin(1, HIGH);
  setRegisterPin(2, HIGH);
  setRegisterPin(3, HIGH);
  setRegisterPin(4, HIGH);
  setRegisterPin(5, LOW);
  setRegisterPin(6, HIGH);
  setRegisterPin(7, HIGH);
  setRegisterPin(8, HIGH);
  }
  /*
  else if(modeLED==5){
  setRegisterPin(1, HIGH);
  setRegisterPin(2, HIGH);
  setRegisterPin(3, HIGH);
  setRegisterPin(4, HIGH);
  setRegisterPin(5, HIGH);
  setRegisterPin(6, LOW);
  setRegisterPin(7, HIGH);
  setRegisterPin(8, HIGH);
  }*/
  writeRegisters();
}
////////////////////////////////////////////////////////////////////////////////////////////////////

/////******************************************************************************************/////
void ssLoop()
{
    setModeLED(1);
    ps2x.read_gamepad(false, vibrate);
if(ps2x.Button(PSB_L1))
if(ps2x.Button(PSB_R1))

if(ps2x.Button(PSB_PAD_UP))
if(ps2x.Button(PSB_PAD_RIGHT))
if(ps2x.Button(PSB_PAD_DOWN))
if(ps2x.Button(PSB_PAD_LEFT))

if(ps2x.Button(PSB_GREEN))
if(ps2x.ButtonPressed(PSB_RED))
if(ps2x.ButtonReleased(PSB_PINK))
if(ps2x.NewButtonState(PSB_BLUE));

    ver_cylinder_goto(0);
    hor_cylinder_goto(0);
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////

/////******************************************************************************************/////
void swingLoop()
{
  setModeLED(2);
  ps2x.read_gamepad(false, vibrate);
if(ps2x.Button(PSB_L1))
if(ps2x.Button(PSB_R1))

if(ps2x.Button(PSB_PAD_UP))
if(ps2x.Button(PSB_PAD_RIGHT))
if(ps2x.Button(PSB_PAD_DOWN))
if(ps2x.Button(PSB_PAD_LEFT))

if(ps2x.Button(PSB_GREEN))
if(ps2x.ButtonPressed(PSB_RED))
if(ps2x.ButtonReleased(PSB_PINK))
if(ps2x.NewButtonState(PSB_BLUE));

}
////////////////////////////////////////////////////////////////////////////////////////////////////

/////******************************************************************************************/////
void poleLoop()
{
  setModeLED(3);
  ps2x.read_gamepad(false, vibrate);
if(ps2x.Button(PSB_L1))
if(ps2x.Button(PSB_R1))

if(ps2x.Button(PSB_PAD_UP))
if(ps2x.Button(PSB_PAD_RIGHT))
if(ps2x.Button(PSB_PAD_DOWN))
if(ps2x.Button(PSB_PAD_LEFT))

if(ps2x.Button(PSB_GREEN))
if(ps2x.ButtonPressed(PSB_RED))
if(ps2x.ButtonReleased(PSB_PINK))
if(ps2x.NewButtonState(PSB_BLUE));

}
////////////////////////////////////////////////////////////////////////////////////////////////////

/////******************************************************************************************/////
void gymLoop()
{
  setModeLED(4);
  ps2x.read_gamepad(false, vibrate);
if(ps2x.Button(PSB_L1))
if(ps2x.Button(PSB_R1))

if(ps2x.Button(PSB_PAD_UP))
if(ps2x.Button(PSB_PAD_RIGHT))
if(ps2x.Button(PSB_PAD_DOWN))
if(ps2x.Button(PSB_PAD_LEFT))

if(ps2x.Button(PSB_GREEN))
if(ps2x.ButtonPressed(PSB_RED))
if(ps2x.ButtonReleased(PSB_PINK))
if(ps2x.NewButtonState(PSB_BLUE));

}
////////////////////////////////////////////////////////////////////////////////////////////////////

/////******************************************************************************************/////
void runLoop()
{
  setModeLED(0);
  ps2x.read_gamepad(false, vibrate);
if(ps2x.Button(PSB_L1))
if(ps2x.Button(PSB_R1))

if(ps2x.Button(PSB_PAD_UP))
if(ps2x.Button(PSB_PAD_RIGHT))
if(ps2x.Button(PSB_PAD_DOWN))
if(ps2x.Button(PSB_PAD_LEFT))

if(ps2x.Button(PSB_GREEN))
if(ps2x.ButtonPressed(PSB_RED))
if(ps2x.ButtonReleased(PSB_PINK))
if(ps2x.NewButtonState(PSB_BLUE));

}
////////////////////////////////////////////////////////////////////////////////////////////////////

/////******************************************************************************************/////
void adjLoop()
{
  setModeLED(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void signalChild(int sigNum)
{
  if(sigNum==1) analogWrite(commpin,commsaw);
  else if(sigNum==2) analogWrite(commpin,commswing);
  else if(sigNum==3) analogWrite(commpin,commpole);
  else if(sigNum==4) analogWrite(commpin,commgym);
  else if(sigNum==5) analogWrite(commpin,commsigd);
  else analogWrite(commpin,0);
}
//////////////////////////////////////////    VERTICAL CYLINDER FUNCTION    ////////////////////////

void ver_cylinder_goto(int ver_cylinder_target)
{
  switch(ver_cylinder_target)
  {

  case 1:            //if target is 1 i.e. base
    if(ver_cylinder_pos>1)
    {
      if(digitalReadFast(ver_hall_1)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(ver_cylinder_ret,HIGH);    //Retract
      }
      else
      {
        digitalWriteFast(ver_cylinder_ret,LOW);     //Piston Stops Retraction
        ver_cylinder_pos=1;                      //Position Reached
      }
    }
    else if(ver_cylinder_pos<1)
    {
      if(digitalReadFast(ver_hall_1)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(ver_cylinder_ext,HIGH);    //extend
      }
      else
      {
        digitalWriteFast(ver_cylinder_ext,LOW);     //Piston Stops extension
        ver_cylinder_pos=1;                      //Position Reached
      }
    }
    break;                                //break after case 1


  case 2:            //if target is 2
    if(ver_cylinder_pos>2)
    {
      if(digitalReadFast(ver_hall_2)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(ver_cylinder_ret,HIGH);    //Retract
      }
      else
      {
        digitalWriteFast(ver_cylinder_ret,LOW);     //Piston Stops Retraction
        ver_cylinder_pos=2;                      //Position Reached
      }
    }
    else if(ver_cylinder_pos<2)
    {
      if(digitalReadFast(ver_hall_2)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(ver_cylinder_ext,HIGH);    //extend
      }
      else
      {
        digitalWriteFast(ver_cylinder_ext,LOW);     //Piston Stops extension
        ver_cylinder_pos=2;                      //Position Reached
      }
    }
    break;                                //break after case 2


  case 3:            //if target is 3
    if(ver_cylinder_pos>3)
    {
      if(digitalReadFast(ver_hall_3)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(ver_cylinder_ret,HIGH);    //Retract
      }
      else
      {
        digitalWriteFast(ver_cylinder_ret,LOW);     //Piston Stops Retraction
        ver_cylinder_pos=3;                      //Position Reached
      }
    }
    else if(ver_cylinder_pos<3)
    {
      if(digitalReadFast(ver_hall_3)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(ver_cylinder_ext,HIGH);    //extend
      }
      else
      {
        digitalWriteFast(ver_cylinder_ext,LOW);     //Piston Stops extension
        ver_cylinder_pos=3;                      //Position Reached
      }
    }
    break;                                //break after case 3

  case 4:            //if target is 4 i.e. top
    if(ver_cylinder_pos>4)
    {
      if(digitalReadFast(ver_hall_4)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(ver_cylinder_ret,HIGH);    //Retract
      }
      else
      {
        digitalWriteFast(ver_cylinder_ret,LOW);     //Piston Stops Retraction
        ver_cylinder_pos=4;                      //Position Reached
      }
    }
    else if(ver_cylinder_pos<4)
    {
      if(digitalReadFast(ver_hall_4)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(ver_cylinder_ext,HIGH);    //extend
      }
      else
      {
        digitalWriteFast(ver_cylinder_ext,LOW);     //Piston Stops extension
        ver_cylinder_pos=4;                      //Position Reached
      }
    }
    break;                                //break after case 4

  }
}

////////////////////////      HORIZONTAL CYLINDER FUNCTION    //////////////////////////////////
void hor_cylinder_goto(int hor_cylinder_target)            
{
  switch(hor_cylinder_target)
  {

  case 1:            //if target is 1 i.e. base
    if(hor_cylinder_pos>1)
    {
      if(digitalReadFast(hor_hall_1)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(hor_cylinder_ret,HIGH);    //Retract
      }
      else
      {
        digitalWriteFast(hor_cylinder_ret,LOW);     //Piston Stops Retraction
        hor_cylinder_pos=1;                      //Position Reached
      }
    }
    else if(hor_cylinder_pos<1)
    {
      if(digitalReadFast(hor_hall_1)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(hor_cylinder_ext,HIGH);    //extend
      }
      else
      {
        digitalWriteFast(hor_cylinder_ext,LOW);     //Piston Stops extension
        hor_cylinder_pos=1;                      //Position Reached
      }
    }
    break;                                //break after case 1


  case 2:            //if target is 2
    if(hor_cylinder_pos>2)
    {
      if(digitalReadFast(hor_hall_2)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(hor_cylinder_ret,HIGH);    //Retract
      }
      else
      {
        digitalWriteFast(hor_cylinder_ret,LOW);     //Piston Stops Retraction
        hor_cylinder_pos=2;                      //Position Reached
      }
    }
    else if(hor_cylinder_pos<2)
    {
      if(digitalReadFast(hor_hall_2)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(hor_cylinder_ext,HIGH);    //extend
      }
      else
      {
        digitalWriteFast(hor_cylinder_ext,LOW);     //Piston Stops extension
        hor_cylinder_pos=2;                      //Position Reached
      }
    }
    break;                                //break after case 2


  case 3:            //if target is 3
    if(hor_cylinder_pos>3)
    {
      if(digitalReadFast(hor_hall_3)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(hor_cylinder_ret,HIGH);    //Retract
      }
      else
      {
        digitalWriteFast(hor_cylinder_ret,LOW);     //Piston Stops Retraction
        hor_cylinder_pos=3;                      //Position Reached
      }
    }
    else if(hor_cylinder_pos<3)
    {
      if(digitalReadFast(hor_hall_3)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(hor_cylinder_ext,HIGH);    //extend
      }
      else
      {
        digitalWriteFast(hor_cylinder_ext,LOW);     //Piston Stops extension
        hor_cylinder_pos=3;                      //Position Reached
      }
    }
    break;                                //break after case 3

  case 4:            //if target is 4 i.e. top
    if(hor_cylinder_pos>4)
    {
      if(digitalReadFast(hor_hall_4)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(hor_cylinder_ret,HIGH);    //Retract
      }
      else
      {
        digitalWriteFast(hor_cylinder_ret,LOW);     //Piston Stops Retraction
        hor_cylinder_pos=4;                      //Position Reached
      }
    }
    else if(hor_cylinder_pos<4)
    {
      if(digitalReadFast(hor_hall_4)==HIGH)  //read appropriate sensor, if its not detecting
      {
        digitalWriteFast(hor_cylinder_ext,HIGH);    //extend
      }
      else
      {
        digitalWriteFast(hor_cylinder_ext,LOW);     //Piston Stops extension
        hor_cylinder_pos=4;                      //Position Reached
      }
    }
    break;                                //break after case 4

  }
}


