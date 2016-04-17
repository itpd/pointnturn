#define USE_SERIAL Serial

void handleWebSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {

	switch(type) {
		case WStype_DISCONNECTED:
			USE_SERIAL.printf("[WSc] Disconnected!\n");
			break;
		case WStype_CONNECTED:
			{
				USE_SERIAL.printf("[WSc] Connected to url: %s\n",  payload);
				
				// send message to server when Connected
				webSocket.sendTXT("{\"setID\":\"itpdiot\",\"passwd\":\"none\"}");
			}
			break;
		case WStype_TEXT:
			USE_SERIAL.printf("[WSc] received: %s\n", payload);

			{ // creating a new scope because otherwise variables like jsonResponse and cmd could be unitialized when falling through the switch case without break. Silly but needed. :)
				// parse JSON
				String jsonResponse = (const char*)payload;
				JsonObject& cmd = getJson(jsonResponse);
				if (!cmd.success()) {
					Serial.println("parseObject() failed");
				} else {
					handleCMD(cmd);
				}
			}
			break;
		case WStype_BIN:
			USE_SERIAL.printf("[WSc] get binary lenght: %u\n", lenght);
			hexdump(payload, lenght);

			// send data to server
			// webSocket.sendBIN(payload, lenght);
			break;
	}

}