#include "RoboLib.h"
#include "PS2X_lib.h"
#include "SabertoothSimplified.h"

//Saber Definitions
SabertoothSimplified ST1(Serial3);     // Use Serial3 as the serial port.
SabertoothSimplified ST2(Serial2);     // Use Serial2 as the serial port.

void setup()
{
  // initialize the serial communications:
  Serial.begin(9600);
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
  
  if(ps2x.Button(PSB_BLUE))
  ssLoop();
  if (Serial.available()) 
  {
  mode=Serial.read();
  Serial.write(mode);
  }
/*  if(ps2x.Button(PSB_L2)){
  Serial.println("L2 pressed");
  if (mode=='A') mode = 'A';
  else mode--;
  */
  if (mode=='A') ssLoop();
  else if (mode=='B') poleLoop();
  else if (mode=='C') swingLoop();
  else if (mode=='D') gymLoop();
  else if (mode=='E') runLoop();
  else if (mode=='F') adjLoop();
/*  }
  else if(ps2x.Button(PSB_R2)){
  Serial.println("R2 pressed");
  if (mode=='F') mode = 'F';
  else mode++;
  
  if (mode=='A') ssLoop();
  else if (mode=='B') poleLoop();
  else if (mode=='C') swingLoop();
  else if (mode=='D') gymLoop();
  else if (mode=='E') runLoop();
  else if (mode=='F') adjLoop();
  
  }
  // print the sensor values:
  Serial.print(analogRead(xpin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(ypin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(zpin));
  Serial.println();
  // delay before next reading:
  delay(100);
*/
}
