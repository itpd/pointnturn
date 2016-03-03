<?php

function fileSetup($attr, $val) {
	$output = json_encode(array('LED' => $val));
	file_put_contents('control.json', $output);
}

if (isset($_GET['led'])) {
	if ($_GET['led'] == 'on') {
		$led = 1;
	} elseif ($_GET['led'] == 'off') {
		$led = 0;
	}
}

fileSetup('led', $led);

echo 'led: '.$led;
echo "\n";