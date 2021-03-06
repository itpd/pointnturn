#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include <Servo.h>
#include <AccelStepper.h> 


// ---------------------------------------------------
//                  Your Settings
// ---------------------------------------------------
// Device ID settings
#define DEVICEID "PNTL" // Device ID
#define DEVICEPASSWORD "none" // Device password

// WiFi settings
const char* ssid     = "SDU-GUEST"; // Wifi name (SSID)
const char* password = ""; // Wifi password (blank for no password)
// ---------------------------------------------------
// ---------------------------------------------------


// Pins
const int outputLEDPin = 0;
const int laserpointerPin = 2;//PH
const int servoXPin = 5;
const int servoYPin = 4;

// Others
WebSocketsClient webSocket;
Servo servoX, servoY;

// Motor stuff
AccelStepper stepper(AccelStepper::FULL4WIRE, 14, 13, 12, 15);
int platformMoveSpeed = 100;

//Time
int timeLastPoint = 0;
int timeSincePoint = 0;



void setup() {  
	pinMode(outputLEDPin, OUTPUT);
  pinMode(laserpointerPin, OUTPUT);//PH
 
	servoX.attach(servoXPin);
	servoY.attach(servoYPin);
  servoX.writeMicroseconds(1500);//PH
  servoY.writeMicroseconds(1500);//PH
 
	Serial.begin(115200);

	delay(10);
	wifiConnect();

	webSocket.begin("achex.ca", 4010); // port 80?
	webSocket.onEvent(handleWebSocketEvent);

	stepper.setMaxSpeed(300);
  stepper.setAcceleration(300);
  digitalWrite(laserpointerPin, HIGH);//PH
}

void loop() {
  
	webSocket.loop();
	if (Serial.available()) {
		String msg = Serial.readString();
		
		Serial.println();
		Serial.print("Sending: ");
		Serial.println(msg);

		webSocket.sendTXT(msg);
	}

	// if the motor has somewhere to go, this makes one step
	stepper.run();

  timeSincePoint = millis()-timeLastPoint;
  
  if (timeSincePoint >= 10000){
    Serial.print("turn off laser: ");
    Serial.print(digitalRead(laserpointerPin));
    Serial.print(" - ");
    Serial.println(timeSincePoint);
      if (digitalRead(laserpointerPin) == 1){
      digitalWrite(laserpointerPin, LOW);//PH
      Serial.print("laserpointerPin: ");
      Serial.print(digitalRead(laserpointerPin));
      }
    
    }

}
