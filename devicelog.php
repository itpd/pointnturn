<?php if (isset($_GET['id'])) {
	$id = $_GET['id'];
} else {
	exit ('You have to specify ID of device. Access this page with ?id=XXX parameter');
} ?>
<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	<meta charset="utf-8">
	
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0">

	<title>ITPD IOT</title>
	<meta property="og:title" content="ITPD IOT">

	<meta name="author" content="Ondřej Henek">
	<meta name="description" content="IT Product Design @SDU.dk - Internet of Things project">
	<meta property="og:description" content="IT Product Design @SDU.dk - Internet of Things project">

	<meta property="og:type" content="website">
	<meta property="og:locale" content="en_US">

	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" integrity="sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7" crossorigin="anonymous">

<!-- 
	<script type="text/javascript" src="https://code.jquery.com/jquery-2.2.1.min.js"></script>
 -->
</head>

<body>


<div class="container">
<br>

	<a href="index.html" class="pull-right">
		The app
	</a>

<br>

	<pre id="log"></pre>

</div>


<script type="text/javascript">

var logdiv = document.getElementById('log');
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
	ws.sendMsg('{"setID":"<?php echo $id ?>","passwd":"none"}');
};

</script>
</body>
</html>

