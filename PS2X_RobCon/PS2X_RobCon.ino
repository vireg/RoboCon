#include <SabertoothSimplified.h>
#include <PS2X_lib.h>  //for v1.6

//Black	GND
//Yellow	Attn	10
//Orange	Cmd		11
//Brown	Data	12 (Pullup, 5V)
//Blue	Clk		13
//Pink	Power	3.3V

#define gnd0 47   
#define en0 45
#define vcc0 43
#define a0 39
#define b0 37

#define gnd1 46
#define en1 44
#define vcc1 42
#define a1 38
#define b1 36

#define gnd2 2
#define en2 3
#define vcc2 4
#define a2 6
#define b2 7

#define gnd3 8  
#define en3 9
#define vcc3 10
#define a3 12
#define b3 13

#define pneu1 25
#define pneu2 27
#define pneu3 29
#define pneu4 31

int w,x,y,z;

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;
SabertoothSimplified ST1,ST2;

void setup(){
 Serial.begin(9600);
  SabertoothTXPinSerial.begin(9600); // This is the baud rate you chose with the DIP switches.
 
  pinMode(vcc0,OUTPUT);
  pinMode(vcc1,OUTPUT);
  pinMode(vcc2,OUTPUT);
  pinMode(vcc3,OUTPUT);
  
  pinMode(gnd0,OUTPUT);
  pinMode(gnd1,OUTPUT);
  pinMode(gnd2,OUTPUT);
  pinMode(gnd3,OUTPUT);
 
  digitalWrite(vcc0,HIGH);
  digitalWrite(vcc1,HIGH);
  digitalWrite(vcc2,HIGH);
  digitalWrite(vcc3,HIGH);
  
  digitalWrite(gnd0,LOW);
  digitalWrite(gnd1,LOW);
  digitalWrite(gnd2,LOW);
  digitalWrite(gnd3,LOW);
  
  pinMode(en0,OUTPUT);
  pinMode(a0,OUTPUT);
  pinMode(b0,OUTPUT);
  
  pinMode(en1,OUTPUT);
  pinMode(a1,OUTPUT);
  pinMode(b1,OUTPUT);
  
  pinMode(en2,OUTPUT);
  pinMode(a2,OUTPUT);
  pinMode(b2,OUTPUT);
  
  pinMode(en3,OUTPUT);
  pinMode(a3,OUTPUT);
  pinMode(b3,OUTPUT);
  
  pinMode(pneu1,OUTPUT);
  pinMode(pneu2,OUTPUT);
  pinMode(pneu3,OUTPUT);
  pinMode(pneu4,OUTPUT);

 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
 error = ps2x.config_gamepad(24,30,32,28,true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
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

void loop(){
   /* You must Read Gamepad to get new values
   Read GamePad and set vibration values
   ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values
   
   you should call this at least once a second
   */
   
   
   
 if(error == 1) //skip loop if no controller found
  return; 
  
 if(type == 2){ //Guitar Hero Controller
   
   ps2x.read_gamepad();          //read controller 
   
   if(ps2x.ButtonPressed(GREEN_FRET))
     Serial.println("Green Fret Pressed");
   if(ps2x.ButtonPressed(RED_FRET))
     Serial.println("Red Fret Pressed");
   if(ps2x.ButtonPressed(YELLOW_FRET))
     Serial.println("Yellow Fret Pressed");
   if(ps2x.ButtonPressed(BLUE_FRET))
     Serial.println("Blue Fret Pressed");
   if(ps2x.ButtonPressed(ORANGE_FRET))
     Serial.println("Orange Fret Pressed");
     

    if(ps2x.ButtonPressed(STAR_POWER))
     Serial.println("Star Power Command");
    
    if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed
     Serial.println("Up Strum");
    if(ps2x.Button(DOWN_STRUM))
     Serial.println("DOWN Strum");
  
 
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");

    
    if(ps2x.Button(ORANGE_FRET)) // print stick value IF TRUE
    {
        Serial.print("Wammy Bar Position:");
        Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
    } 
 }

 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
         
     if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      }
      if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("DOWN held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      }   
  
    
      vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                              //how hard you press the blue (X) button    
    
    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {
     
       
         
        if(ps2x.Button(PSB_L3))
         Serial.println("L3 pressed");
        if(ps2x.Button(PSB_R3))
         Serial.println("R3 pressed");
        if(ps2x.Button(PSB_L2))
         Serial.println("L2 pressed");
        if(ps2x.Button(PSB_R2))
         Serial.println("R2 pressed");
     //   if(ps2x.Button(PSB_GREEN))
       //  Serial.println("Triangle pressed");
         
    }   
         
    
    //if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
  //       Serial.println("Circle just pressed");
         
    //if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
      //   Serial.println("Square just released");     
    
  //  if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
    //     Serial.println("X just changed");    
    
    
//  if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
//    {
//        Serial.print("Stick Values:");
//        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
//        Serial.print(",");
//        Serial.print(ps2x.Analog(PSS_LX), DEC); 
//        Serial.print(",");
//        Serial.print(ps2x.Analog(PSS_RY), DEC); 
//        Serial.print(",");
//        Serial.println(ps2x.Analog(PSS_RX), DEC); 
//    } 

      if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)){  //pullup PNEUMATIC0
          if(ps2x.Button(PSB_GREEN)) {
  //         //will be TRUE if button was JUST pressed
           Serial.println(F("VUP"));
           digitalWrite(pneu1,HIGH);
          }
        
         if(ps2x.Button(PSB_BLUE)) {
  //         //will be TRUE if button was JUST pressed
           Serial.println(F("VD"));
           digitalWrite(pneu2,HIGH);
          }
          
         if(ps2x.Button(PSB_RED)) {
  //         //will be TRUE if button was JUST pressed
           Serial.println(F("HOUT"));
           digitalWrite(pneu3,HIGH);
          }
        
         if(ps2x.Button(PSB_PINK)) {
  //         //will be TRUE if button was JUST pressed
           Serial.println(F("HIN"));
           digitalWrite(pneu4,HIGH);
          }
      }
      
      if(ps2x.Button(PSB_PAD_DOWN)) {
  //         //will be TRUE if button was JUST pressed
           Serial.println(F("STOP"));
           pist_stop();
      }
               
          
        if(1)
    {  //3
        //Serial.print(F("Stick Values:"));
        //Serial.print(ps2x.Analog(PSS_LY), DEC);       //Left stick, Y axis. Other options: LX, RY, RX 
        y=ps2x.Analog(PSS_RY);
        x=ps2x.Analog(PSS_LX);
       if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)){  //Loop1
       if(x>=0 && x<100 && y>=0 && y<100) {
         nWest(127);  //L,U
       }
       else if(x>155 && x<=255 && y>=0 && y<100) {
         nEast(127);  //R,U
       }
       else if(x>=0 && x<100 && y>155 && y<=255) {
         sWest(127);  //L,D
       }
       else if(x>155 && x<=255 && y>155 && y<=255) {
         sEast(127);  //R,D
       }
       else if(ps2x.Button(PSB_PAD_RIGHT)){
        tcw();
        }
      else if(ps2x.Button(PSB_PAD_LEFT)){
        tccw();
        }
       }  //Loop1
              else if(x>=0 && x<100) {
                xLEFT(x);
              }
              else if(x>155 && x<=255) {
                xRIGHT(x);
              }
              else if(y>=0 && y<100) {
                yUP(y);
              }
              else if(y>155 && y<=255) {
                yDOWN(y);
              }
              else {
                 neutral();
              }              
        //}  //2
        if(ps2x.ButtonPressed(PSB_BLUE))
      {
        neutral();
      } 
      
    }  //3
      
      
}  //4


delay(50);
     
}

void yUP(int y)
{
//  int t0=map(y,0,100,255,0);
  int t0=map(y,0,100,127,0);
  ST1.motor(1, t0);
  ST1.motor(2, t0);
  ST2.motor(1, t0);
  ST2.motor(2, t0);
                //neutral();
//                digitalWrite(a0,LOW); digitalWrite(b0,HIGH); analogWrite(en0,t0);
//                digitalWrite(a1,HIGH); digitalWrite(b1,LOW); analogWrite(en1,t0);
//                digitalWrite(a2,LOW);digitalWrite(b2,HIGH);analogWrite(en2,t0);
//                digitalWrite(a3,LOW);digitalWrite(b3,HIGH);analogWrite(en3,t0);
//                Serial.println(y);
                  Serial.println("Up");
}

void yDOWN(int y)
{
  int t0=map(y,155,255,0,-127);
  ST1.motor(1, t0);
  ST1.motor(2, t0);
  ST2.motor(1, t0);
  ST2.motor(2, t0);
//                int t0=map(y,155,255,0,255);
//                digitalWrite(a0,HIGH);digitalWrite(b0,LOW); analogWrite(en0,t0);
//                digitalWrite(a1,LOW);digitalWrite(b1,HIGH);analogWrite(en1,t0);
//                digitalWrite(a2,HIGH);digitalWrite(b2,LOW);analogWrite(en2,t0);
//                digitalWrite(a3,HIGH);digitalWrite(b3,LOW);analogWrite(en3,t0);
                  Serial.println("Down");
}

void xLEFT(int x)
{
  int t0=map(y,0,100,127,0);
  int t1=map(y,155,255,0,-127);
  ST1.motor(1, t0);
  ST1.motor(2, t1);
  ST2.motor(1, t1);
  ST2.motor(2, t0);
//                int t0=map(x,0,100,255,0);
//                digitalWrite(a0,LOW);digitalWrite(b0,HIGH);analogWrite(en0,t0);
//                digitalWrite(a1,LOW);digitalWrite(b1,HIGH);analogWrite(en1,t0);
//                digitalWrite(a2,HIGH);digitalWrite(b2,LOW);analogWrite(en2,t0);
//                digitalWrite(a3,LOW);digitalWrite(b3,HIGH);analogWrite(en3,t0);
//                Serial.println(x);
                  Serial.println("LEFT");
}

void xRIGHT(int x)
{
  int t0=map(y,0,100,127,0);
  int t1=map(y,155,255,0,-127);
  ST1.motor(1, t1);
  ST1.motor(2, t0);
  ST2.motor(1, t0);
  ST2.motor(2, t1);
//                int t0=map(x,155,255,0,255);
//                digitalWrite(a0,HIGH);digitalWrite(b0,LOW);analogWrite(en0,t0);    
//                digitalWrite(a1,HIGH);digitalWrite(b1,LOW);analogWrite(en1,t0);
//                digitalWrite(a2,LOW);digitalWrite(b2,HIGH);analogWrite(en2,t0);
//                digitalWrite(a3,HIGH);digitalWrite(b3,LOW);analogWrite(en3,t0);
//                Serial.println(x);
                  Serial.println("RIGHT");
}

void nWest(int t0)  //1,3
{
                digitalWrite(a0,LOW);digitalWrite(b0,HIGH);analogWrite(en0,180);
                digitalWrite(a1,LOW);digitalWrite(b1,LOW);analogWrite(en1,0);
                analogWrite(en2,0);
                digitalWrite(a3,LOW);digitalWrite(b3,HIGH);analogWrite(en3,180);
                Serial.println("nWest"); 
}

void nEast(int t0)  //0,2
{
                digitalWrite(a0,LOW);digitalWrite(b0,LOW);analogWrite(en0,0);
                digitalWrite(a1,HIGH);digitalWrite(b1,LOW);analogWrite(en1,180);
                digitalWrite(a2,LOW);digitalWrite(b2,HIGH);analogWrite(en2,180);
                analogWrite(en3,0);
                Serial.println("nEast");          
}

void sWest(int t0)  //0,2
{
                digitalWrite(a0,LOW);digitalWrite(b0,LOW);analogWrite(en0,0);
                digitalWrite(a1,LOW);digitalWrite(b1,HIGH);analogWrite(en1,180);
                digitalWrite(a2,HIGH);digitalWrite(b2,LOW);analogWrite(en2,180);
                analogWrite(en3,0);
                Serial.println("sWest"); 
}

void sEast(int t0)  //1,3
{
                digitalWrite(a0,HIGH);digitalWrite(b0,LOW);analogWrite(en0,180);
                digitalWrite(a1,LOW);digitalWrite(b1,LOW);analogWrite(en1,0);
                analogWrite(en2,0);
                digitalWrite(a3,HIGH);digitalWrite(b3,LOW);analogWrite(en3,180);
                Serial.println("sEast"); 
}

void tcw()
{
  int t0=127;
                //neutral();
                digitalWrite(a0,HIGH); digitalWrite(b0,LOW); analogWrite(en0,t0);
                digitalWrite(a1,LOW); digitalWrite(b1,HIGH); analogWrite(en1,t0);
                digitalWrite(a2,LOW);digitalWrite(b2,HIGH);analogWrite(en2,t0);
                digitalWrite(a3,LOW);digitalWrite(b3,HIGH);analogWrite(en3,t0);
                Serial.println("CW");
}

void tccw()
{
  int t0=127;
                //neutral();
                digitalWrite(a0,LOW); digitalWrite(b0,HIGH); analogWrite(en0,t0);
                digitalWrite(a1,HIGH); digitalWrite(b1,LOW); analogWrite(en1,t0);
                digitalWrite(a2,HIGH);digitalWrite(b2,LOW);analogWrite(en2,t0);
                digitalWrite(a3,HIGH);digitalWrite(b3,LOW);analogWrite(en3,t0);
                Serial.println("CCW");
}

void brake()
{
 Serial.println("Brake");
 digitalWrite(a2,HIGH);digitalWrite(b2,HIGH);analogWrite(en2,0);
 digitalWrite(a1,HIGH);digitalWrite(b1,HIGH);analogWrite(en1,0);
 digitalWrite(a3,HIGH);digitalWrite(b3,HIGH);analogWrite(en3,0);
 digitalWrite(a0,HIGH);digitalWrite(b0,HIGH);analogWrite(en0,0);
}

void neutral()
{
  digitalWrite(a0,LOW);
  digitalWrite(b0,LOW);
  
  digitalWrite(a1,LOW);
  digitalWrite(b1,LOW);
  
  digitalWrite(a2,LOW);
  digitalWrite(b2,LOW);
  
  digitalWrite(a3,LOW);
  digitalWrite(b3,LOW);
  
  Serial.println("neutral");
}

void pist_stop()
{
digitalWrite(pneu1,LOW);
digitalWrite(pneu2,LOW);
digitalWrite(pneu3,LOW);
digitalWrite(pneu4,LOW);
}

