
void handleCMD(JsonObject& cmd) {

	if (cmd.containsKey("led")) {
		if (cmd["led"] == 0) {
			digitalWrite(outputLEDPin, HIGH); // somehow the built in LED is ON when LOW
			Serial.println("LED OFF");
		} else {
			digitalWrite(outputLEDPin, LOW); // somehow the built in LED is ON when LOW
			Serial.println("LED ON");
		}
	}

	// if (cmd.containsKey("servoX")) {
	// 	servoX.write(cmd["servoX"]);
	// 	Serial.print("servoX: ");
	// 	// Serial.println(cmd["servoX"]);
	// }


	// if (cmd.containsKey("servoY")) {
	// 	servoX.write(cmd["servoX"]);
	// 	Serial.print("servoX: ");
	// 	Serial.println(cmd["servoX"]);
	// }

}