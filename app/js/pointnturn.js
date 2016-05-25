// -----------------------------
// PNT Parent object
// -----------------------------
function PNT(address, senderID, destinationID, log) {
	this.address = address;
	this.senderID = senderID;
	this.destinationID = destinationID;
	this.led = false;
	this.logElement = document.getElementById(log);

	this.send = function(msg) {
		this.log('sent: '+ msg);
		this.ws.send(msg);
	}

	this.log = function(msg) {
		if (this.logElement != null) {
			this.logElement.innerHTML = msg + "\n" + this.logElement.innerHTML;
		}
	}

	// create WebSocket
	this.ws = new WebSocket(address);

	// add event handler for incomming message
	this.ws.onmessage = (function(evt){
		var my_received_message = evt.data;
		this.log('received: ' + my_received_message);
	}).bind(this);

	// add event handler for diconnection 
	this.ws.onclose = (function(evt){
		this.log('log: Diconnected');
	}).bind(this);

	// add event handler for error 
	this.ws.onerror = (function(evt){
		this.log('log: Error');
	}).bind(this);

	// add event handler for new connection 
	this.ws.onopen = (function(evt) {
		this.log('log: Connected');
		this.send('{"setID":"' +this.senderID+ '","passwd":"none"}');
	}).bind(this);

	// Get value of last delay in miliseconds
	this.getDelay = function() {
		return false;
	}

	// Returns true if the handshake was successful and delay is not going over given threshold
	this.connected = function() {
		return true;
	}


	// -------------------------------
	// DEPRECATED FUNCTIONS
	// -------------------------------
	// sends a message to switch LED on and off
	this.switchLED = function() {
		var newValue;
		var ledSwitch = document.getElementById('ledSwitch');
		if (this.led) { // turn off!
			newValue = 0;
			ledSwitch.innerHTML = 'LED ON';
			ledSwitch.classList.remove('btn-danger');
			ledSwitch.classList.add('btn-success');
		} else {
			newValue = 1;
			ledSwitch.innerHTML = 'LED OFF';
			ledSwitch.classList.remove('btn-success');
			ledSwitch.classList.add('btn-danger');
		}
		this.send('{"to":"' +this.destinationID+ '","led":"' +newValue+ '"}');
		this.led = newValue;
	}
}

// DEFINING Laser functions
// -------------------------
function PNTLaser(address, senderID, destinationID, log) {
	PNT.call(this, address, senderID, destinationID, log);
	this.x = 1500;
	this.y = 1500;
	this.limitXTop = 1750;
	this.limitXBot = 1250;
	this.limitYTop = 1750;
	this.limitYBot = 1250;
}
// setting up inheritance
PNTLaser.prototype = Object.create(PNT.prototype);
PNTLaser.prototype.constructor = PNT;

PNTLaser.prototype.move = function(x, y) {
	this.x += x;
	this.y += y;
	
	if (this.x > this.limitXTop) this.x = this.limitXTop;
	if (this.x < this.limitXBot) this.x = this.limitXBot;

	if (this.y > this.limitYTop) this.y = this.limitYTop;
	if (this.y < this.limitYBot) this.y = this.limitYBot;

	this.sendMove();
}
// centers the 
PNTLaser.prototype.center = function() {
	this.x = Math.floor((this.limitXTop - this.limitXBot) / 2);
	this.y = Math.floor((this.limitYTop - this.limitYBot) / 2);
	this.sendMove();
}
// generates random X and Y degrees inside limit boundaries and sends it to ESP
PNTLaser.prototype.moveRandom = function() {
	this.x = Math.floor(Math.random() * this.limitXTop);
	this.y = Math.floor(Math.random() * this.limitYTop);
	this.sendMove();
}
// move to absolute position
PNTLaser.prototype.sendMove = function() {
	this.send('{"to":"' +this.destinationID+ '","servox":"' +this.x+ '","servoy":"' +this.y+ '"}');
}

// if we are at the limit on X axis, return true
PNTLaser.prototype.limitX = function() {
	if (this.x >= this.limitXTop) return '+';
	else if (this.x <= this.limitXBot) return '-';
	return false;
}
// if we are at the limit on Y axis, return true
PNTLaser.prototype.limitY = function() {
	if (this.y >= this.limitYTop) return '+';
	else if (this.y <= this.limitYBot) return '-';
	return false;
}
// turns the laser on
PNTLaser.prototype.laserOn = function() {
	this.send('{"to":"' +this.destinationID+ '","laser":"1"}');
}
// turns the laser off
PNTLaser.prototype.laserOff = function() {
	this.send('{"to":"' +this.destinationID+ '","laser":"0"}');
}





// DEFINING Platform functions
// -------------------------
function PNTPlatform(address, senderID, destinationID, log) {
	PNT.call(this, address, senderID, destinationID, log);
}
// setting up inheritance
PNTPlatform.prototype = Object.create(PNT.prototype);
PNTPlatform.prototype.constructor = PNT;

PNTPlatform.prototype.rotate = function(step) {
	this.send('{"to":"' +this.destinationID+ '","step":"' +step+ '"}');
}



