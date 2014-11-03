#include "main.h"

void setup() {
	initServer();
	initLedBut();
	initAcel();
}

void loop() {
	char *cmd;
	if ((cmd = getCmd()) != 0) {
		switch(cmd[0]) {
			case 'v':
				sendMsg(VERSION_STR);
				break;
			case 'l':
				cmdLed(cmd);
				break;
			case 'b':
				cmdBut();
				break;
			case 'a':
				getI2Caddresses();
				break;
			case 'r':
				takeReading();
				break;
		}
	}
	procBut();
}
