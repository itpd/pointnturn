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

JsonObject& getJson(String response) {
	// Serial.println(response);

	// parsing the JSON
	int size = response.length() + 1;
	char json[size];
	response.toCharArray(json, size);
	StaticJsonBuffer<1023> jsonBuffer; // Exception (28) if too small!
	return jsonBuffer.parseObject(response);
}
