#include <CheapStepper.h>
#include <IRremote.hpp>

CheapStepper stepper (8, 9, 10, 11);

int V_PIN = 3;

void setup() {
	stepper.setRpm(12);
	IrReceiver.begin(2, true);
	pinMode(V_PIN, OUTPUT);
}

void loop() {
	if (IrReceiver.decode()) {
		unsigned char command = IrReceiver.decodedIRData.command;
		char n = 0;
		switch (command) {
			case 0xC:
				n = 1;
				break;
			case 0x18:
				n = 2;
				break;
			case 0x5E:
				n = 3;
				break;
			case 0x8:
				n = 4;
				break;
			case 0x1C:
				n = 5;
				break;
			case 0x5A:
				n = 6;
				break;
			case 0x42:
				n = 7;
				break;
			case 0x52:
				n = 8;
		}
		int time;
		while (n) {
			if (n & 1)
				time = 200;
			else
				time = 100;
			n >>= 1;
			analogWrite(V_PIN, 255);
			delay(time);
			analogWrite(V_PIN, 0);
			delay(500);
		}
		IrReceiver.resume();
	}
}
