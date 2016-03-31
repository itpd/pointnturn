// static because some random Fatal Error
static void handleCMD(JsonObject& cmd) {

	if (cmd.containsKey("led")) {
		if (cmd["led"] == 0) {
			digitalWrite(outputLEDPin, HIGH); // somehow the built in LED is ON when LOW
			Serial.println("LED OFF");
		} else {
			digitalWrite(outputLEDPin, LOW); // somehow the built in LED is ON when LOW
			Serial.println("LED ON");
		}
	}

	if (cmd.containsKey("servox")) {
		servoX.write((int) cmd["servox"]);
		Serial.print("servox: ");
		Serial.println((int) cmd["servox"]);
	}

	if (cmd.containsKey("servoy")) {
		servoX.write((int) cmd["servoy"]);
		Serial.print("servoy: ");
		Serial.println((int) cmd["servoy"]);
	}


}