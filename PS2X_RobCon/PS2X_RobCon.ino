#include "PS2X_lib.h"  //for v1.6

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.

#define dir1 5
#define pwm1 4
#define brk1 

#define dir2 36
#define pwm2 38 
#define brk2

#define vcc1 3
#define gnd1 6
#define vcc2 40
#define gnd2 34

#define dir3 26
#define pwm3 24
#define brk3
#define vcc3 28
#define gnd3 22

#define dir4
#define pwm4
#define brk4
#define vcc4
#define gnd4

#define p1 14 
#define n1 15
#define p2 16
#define n2 18
#define cg 19

int w,x,y,z,t0,t1,t2,t3;

int error = 0; 
byte type = 0;
byte vibrate = 0;
int write;
 
void setup(){
  pinMode(dir1,OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(vcc1,OUTPUT);
  pinMode(gnd1,OUTPUT);

  pinMode(dir2,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(vcc2,OUTPUT);
  pinMode(gnd2,OUTPUT);
  
  pinMode(dir3,OUTPUT);
  pinMode(pwm3,OUTPUT);
  pinMode(vcc3,OUTPUT);
  pinMode(gnd3,OUTPUT);
  
  pinMode(p1,OUTPUT);
  pinMode(n1,OUTPUT);
  pinMode(p2,OUTPUT);
  pinMode(n2,OUTPUT);
  pinMode(cg,OUTPUT);
  
digitalWrite(vcc1,HIGH);
digitalWrite(vcc2,HIGH);
digitalWrite(gnd1,HIGH);
digitalWrite(gnd2,HIGH);
digitalWrite(cg,LOW);

Serial.begin(9600);
pinMode(9,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT); 
pinMode(8,INPUT);

 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
 error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
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
    
  // digitalWrite(vcc,HIGH);
   
 if(error == 1) //skip loop if no controller found
  return; 

 else { //DualShock Controller  //4
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
         /*
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
      if(ps2x.Button(PSB_GREEN)){
       Serial.print("DOWN held this hard: ");
     Serial.println(ps2x.Analog(PSB_GREEN), DEC);
      }   
  */
    
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
        if(ps2x.Button(PSB_GREEN)){
         Serial.println("Triangle pressed");
        /*analogWrite(pwm1,0);
        analogWrite(pwm2,0);
        analogWrite(pwm3,0);
        digitalWrite(p1,LOW);
        digitalWrite(p2,LOW);
        digitalWrite(n1,LOW);
        digitalWrite(n2,LOW);*/
        }
         
    }   
         
    
    if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
         Serial.println("Circle just pressed");
         
    if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
         Serial.println("Square just released");     
    
    if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
         Serial.println("X just changed");    
    
 
// ###############################################################################################
//MOTOR CODE

//Assign Pins
// 30,31,32,33 
// 34,35,36,37
// 38,38,40,41
// 42,43,44,45

 
   // if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {  //3
        //Serial.print("Stick Values:");
        //Serial.print(ps2x.Analog(PSS_LY), DEC);       //Left stick, Y axis. Other options: LX, RY, RX  
        y=ps2x.Analog(PSS_RY);
        z=ps2x.Analog(PSS_LX);
        x=ps2x.Analog(PSAB_PAD_DOWN);
        w=ps2x.Analog(PSAB_PAD_UP);
        if(x){
          digitalWrite(dir2,HIGH);digitalWrite(dir1,HIGH);digitalWrite(dir3,HIGH);
        Serial.println(x);
        Serial.println("TURN CW");
        analogWrite(pwm1,150);
        analogWrite(pwm2,150);
        analogWrite(pwm3,150);
        digitalWrite(p1,LOW);
        digitalWrite(n1,LOW);
        //digitalWrite(p2,LOW);
        //digitalWrite(n2,HIGH);
        }
        else if(w){
          digitalWrite(dir2,LOW);digitalWrite(dir1,LOW);digitalWrite(dir3,LOW);
        Serial.println(w);
        Serial.println("TURN CCW");
        analogWrite(pwm1,150);
        analogWrite(pwm2,150);
        analogWrite(pwm3,150);
        digitalWrite(p1,HIGH);
        digitalWrite(n1,HIGH);
        //analogWrite(p2,150);
        //digitalWrite(n2,LOW);
        }
        else{  //2
              if(z>=0 && z<100) {
                t0=255-z;
                digitalWrite(dir3,LOW);//digitalWrite(dir4,LOW);
              Serial.println(z);
              Serial.println("LEFT");
              analogWrite(pwm3,t0);
              digitalWrite(p1,LOW);
              digitalWrite(n1,LOW);
            //  digitalWrite(p2,LOW);
              //digitalWrite(n2,HIGH);
              //analogWrite(pwm4,t0);
              }
              else if(z>155 && z<=255) {
                digitalWrite(dir3,HIGH);//digitalWrite(dir4,HIGH);
              Serial.println(z);
              Serial.println("RIGHT");
              analogWrite(pwm3,z);
              digitalWrite(p1,HIGH);
              digitalWrite(n1,HIGH);
             // analogWrite(p2,z);
              //digitalWrite(n2,LOW);
              //analogWrite(pwm4,z);
              }
              else {
              analogWrite(pwm3,0);
              digitalWrite(p1,LOW);
              digitalWrite(n1,LOW);
              //digitalWrite(p2,LOW);
              //digitalWrite(n2,LOW);
              //analogWrite(pwm4,0);
              }
      
              if(y>=0 && y<100) {
                t0=255-y;
                digitalWrite(dir2,HIGH);digitalWrite(dir1,LOW);
              Serial.println(y);
              Serial.println("FORWARD");
              analogWrite(pwm1,t0);
              analogWrite(pwm2,t0);
              }
              else if(y>155 && y<=255) {
                digitalWrite(dir2,LOW);digitalWrite(dir1,HIGH);
              Serial.println(y);
              Serial.println("BACKWARD");
              analogWrite(pwm1,y);
              analogWrite(pwm2,y);
              }
              else {
              analogWrite(pwm1,0);
              analogWrite(pwm2,0); 
              }              
        }  //2
      }  //3
}  //4
    


delay(50);
     
}
