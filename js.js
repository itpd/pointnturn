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
		this.logElement.innerHTML = msg + "\n" + this.logElement.innerHTML;
	}

	// create WebSocket
	this.ws = new WebSocket(address);

	// add event handler for incomming message
	this.ws.onmessage = function(evt){
		var my_received_message = evt.data;
		this.log('received: ' + my_received_message);
	};

	// add event handler for diconnection 
	this.ws.onclose= function(evt){
		this.log('log: Diconnected');
	};

	// add event handler for error 
	this.ws.onerror= function(evt){
		this.log('log: Error');
	};

	// add event handler for new connection 
	this.ws.onopen = (function(evt) {
		this.log('log: Connected');
		this.send('{"setID":"' +this.senderID+ '","passwd":"none"}');
	}).bind(this);


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

	// make a simple send function
	this.sendFromInput = function() {
		var input = document.getElementById('userinput');
		this.send(input.value);
	}
}

// DEFINING Laser functions
// -------------------------
function PNTLaser(address, senderID, destinationID) {
	PNT.call(this, address, senderID, destinationID);
}
// setting up inheritance
PNTLaser.prototype = Object.create(PNT.prototype);
PNTLaser.prototype.constructor = PNT;

PNTLaser.prototype.move = function(x, y) {
	this.send('{"to":"' +this.destinationID+ '","servox":"' +x+ '","servoy":"' +y+ '"}');
}
// generates random X and Y degrees 0 - 180 and sends it to ESP
PNTLaser.prototype.moveRandom = function() {
	var x = Math.floor(Math.random() * 180);
	var y = Math.floor(Math.random() * 180);
	this.move(x, y);
}



// DEFINING Platform functions
// -------------------------
function PNTPlatform(address, senderID, destinationID) {
	PNT.call(this, address, senderID, destinationID);
}
// setting up inheritance
PNTPlatform.prototype = Object.create(PNT.prototype);
PNTPlatform.prototype.constructor = PNT;

PNTPlatform.prototype.rotate = function(step, direction) {
	if (direction != 'L' && direction != 'R') {
		alert('Set the direction of rotation as "L" for left or "R" for right');
	}
	this.send('{"to":"' +this.destinationID+ '","step":"' +step+ '","dir":"' +direction+ '"}');
}



