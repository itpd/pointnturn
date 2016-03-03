#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid     = "AndroidAP";
const char* password = "linx6447";

const char* host     = "itpdiot.ondrejhenek.cz";
String path          = "/control/index.json";
const int outputLEDPin = 0;

void setup() {  
	pinMode(outputLEDPin, OUTPUT);
	Serial.begin(115200);

	delay(10);
	wifiConnect();
}

void loop() {  

	String response = connect();
	if (response == "F") {
		Serial.println("Connection failed");
		return;
	}

	// parsing the JSON
	int size = response.length() + 1;
	char json[size];
	response.toCharArray(json, size);
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& json_parsed = jsonBuffer.parseObject(response);
	// JsonObject& json_parsed = getJson(response);


	if (!json_parsed.success()) {
		Serial.println("parseObject() failed");
		return;
	}
	
	if (json_parsed["LED"] == 1) {
		digitalWrite(outputLEDPin, LOW); // somehow the built in LED is ON when LOW
		Serial.println("LED ON");
	} else {
		digitalWrite(outputLEDPin, HIGH); // somehow the built in LED is ON when LOW
		Serial.println("LED OFF");
	}

}


JsonObject getJson(String) {
 // MAYBE IT WORKS WITHOUT POINTESRS I HATE POINTERS
}