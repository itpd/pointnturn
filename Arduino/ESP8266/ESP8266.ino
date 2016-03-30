#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include <WebSocketsClient.h>

#include <Hash.h>

const char* ssid     = "SDU-GUEST";
const char* password = "";

const char* host     = "itpdiot.ondrejhenek.cz";
String path          = "/control.json";
const int outputLEDPin = 0;

WebSocketsClient webSocket;

// declaring a function to get JSON. Don't know why it's needed, but it's needed :X
// JsonObject& getJson(String response);

void setup() {  
	pinMode(outputLEDPin, OUTPUT);
	Serial.begin(115200);

	delay(10);
	wifiConnect();

	webSocket.begin("echo.websocket.org", 80);
	//webSocket.setAuthorization("user", "Password"); // HTTP Basic Authorization
	webSocket.onEvent(handleWebSocketEvent);
}

void loop() {
	// Serial.print(".");
	// delay(500);

	webSocket.loop();
	if (Serial.available()) {
		String msg = Serial.readString();
		
		Serial.println();
		Serial.print("Sending: ");
		Serial.println(msg);

		webSocket.sendTXT(msg);
	}

}
