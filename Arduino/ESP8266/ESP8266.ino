#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid     = "SDU-GUEST";
const char* password = "";

const char* host     = "itpdiot.ondrejhenek.cz";
String path          = "/control.json";
const int outputLEDPin = 0;

// declaring a function to get JSON. Don't know why it's needed, but it's needed :X
JsonObject& getJson(String response);

void setup() {  
	pinMode(outputLEDPin, OUTPUT);
	Serial.begin(115200);

	delay(10);
	wifiConnect();
}

void loop() {  

	// Connect to server and get some response
	String jsonResponse = connect();
	if (jsonResponse == "F") {
		Serial.println("Connection failed");
		return;
	}

	// parse the response from JSON to array "cmd"
	JsonObject& cmd = getJson(jsonResponse);
	if (!cmd.success()) {
		Serial.println("parseObject() failed");
		return;
	}

	// whatever logic with JSON, now only LED
	if (cmd["LED"] == 1) {
		digitalWrite(outputLEDPin, LOW); // somehow the built in LED is ON when LOW
		Serial.println("LED ON");
	} else {
		digitalWrite(outputLEDPin, HIGH); // somehow the built in LED is ON when LOW
		Serial.println("LED OFF");
	}

}
