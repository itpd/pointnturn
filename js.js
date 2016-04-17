var logdiv = document.getElementById('log');
var led = false;
var ledSwitch = document.getElementById('ledSwitch');

function logf(str){
	logdiv.innerHTML = str + "\n" + logdiv.innerHTML;
}

// -----------------------------
// Websocket functionality
// -----------------------------

WebSocket.prototype.sendMsg = function(msg) {
	logf('sent: '+ msg);
	this.send(msg);
}

// create WebSocket
var ws = new WebSocket('ws://achex.ca:4010');

// add event handler for incomming message
ws.onmessage = function(evt){
	var my_received_message = evt.data;
	logf('received: ' + my_received_message);
};

// add event handler for diconnection 
ws.onclose= function(evt){
	logf('log: Diconnected');
};

// add event handler for error 
ws.onerror= function(evt){
	logf('log: Error');
};

// add event handler for new connection 
ws.onopen= function(evt){
	logf('log: Connected');
	ws.sendMsg('{"setID":"itpdiotserver","passwd":"none"}');
};

// -----------------------------
// TEMPORARY INTERFACE FUNCTIONS
// -----------------------------

// make a simple send function
function send(){
	var input = document.getElementById('userinput');
	ws.sendMsg(input.value);
}

// sends a message to switch LED on and off
function switchLED() {
	var newValue;
	if (led) { // turn off!
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
	ws.sendMsg('{"to":"itpdiot","led":"' +newValue+ '"}');
	led = newValue;
}

// generates random X and Y degrees 0 - 180 and sends it to ESP
function moveRandom() {
	var x = Math.floor(Math.random() * 180);
	var y = Math.floor(Math.random() * 180);
	move(x, y);
}

// sends coordinates for laser
function move(x, y) {
	ws.sendMsg('{"to":"itpdiot","servox":"' +x+ '","servoy":"' +y+ '"}');
}
