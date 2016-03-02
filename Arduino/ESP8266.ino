#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid     = "AndroidAP";  
const char* password = "linx6447";

const char* host     = "itpdiot.ondrejhenek.cz"; // Your domain  
String url          = "/control/index.json";
const int pin        = 2;

void setup() {  
	pinMode(pin, OUTPUT); 
	pinMode(pin, LOW);
	Serial.begin(115200);

	delay(10);
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);
	int wifi_ctr = 0;
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("WiFi connected");  
	Serial.println("IP address: " + WiFi.localIP());
}

void loop() {  
	Serial.print("connecting to ");
	Serial.println(host);

	WiFiClient client;
	const int httpPort = 80;
	if (!client.connect(host, httpPort)) {
		Serial.println("connection failed");
		return;
	}


	Serial.print("Requesting URL: ");
	Serial.println(url);

	// This will send the request to the server
	client.print(String("GET ") + url + " HTTP/1.1\r\n" +
	           "Host: " + host + "\r\n" + 
	           "Connection: close\r\n\r\n");

	delay(500); // wait for server to respond

	// read response
	String section="header";
	while(client.available()){
		String line = client.readStringUntil('\r');


		// we’ll parse the HTML body here
		if (section=="header") { // headers..
			Serial.print(".");
			if (line=="\n") { // skips the empty space at the beginning 
				section="json";
			}
		}
		else if (section=="json") {  // print the good stuff
			section="ignore";
			String result = line.substring(4);
Serial.println("PH: " + result);
			// Parse JSON
			int size = result.length() + 1;
			char json[size];
			result.toCharArray(json, size);
			StaticJsonBuffer<200> jsonBuffer;
			JsonObject& json_parsed = jsonBuffer.parseObject(json);
			if (!json_parsed.success())
			{
				Serial.println("parseObject() failed");
				return;
			}

			// Make the decision to turn off or on the LED
			if (strcmp(json_parsed["led"], "1") == 0) {
				digitalWrite(pin, HIGH); 
				Serial.println("LED ON");
			}
			else {
				digitalWrite(pin, LOW);
				Serial.println("led off");
			}
		}
	}
	Serial.print("closing connection. ");
}