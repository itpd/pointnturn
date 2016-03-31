#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include <Servo.h> 

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

}
