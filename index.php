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
	<script type="text/javascript" src="https://code.jquery.com/jquery-2.2.1.min.js"></script>

<script type="text/javascript" src="script.js"></script>
<script>
var connection = new WebSocket('ws://10.11.2.1:81/', ['arduino']);

connection.onopen = function () {
	connection.send('Message from Browser to ESP8266 yay its Working!! ' + new Date()); 
	connection.send('ping');
	
/*	setInterval(function() {
		connection.send('Time: ' + new Date()); 
	}, 20);
*/
connection.send('Time: ' + new Date()); 
};

connection.onerror = function (error) {
	console.log('WebSocket Error ', error);
};

connection.onmessage = function (e) {
	console.log('Server: ', e.data);
	connection.send('Time: ' + new Date()); 
};

function sendRGB() {
	console.log('RGB: ' + rgb);
	connection.send(rgb); 
}

</script>


</head>

<body>

<div class="container text-center">
	<a class="btn btn-lg btn-success ajax-link" href="server.php?led=on">
		TURN ON
	</a>

	<a class="btn btn-lg btn-danger ajax-link" href="server.php?led=off">
		TURN OFF
	</a>

	<a href="control.json" class="pull-right" target="_blank">
		Control file
	</a>
</div>

<pre class="log">
</pre>

<script type="text/javascript">
// $(document).on('click', '.ajax-link', function(e) {
// 	var link = $(this);
// 	$.ajax({
// 		url: link.attr('href'),
// 		success: function(data) {
// 			$('.log').prepend(data);
// 		}
// 	});
// 	e.preventDefault();
// 	return false;
// })


</script>

</body></html>
