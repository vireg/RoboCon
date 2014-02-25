#include "RoboLib.h"
#include "PS2X_lib.h"
#include "SabertoothSimplified.h"
#include <digitalWriteFast.h>

//Saber Definitions
SabertoothSimplified ST1(Serial3);     // Use Serial3 as the serial port.
SabertoothSimplified ST2(Serial2);     // Use Serial2 as the serial port.

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
  
if(ps2x.ButtonPressed(PSB_R1))//Mode Increment
{
    if(mode==4)
      mode=0;
    else
      mode+=1;
}
  if(ps2x.ButtonPressed(PSB_L1))
  {
    if(mode==1)                                      //See-Saw
    {
      ssLoop();
    }
    else if(mode==2)                                  //Swing
    {
      swingLoop();
    }
    else if(mode==3)                              //Pole Walk
    {
      poleLoop();
    }
    else if(mode==4)                                //Ladder
    {
      gymLoop();
    }
    else
    {
      runLoop();
    }
  }


}
