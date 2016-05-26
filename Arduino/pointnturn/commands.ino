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
    int upsideDown = 3000-int( cmd["servox"]);
    servoX.writeMicroseconds(upsideDown);
    timeLastPoint = millis();
      if (digitalRead(laserpointerPin) == 0){
        digitalWrite(laserpointerPin, HIGH);//PH
        Serial.print("laserpointerON: ");
        Serial.print(digitalRead(laserpointerPin));
      }
	}

	if (cmd.containsKey("servoy")) {
    servoY.write(int( cmd["servoy"]));//PH
    timeLastPoint = millis();
      if (digitalRead(laserpointerPin) == 0){
        digitalWrite(laserpointerPin, HIGH);//PH
        Serial.print("laserpointerON: ");
        Serial.print(digitalRead(laserpointerPin));
      }   
	}

	if (cmd.containsKey("step")) {
		int move = (int) cmd["step"];
		move = move * platformMoveSpeed;

		Serial.print("Platform speed: ");
		Serial.println(move);

		stepper.move(move);
	}


}
