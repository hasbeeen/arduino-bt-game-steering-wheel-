/*

ADDR =19:8:35C861

*/
//#include <XInput.h>
#include <Joystick.h>
#include <SoftwareSerial.h>
//#include <Keyboard.h>

SoftwareSerial RC(9, 8);// bluetooth TX,RX


String printed;


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  14, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, true,          // No rudder or throttle
  true, true, true);  // No accelerator, brake, or steering


int joy_min = 0;
int joy_max = 1023;



void setup() {
  Serial.begin(9600);
  RC.begin(38400);
  //Keyboard.begin();
  Joystick.begin();
/*
  // Initialize Button Pins
  pinMode(4, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
*/
  // Initialize Joystick Library
  
  

  //Joystick.setXAxisRange(joy_min, joy_max);
  //Joystick.setRudderRange(joy_min, joy_max);
  Joystick.setThrottleRange(joy_min, joy_max);
  Joystick.setAcceleratorRange(joy_min, joy_max);
  Joystick.setBrakeRange(joy_min, joy_max);
  Joystick.setSteeringRange(joy_min, joy_max);

  //Keyboard.println("Hello!");

	//XInput.setReceiveCallback(rumbleCallback);

	//XInput.begin();


}

// Last state of the buttons
int lastButtonState[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};


void loop() {
  //BT
    if(RC.available() > 0) {
    printed = RC.readStringUntil('.');//recieve value from bluetooth      
                
  }
  //Serial.print(printed);
  //Serial.println(printed.substring(35,39));
   //           /                         BUTON VERİSİ                                   /
//BT GELEN VERİ 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 
// gelen veri = 1 , 1 , 1 , 1 , 1 , 1  ,  1  ,  1  ,  1  ,  1  ,  1  ,  1  ,  1  ,  1  ,  1  5  2  8  ,  1  9  2  6



Joystick.setButton(0, (printed.substring(0,3)).toInt());
Joystick.setButton(1, (printed.substring(4,5)).toInt());
Joystick.setButton(2, (printed.substring(6,7)).toInt());
Joystick.setButton(3, (printed.substring(8,9)).toInt());
Joystick.setButton(4, (printed.substring(10,11)).toInt());
Joystick.setButton(5, (printed.substring(12,13)).toInt());
Joystick.setButton(6, (printed.substring(14,15)).toInt());
Joystick.setButton(7, (printed.substring(16,17)).toInt());
Joystick.setButton(8, (printed.substring(18,19)).toInt());
Joystick.setButton(9, (printed.substring(20,21)).toInt());
Joystick.setButton(10, (printed.substring(22,23)).toInt());
Joystick.setButton(11, (printed.substring(24,25)).toInt());
Joystick.setButton(12, (printed.substring(26,27)).toInt());
Joystick.setButton(13, (printed.substring(28,29)).toInt());

/////direxyon
int roll = map((printed.substring(30,34)).toInt(),1000,2023,0,1023);
//Serial.println(roll);
Joystick.setSteering(roll);
/*
int pic = map(printed[35,39]+0,1000,2023,0,1023);
Joystick.setXAxis(pic);
*/



Joystick.setAccelerator(map(analogRead(A1),0,900,1023,0));

Joystick.setBrake(map(analogRead(A3),100,900,0,1023));

//Joystick.setRudder(map(analogRead(A1),0,900,1023,0));
Joystick.setThrottle(map(analogRead(A2),200,1000,0,1023));
 
//Keyboard.println(printed);
//printed = ""; 




}
/*

 void rumbleCallback(uint8_t packetType) {
	// If we have an LED packet (0x01), do nothing
	if (packetType == (uint8_t) XInputReceiveType::LEDs) {
		return;
	}

	// If we have a rumble packet (0x00), see our rumble data on the LED
	else if (packetType == (uint8_t) XInputReceiveType::Rumble) {
		uint8_t rumbleleft = XInput.getRumbleLeft() ;
    uint8_t rumbleright = XInput.getRumbleRight();
		Serial.print(rumbleleft,rumbleright);
	}
  
  
  }*/