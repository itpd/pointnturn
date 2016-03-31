bool wifiConnect() {
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);
	int wifi_ctr = 0;
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("WiFi connected");  
	// Serial.println("IP address: " + WiFi.localIP());

	return true;
}


// String connect() {

// 	const char* host     = "itpdiot.ondrejhenek.cz";
// 	String path          = "/control.json";

	
// 	Serial.print("connecting to ");
// 	Serial.println(host);
// 	WiFiClient client;
// 	const int httpPort = 80;

// 	if (!client.connect(host, httpPort)) {
// 		Serial.println("connection failed");
// 		return "F";
// 	}

// 	client.print(String("GET ") + path + " HTTP/1.1\r\n" +
// 							 "Host: " + host + "\r\n" + 
// 							 "Connection: keep-alive\r\n\r\n");

// 	delay(500); // wait for server to respond

// 	// read response
// 	String section="header";
// 	while (client.available()) {
// 		String line = client.readStringUntil('\r');
// 		// Serial.print(line);
// 		// we’ll parse the HTML body here
// 		if (section=="header") { // headers..
// 			Serial.print(".");
// 			// Serial.print(line);
// 			if (line == "\n") { // skips the empty space at the beginning 
// 				section = "json";
// 			}
// 		} else if (section == "json") {  // print the good stuff
// 			section = "ignore";
// 			String result = line.substring(1);
// 			//String result = line.substring(4); //PH: Hack to remove sick letters.
// 			Serial.println("PH: " + result);
// 			// Parse JSON

// 			return result;
// 		}
// 	}
// 	Serial.print("closing connection. ");
// 	return "F";
// }


JsonObject& getJson(String response) {
	// Serial.println(response);

	// parsing the JSON
	int size = response.length() + 1;
	char json[size];
	response.toCharArray(json, size);
	StaticJsonBuffer<400> jsonBuffer; // Exception (28) if too small!
	return jsonBuffer.parseObject(response);
}