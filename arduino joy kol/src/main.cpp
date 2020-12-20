#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

#include <SoftwareSerial.h>


MPU6050 mpu;


SoftwareSerial RC(A3, A2);// bluetooth TX,RX
 int s1 = 7;
 int s2 = 8;
 int s3 = 6;

 int c1 = 2;
 int c2 = 3;
 int c3 = 4;
 int c4 = 5;

int ar1 = 11;
int ar2 = 12;

int a1;
int a2;
int a3;


int b1;
int b2;
int b3;


int d1;
int d2;
int d3;

int e1;
int e2;
int e3;


int ark1;
int ark2;

void setup() {
    RC.begin(38400);
    Serial.begin(9600);
   while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }
 


 pinMode(s1, INPUT);
 pinMode(s2, INPUT);
 pinMode(s3, INPUT);
 
 pinMode(c1, OUTPUT);
 pinMode(c2, OUTPUT);
 pinMode(c3, OUTPUT);
 pinMode(c4, OUTPUT);

 pinMode(ar1, INPUT_PULLUP);
 pinMode(ar2, INPUT_PULLUP);
 
 }
 /*
       c1 c2 c3 c4
        \  \  \  \
   s1 - a1 b2 d3 e4 
   s2 - a1 b2 d3 e4
   s3 - a1 b2 d3 e4
   

*/


void loop() {
  //jayro
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch & Roll
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

  
////////////////////////////button girdileri/////////////////
   ///////a ///////////
    digitalWrite(c1,1);
    a1=digitalRead(s1);
    a2=digitalRead(s2);
    a3=digitalRead(s3);
    digitalWrite(c1,0);

   /////////b/////////
   digitalWrite(c2,1);
    b1=digitalRead(s1);
    b2=digitalRead(s2);
    b3=digitalRead(s3);
    digitalWrite(c2,0);

    /////////d//////////
  
    digitalWrite(c3,1);  
    d1=digitalRead(s1);
    d2=digitalRead(s2);
    d3=digitalRead(s3);
    digitalWrite(c3,0);
    
    digitalWrite(c4,1);  
    e1=digitalRead(s1);
    e2=digitalRead(s2);
    e3=digitalRead(s3);
    digitalWrite(c4,0);

  //////////ark///////////
  ark1=!digitalRead(ar1);
  ark2=!digitalRead(ar2);
  
  ////////////////////////////////////////////////////////////
  //Serial.print(pitch+"       "+roll );
  //RC.write(roll);
  int rol= map(roll,-90,90,1000,2023);
  int pitc= map(pitch,-90,90,1000,2023);

  String veri =(String(a1)+','+String(a2)+','+String(a3)+','+
                String(b1)+','+String(b2)+','+String(b3)+','+
                String(d1)+','+String(d2)+','+String(d3)+','+
                String(e1)+','+String(e2)+','+String(e3)+','+
                String(ark1)+','+String(ark2)+','+String(rol)+','+String(pitc)+'.');
  Serial.println(veri);    
  RC.println(veri);
  //delay(200);
 



}