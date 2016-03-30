
void handleCMD(JsonObject& cmd) {

	if (cmd["led"] == 1) {
		digitalWrite(outputLEDPin, LOW); // somehow the built in LED is ON when LOW
		Serial.println("LED ON");
	} else {
		digitalWrite(outputLEDPin, HIGH); // somehow the built in LED is ON when LOW
		Serial.println("LED OFF");
	}

	// if (cmd["motor"] == 'r') {
	// speed, direction, ?

}