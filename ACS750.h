#ifndef ACS750_h
#define ACS750_h

#include <Arduino.h>

#define ADC_SCALE 1023.0
#define VREF 5.0
#define DEFAULT_FREQUENCY 50

enum ACS750_type {ACS750LCA_050};

class ACS750 {
public:
	ACS750(ACS750_type type, uint8_t _pin);
	int calibrate();
	void setZeroPoint(int _zero);
	void setSensitivity(float sens);
	float getCurrentDC();
	float getCurrentAC();
	float getCurrentAC(uint16_t frequency);

private:
	float zero = 512.0;
	float sensitivity;
	uint8_t pin;
};

#endif