#include "RoboLib.h"
#include "PS2X_lib.h"
#include "SabertoothSimplified.h"
#include <digitalWriteFast.h>

//////////******************************Legacy Code******************************//////////
#define hall1 00
#define hall2 00
#define hall3 00 
#define hall4 00
#define pneu1 00
#define pneu2 00
#define pneu3 00
#define pneu4 00
int hallvalue1,hallvalue2,hallvalue3,hallvalue4;
int xval,yval;
//////////**********************************************************************//////////

//Saber Definitions
SabertoothSimplified ST1(Serial3);     // Use Serial3 as the serial port.
SabertoothSimplified ST2(Serial2);     // Use Serial2 as the serial port.

int x;  //Joystick X
int y;  //Joystick Y
int t;  //Turning L2,R2
boolean line;  //line present or absent

float x_1;
float y_1;
int deadz=40;
float V_x;  //Sideways Velocity
float V_y;  //Forward Velocity
float V_t;  //Turning velocity
float rot=0.1;  //Rotation Factor for turning while line following
//drive motors
float m1=0;
float m2=0;
float m3=0;
float m4=0;
float divisor;  //divisor  for normalizing

void setup()
{
  // initialize the serial communications:
  Serial.begin(9600);
  arduConfig();
  PS2_setup();
     
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  // Provide ground and power by using the analog inputs as normal
  // digital pins.  This makes it possible to directly connect the
  // breakout board to the Arduino.  If you use the normal 5V and
  // GND pins on the Arduino, you can remove these lines.

  clearRegisters();
  writeRegisters();
}

void loop()
{
  ps2x.read_gamepad(false, vibrate);
  
    if(ps2x.ButtonPressed(PSB_L1))//Mode Toggle Button
  {
    if(mode==4)
      mode=1;
    else
      mode+=1; 
  }

  if(mode==1)                                      //See-Saw
  {
    setModeLED(1);
    Serial.println("Mode 1");
    //See-Saw Mode Module
    if(ps2x.Button(PSB_R1))  //Mode Action ON
    {

      if(ps2x.ButtonPressed(PSB_TRIANGLE))  //go to see saw placing position
      {
        hor_cylinder_target=2;
      }
      if(ps2x.ButtonPressed(PSB_CROSS))  //
      {
        hor_cylinder_target=3;
      }
      if(ps2x.Button(PSB_CIRCLE))  //
      {
        
      }
      if(ps2x.Button(PSB_SQUARE))  //
      {
        
      }
      if(ps2x.Button(PSB_PAD_UP))  //
      {
      }
      if(ps2x.ButtonPressed(PSB_PAD_DOWN))  //AutoBot Holding Magnet ON/OFF
      {
        
      }
      if(ps2x.ButtonPressed(PSB_PAD_LEFT))  //Swing Pulling Mechanism ON/OFF
      {
        sigBot=true;
        sigNo=1;        
      }
      if(ps2x.Button(PSB_PAD_RIGHT))  //
      {
        sigBot=true;
        sigNo=5;
      }
    }
  }

  else if(mode==2)                                  //Swing
  {
    setModeLED(2);
    //Swing Mode Module
    if(ps2x.Button(PSB_R1))  //Mode Action ON
    {
      if(ps2x.Button(PSB_TRIANGLE))  //
      {
      }
      if(ps2x.Button(PSB_CROSS))  //
      {
      }
      if(ps2x.Button(PSB_CIRCLE))  //
      {
      }
      if(ps2x.Button(PSB_SQUARE))  //
      {
      }
      if(ps2x.Button(PSB_PAD_UP))  //
      {
      }
      if(ps2x.ButtonPressed(PSB_PAD_DOWN))  //AutoBot Holding Magnet ON/OFF
      {
      }
      if(ps2x.ButtonPressed(PSB_PAD_LEFT))  //Swing Pulling Mechanism ON/OFF
      {
        sigBot=true;
        sigNo=2;
      }
      if(ps2x.Button(PSB_PAD_RIGHT))  //
      {
        sigBot=true;
        sigNo=5;
      }
    }
  }

  else if(mode==3)                              //Pole Walk
  {
    setModeLED(3);
    //Pole Walk Mode Module
    if(ps2x.Button(PSB_R1))  //Mode Action ON
    {
      if(ps2x.Button(PSB_TRIANGLE))  //
      {
      }
      if(ps2x.Button(PSB_CROSS))  //
      {
      }
      if(ps2x.Button(PSB_CIRCLE))  //
      {
      }
      if(ps2x.Button(PSB_SQUARE))  //
      {
      }
      if(ps2x.Button(PSB_PAD_UP))  //
      {
      }
      if(ps2x.ButtonPressed(PSB_PAD_DOWN))  //AutoBot Holding Magnet ON/OFF
      {
      }
      if(ps2x.ButtonPressed(PSB_PAD_LEFT))  //Swing Pulling Mechanism ON/OFF
      {
        sigBot=true;
        sigNo=3;
      }
      if(ps2x.Button(PSB_PAD_RIGHT))  //
      {
        sigBot=true;
        sigNo=5;
      }
    }
  }

  else if(mode==4)                                //Ladder
  {
    setModeLED(4);
    //Ladder Mode Module
    if(ps2x.Button(PSB_R1))  //Mode Action ON
    {
      if(ps2x.Button(PSB_TRIANGLE))  //
      {
      }
      if(ps2x.Button(PSB_CROSS))  //
      {
      }
      if(ps2x.Button(PSB_CIRCLE))  //
      {
      }
      if(ps2x.Button(PSB_SQUARE))  //
      {
      }
      if(ps2x.Button(PSB_PAD_UP))  //
      {
      }
      if(ps2x.ButtonPressed(PSB_PAD_DOWN))  //AutoBot Holding Magnet ON/OFF
      {
      }
      if(ps2x.ButtonPressed(PSB_PAD_LEFT))  //Swing Pulling Mechanism ON/OFF
      {
        sigBot=true;
        sigNo=4;
      }
      if(ps2x.Button(PSB_PAD_RIGHT))  //
      {
        sigBot=true;
        sigNo=5;
      }
    }
  }

  if(ps2x.Button(PSB_R1)==0)  //Mode Action OFF
  {
    if(ps2x.ButtonPressed(PSB_TRIANGLE))  //Carriage UP
    {
      digitalWriteFast(carriage_clamp_1,LOW);          //Release clamping magnets
      digitalWriteFast(carriage_clamp_2,LOW);          //Release clamping magnets
      digitalWriteFast(ver_cylinder_ext,HIGH);        //Enable pneumatic extension
      ver_cylinder_status=1;
    }
    if(ps2x.ButtonReleased(PSB_TRIANGLE))  //Carriage Stops
    {
      digitalWriteFast(carriage_clamp_1,HIGH);          //Engage clamping magnets
      digitalWriteFast(carriage_clamp_2,HIGH);          //Engage clamping magnets
      digitalWriteFast(ver_cylinder_ext,LOW);          //Disable pneumatic extension
      ver_cylinder_status=0;
    }
    if(ps2x.ButtonPressed(PSB_CROSS))  //Carriage Down
    {
      digitalWriteFast(carriage_clamp_1,LOW);          //Release clamping magnets
      digitalWriteFast(carriage_clamp_2,LOW);          //Release clamping magnets
      digitalWriteFast(ver_cylinder_ret,HIGH);        //Enable pneumatic return
      ver_cylinder_status=-1;
    }
    if(ps2x.ButtonReleased(PSB_CROSS))  //Carriage Stops
    {
      digitalWriteFast(carriage_clamp_1,HIGH);          //Engage clamping magnets
      digitalWriteFast(carriage_clamp_2,HIGH);          //Engage clamping magnets
      digitalWriteFast(ver_cylinder_ret,LOW);          //Enable pneumatic return
      ver_cylinder_status=0;
    }
    if(ps2x.ButtonPressed(PSB_CIRCLE))  //Slider Forward
    {
      digitalWriteFast(hor_cylinder_ext,HIGH);
      hor_cylinder_status=1;
    }
    if(ps2x.ButtonReleased(PSB_CIRCLE))  //Slider Stops
    {
      digitalWriteFast(hor_cylinder_ext,LOW);
      hor_cylinder_status=0;
    }
    if(ps2x.ButtonPressed(PSB_SQUARE))  //Slider Back
    {
      digitalWriteFast(hor_cylinder_ret,HIGH);
      hor_cylinder_status=-1;
    }
    if(ps2x.ButtonReleased(PSB_SQUARE))  //Slider Stops
    {
      digitalWriteFast(hor_cylinder_ret,LOW);
      hor_cylinder_status=0;
    }
    if(ps2x.ButtonPressed(PSB_PAD_UP))  //Motor cylinder Extends
    {
      digitalWriteFast(arm_cylinder_ext,HIGH);
      arm_cylinder_status=1;
    }
    if(ps2x.ButtonReleased(PSB_PAD_UP))  //Motor cylinder stops
    {
      digitalWriteFast(arm_cylinder_ext,LOW);
      arm_cylinder_status=0;
    }
    if(ps2x.ButtonPressed(PSB_PAD_DOWN))  //Motor cylinder Retracts
    {
      digitalWriteFast(arm_cylinder_ret,HIGH);
      arm_cylinder_status=-1;
    }
    if(ps2x.ButtonReleased(PSB_PAD_DOWN))  //Motor cylinder stops
    {
      digitalWriteFast(arm_cylinder_ret,LOW);
      arm_cylinder_status=0;
    }
    if(ps2x.ButtonPressed(PSB_PAD_LEFT))  //Holding Motor CCW
    {
      digitalWriteFast(holding_motor_a,HIGH);
      digitalWriteFast(holding_motor_b,LOW);
      analogWrite(holding_motor_e,holding_motor_pwm);
      holding_motor_status=-1;
    }
    if(ps2x.ButtonReleased(PSB_PAD_LEFT))  //Holding Motor Stops
    {
      digitalWriteFast(holding_motor_a,LOW);
      digitalWriteFast(holding_motor_b,LOW);
      analogWrite(holding_motor_e,0);
      holding_motor_status=0;
    }
    if(ps2x.ButtonPressed(PSB_PAD_RIGHT))  //Holding Motor CW
    {
      digitalWriteFast(holding_motor_a,LOW);
      digitalWriteFast(holding_motor_b,HIGH);
      analogWrite(holding_motor_e,holding_motor_pwm);
      holding_motor_status=1;
    }
    if(ps2x.ButtonReleased(PSB_PAD_RIGHT))  //Holding Motor Stops
    {
      digitalWriteFast(holding_motor_a,LOW);
      digitalWriteFast(holding_motor_b,LOW);
      analogWrite(holding_motor_e,0);
      holding_motor_status=0;
    }
  }
  signalChild(sigNo);
  x=ps2x.Analog(PSS_RX);
  y=ps2x.Analog(PSS_LY);

  if(ps2x.Button(PSB_L2))
    t=-1;
  else if(ps2x.Button(PSB_R2))
    t=1;
  else
    t=0;

  ///////////////////function calls////////////////////

  if(ver_cylinder_target!=ver_cylinder_pos)
  {
    ver_cylinder_goto(ver_cylinder_target);
  }
  if(hor_cylinder_target!=hor_cylinder_pos)
  {
    hor_cylinder_goto(hor_cylinder_target);
  }

  holo_drive( x , y , t , line);

/////////////////////////////////Enable Serial output to Debug the program//////////////////////

  Serial.print(" Carriage Status= ");
  Serial.print(ver_cylinder_status);
  Serial.print(" Carriage Position= ");
  Serial.print(ver_cylinder_pos);
  Serial.print(" Carriage Target= ");
  Serial.print(ver_cylinder_target);
  Serial.print(" Slider Status= ");
  Serial.print(hor_cylinder_status);
  Serial.print(" Slider Position= ");
  Serial.print(hor_cylinder_pos);
  Serial.print(" Slider Target= ");
  Serial.print(hor_cylinder_target);
  Serial.print(" Holding Motor Status= ");
  Serial.print(holding_motor_status);

}

//////////////////holonomic drive function if line is detected, drive changes according to the mode///////////////////
void holo_drive(int x, int y, int t,boolean line)
{

  if(x>=0 && x<(128-deadz/2))
  {
    x_1=(x-(127.5-deadz/2))/(127.5-deadz/2);
  }
  else if(x>128+deadz/2&& x<=256)
  {
    x_1=(x-(127.5+deadz/2))/(127.5-deadz/2);
  }
  else
  {
    x_1 = 0;
  }

  if(y >= 0 && y <(128-deadz/2))
  {
    y_1=-((y-(127.5-deadz/2)) / (127.5-deadz/2));
  }
  else if(y > 128+deadz/2 && y<=256)
  {
    y_1=-((y -(127.5+deadz/2)) / (127.5-deadz/2));
  }
  else
  {
    y_1 = 0;
  }

  if(x_1>=0)  
    V_x = (pow(11,x_1)-1);
  else
    V_x = -pow(11,-x_1)+1;

  if(y_1>=0)
    V_y = pow(11,y_1)-1;
  else
    V_y = -pow(11,-y_1)+1;

  V_t = t;

  if(line)  //Change the drive if line is detected
  {
    if(mode != 2 || mode !=0)
      V_t= V_x*rot;
  }

  m1 = (V_x + V_y + V_t)*12.7;
  m2 = (V_x - V_y + V_t)*12.7;
  m3 = (-V_x - V_y + V_t)*12.7;
  m4 = (-V_x + V_y + V_t)*12.7; 

  if(abs(m1)>127 || abs(m2)>127 || abs(m3)>127 || abs(m4)>127)  //Normalizing the values to counter the overflow
  {
    divisor= max(abs(m1),abs(m2));
    divisor= max(abs(divisor),abs(m3));
    divisor= max(abs(divisor),abs(m4));
    //    divisor= divisor;
    m1= m1*127/divisor;
    m2= m2*127/divisor;
    m3= m3*127/divisor;
    m4= m4*127/divisor;
  }

  ST2.motor(2,(int)m1);
  ST2.motor(1,(int)m2);
  ST1.motor(1,(int)m3);
  ST1.motor(2,(int)m4);

  /*   Serial.print("Divisor ");
   Serial.print(divisor);
   Serial.print(" x_1= ");
   Serial.print(x_1);
   Serial.print(" y_1= ");
   Serial.print(y_1);
   Serial.print(" vx= ");
   Serial.print(V_x);
   Serial.print(" vy = ");      
   Serial.print(V_y);
   Serial.print(" pwm1= ");
   Serial.print((int)m1);
   Serial.print(" pwm2= ");
   Serial.print((int)m2);
   Serial.print(" pwm3= ");
   Serial.print((int)m3);
   Serial.print(" pwm4= ");
   Serial.println((int)m4);
   */
}


