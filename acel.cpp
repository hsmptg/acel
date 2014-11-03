#include "main.h"
#include "Wire.h"

const int ADXL345 = 0x53; // I2C address for ADXL345

void initAcel() {
	Wire.begin(); // set up Arduino I2C support
    Wire.beginTransmission(ADXL345);
    Wire.write(0x2D);
    Wire.write(0x08); // Set "Measure bit" (D3) of "POWER_CTL" register (page 25 of datasheet)
    Wire.endTransmission();
}

void getI2Caddresses() {
	uint8_t addr;
	uint8_t v;

	for (addr=0; addr<0x80; addr++) {
		Wire.beginTransmission(addr);
		v = Wire.endTransmission();
		if (v != 0)
			Serial.print("-- ");
		else {
			Serial.print(addr, HEX);
			Serial.print(" ");
		}
		if ((addr % 16) == 15)
			Serial.print("\r");
	}
}

void takeReading() {
	int x, y, z;
	uint8_t dat[10];

	Wire.beginTransmission(ADXL345);
    Wire.write(0x32);
    Wire.endTransmission();
    Wire.requestFrom (ADXL345, 6);
    Wire.readBytes(dat, 6);
    x = ((uint16_t)dat[1] << 8) + dat[0];
	y = ((uint16_t)dat[3] << 8) + dat[2];
	z = ((uint16_t)dat[5] << 8) + dat[4];

	Serial.print(x);
	Serial.print(" ");
	Serial.print(y);
	Serial.print(" ");
	Serial.print(z);
	Serial.print("\r"); // O println envia "\r\n" no fim!
}
