#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>

const uint8_t LOW PROGMEM = 0;
const uint8_t HIGH PROGMEM = 1;

const uint8_t INPUT PROGMEM = 0;
const uint8_t OUTPUT PROGMEM = 1;

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef SET_PIN
#define SET_PIN(port, bit) {&port, _BV(bit)}
#endif


struct PORT{
	uint8_t * const status;
	uint8_t * const input;
	uint8_t * const output;
};

#define X(val) const struct PORT val PROGMEM = {&PORT##val, &PIN##val, &DDR##val};
	#include "ports.h"
#undef X

struct PIN{
	const struct PORT *port;
	const uint8_t mask;
};

void pinMode(const struct PIN p, uint8_t val){
	if (val){
		*(p.port->status) |= p.mask;
	}else{
		*(p.port->status) &= ~p.mask;
	}
}

void digitalWrite(const struct PIN p, uint8_t val){
	if (val){
		*(p.port->output) |= p.mask;
	}else{
		*(p.port->output) &= ~p.mask;
	}
}

uint8_t digitalRead(const struct PIN p){
	return *(p.port->input) & p.mask;
}