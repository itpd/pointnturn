# Point'N'Turn

## Javascript Interfce

To initialize the Laser create a new PNTLaser object with 3 arguments:

1. Address of websocket server, 'ws://achex.ca:4010' is very recommended
2. ID of the controller. In future userful for security
3. ID of the Point'N'Turn Laser device. (Right now hard-coded on line 14 in websocket.ino file)
4. Optional ID of a log element

## Initialize laser

	var laser = new PNTLaser('ws://achex.ca:4010', 'PNTC', 'PNTL');

	// moves the servos of laser pointer by X and Y degrees
	// for example move(-3, 0) or move(3, -3)
	laser.move(int x, int y);

	// centers the laser
	laser.center()

	// moves the serovs of laser pointer to a random direction
	laser.moveRandom()

	// Turns laser ON
	laser.laserOn()

	// Turns laser OFF
	laser.laserOff()

	// Returns:
	// false - no limit is hit
	// '+' - limit hit on top
	// '-' - limit hit on bottom
	laser.limitX()

	// Returns:
	// false - no limit is hit
	// '+' - limit hit on top
	// '-' - limit hit on bottom
	laser.limitX()

	// Returns:
	// true - connection is alright
	// false - connection is lost or timed out (1000 ms)
	laser.connected();

	// returns last delay in ms
	laser.getDelay();

	// both Laser and Platform have switchLED() method which switches embedded LED on and off
	platform.switchLED();

## Initialize platform


	var platform = new PNTPlatform('ws://achex.ca:4010', 'PNTC', 'PNTP');


	// moves the platform by Step of size (1-5) which takes 300ms
	// and in Direction 'L' for left and 'R' for right
	platform.rotate(Step, Direction);

	// both Laser and Platform have switchLED() method which switches embedded LED on and off
	platform.switchLED();

	// Returns:
	// true - connection is alright
	// false - connection is lost or timed out (1000 ms)
	platform.connected();

	// returns delay in milliseconds
	platform.getDelay()

	
## ToDo

1. Make the DEVICEID in the code as a variable
2. Interface for connecting to different wifis than 'SDU-GUEST' for ESP
3. Interface for the contoller

## Board setup with Arduino
https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide

- Flash Mode "QIO"
- Flash Frequency "40MHz"
- Upload Using "Serial"
- CPU Frequency "80 MHz"
- Flash Size "4M"
- Reset Method "nodemcu"
