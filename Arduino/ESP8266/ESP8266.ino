#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include <Servo.h>
#include <AccelStepper.h>

#define DEVICEID "PNTP"

// WiFi settings
const char* ssid     = "SDU-GUEST";
const char* password = "";

// Pins
const int outputLEDPin = 0;
const int servoXPin = 12;
const int servoYPin = 13;

// Others
WebSocketsClient webSocket;
Servo servoX, servoY;

// Motor stuff
AccelStepper stepper(AccelStepper::FULL4WIRE, 14, 13, 12, 15);
int platformMoveSpeed = 100;

void setup() {  
	pinMode(outputLEDPin, OUTPUT);
	servoX.attach(servoXPin);
	servoY.attach(servoYPin);
	Serial.begin(115200);

	delay(10);
	wifiConnect();

	webSocket.begin("achex.ca", 4010); // port 80?
	//webSocket.setAuthorization("user", "Password"); // HTTP Basic Authorization
	webSocket.onEvent(handleWebSocketEvent);

	stepper.setMaxSpeed(300);
	stepper.setAcceleration(100);
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

}
