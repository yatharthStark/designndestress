//adafruit wala code 
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_9DOF.h>
#include <Adafruit_L3GD20_U.h>
const int flexPin =A0;
int flex;
/* Assign a unique ID to the sensors */
Adafruit_9DOF                 dof   = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);

/**************************************************************************/
/*!
    @brief  Initialises all the sensors used by this example
*/
/**************************************************************************/
void initSensors()
{
  if(!accel.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}

/**************************************************************************/
/*!

*/
/**************************************************************************/





#include <SoftwareSerial.h>


const int rxpin = 0, txpin = 1;
SoftwareSerial bluetooth(rxpin, txpin);
const int x=A0;
const int y=A1;
int xh, yh ,xi ,xc , yi , yc;
int xcord, ycord;
const int trigger = 5;
int lstate = 0;
int rstate = 0;
const int lclick = 6;
const int rclick = 7;
const int led = 8;

void setup()
{
initSensors();




  
  pinMode(x,INPUT);
  pinMode(y,INPUT);
  pinMode(trigger,INPUT_PULLUP);
  pinMode(lclick,INPUT);
  pinMode(rclick,INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(lclick,HIGH);
  digitalWrite(rclick,HIGH);
  Serial.begin(9600);
  bluetooth.begin(9600);
sensors_event_t accel_event;
  sensors_event_t mag_event;
  sensors_vec_t   orientation;




  xh=orientation.roll;
  yh=orientation.pitch;
}

void loop()
{



  
digitalWrite(led,LOW);




//  while(digitalRead(trigger)==HIGH)
//  {
  sensors_event_t accel_event;
  sensors_event_t mag_event;
  sensors_vec_t   orientation;

  /* Read the accelerometer and magnetometer */
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);

  /* Use the new fusionGetOrientation function to merge accel/mag data */  
  if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation))
  {
    /* 'orientation' should have valid .roll and .pitch fields */
//    Serial.print(F("Orientation: "));
//    Serial.print(orientation.roll);
//    Serial.print(F(" "));
//    Serial.print(orientation.pitch);
//    Serial.print(F(" "));
//    Serial.print(orientation.heading);
//    Serial.println(F(""));
  }
  

  
    int flexValue;
flexValue= analogRead (flexPin);
//Serial.print("sensor:");
//
////flexValue=map(flexValue,700,1023,0,700);
//Serial.println(flexValue);


    digitalWrite(led, HIGH);
    lstate = digitalRead(lclick);
    rstate = digitalRead(rclick);
    
    xi=orientation.roll;
    xc=xi-xh;

    yi=orientation.pitch;
    yc=yi-yh;
    if (abs(xc)>8){
    xcord=map(xc,-80,80,0,1366);}
    if (abs(yc)>8){
    ycord=map(yc,-70,70,0,768);}
    if (xcord<0)
    {
      xcord=100;
    }
    if (xcord>1366)
    {
      xcord=100;
    }
    if (ycord<0)
    {
      ycord=100;
    }
    if (ycord>768)
    {
      ycord=100;
    }
    
    
    String xss,yss;
    xss=String(xcord);
    yss=String(ycord);
    if (xss.length()==1)
    {
      xss="000"+xss; 
    }
    if (xss.length()==2)
    {
      xss="00"+xss; 
    }
    if (xss.length()==3)
    {
      xss="0"+xss; 
    }
    if (yss.length()==1)
    {
      yss="00"+yss;
    }
    if (yss.length()==2)
    {
      yss="0"+yss;
    }
    
//    Serial.print("x");
//    Serial.print(xss);
//    Serial.print("y");
//    Serial.print(yss);
    String f="x"+xss+"y"+yss;
    String ff;

//    if (flexValue>140)
//    {lstate=HIGH;}

    
    if (flexValue>140)
    {
//    {Serial.print("l");
//      Serial.print(1);
  ff=f+"l1";
    }
    else 
    {ff=f+"l0";
}
    if (rstate == LOW){
//      Serial.print("r");
//    Serial.print(1);}
ff=ff+"r1";
    }
    else {
//      Serial.print("r");
//    Serial.print(0);}
ff=ff+"r0";
    }
//    bluetooth.print(xcord);
//    bluetooth.print(ycord);
//    if (lstate == LOW)
//    bluetooth.print(1);
//    else 
//    bluetooth.print(0);
//    if (rstate == LOW)
//    bluetooth.print(1);
//    else 
//    bluetooth.print(0);
    Serial.println(ff);
    delay(200);
   }
//}
