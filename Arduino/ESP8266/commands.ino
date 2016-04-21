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
		servoY.write((int) cmd["servoy"]);
		Serial.print("servoy: ");
		Serial.println((int) cmd["servoy"]);
	}

	if (cmd.containsKey("step")) {
		if (cmd.containsKey("dir")) {

			Serial.print("step: ");
			Serial.println((int) cmd["step"]);
			Serial.print("direction: ");

			if (cmd["dir"] == 'L') {
				// moving left
				Serial.println('left');
			} else {
				// moving right
				Serial.println('right');
			}
	}


}