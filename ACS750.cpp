#include "ACS750.h"
int zero; 
ACS750::ACS750(ACS750_type type, uint8_t _pin) {
	switch (type) {
		case ACS750LCA_050:
			sensitivity = 0.0400;
		default:
			sensitivity = 0.0400;
			break;
	}
	pin = _pin;
}

int ACS750::calibrate() {
	int _zero = 0;
	for (int i = 0; i < 10; i++) {
		_zero += analogRead(pin);
		delay(10);
	}
	_zero /= 10;
	zero = _zero;
	return _zero;
}

void ACS750::setZeroPoint(int _zero) {
	zero = _zero;
}

void ACS750::setSensitivity(float sens) {
	sensitivity = sens;
}

float ACS750::getCurrentDC() {
	float I = (zero - analogRead(pin)) / ADC_SCALE * VREF / sensitivity;
	return I;
}

float ACS750::getCurrentAC() {
	return getCurrentAC(DEFAULT_FREQUENCY);
}

float ACS750::getCurrentAC(uint16_t frequency) {
	uint32_t period = 1000000 / frequency;
	uint32_t t_start = micros();

	uint32_t Isum = 0, measurements_count = 0;
	int32_t Inow;

	while (micros() - t_start < period) {
		Inow = zero - analogRead(pin);
		Isum += Inow*Inow;
		measurements_count++;
	}

	float Irms = sqrt(Isum / measurements_count) / ADC_SCALE * VREF / sensitivity;
	return Irms;
}
