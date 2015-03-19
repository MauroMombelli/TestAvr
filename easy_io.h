#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>

#define NULL 0

const uint8_t LOW PROGMEM = 0;
const uint8_t HIGH PROGMEM = 1;

const uint8_t INPUT PROGMEM = 0;
const uint8_t OUTPUT PROGMEM = 1;

volatile uint8_t *set_reg[] = {NULL, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF};
volatile uint8_t *out_reg[] = {NULL, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF};
volatile uint8_t *in_reg[] = {NULL, &PINB, &PINC, &PIND, &PINE, &PINF};

void pinMode(uint8_t pin, uint8_t status){
	uint8_t mask = 1 << (pin % 8);
	if (status == OUTPUT){
		*set_reg[pin/8] &= (uint8_t) (~mask);
	}else{
		*set_reg[pin/8] |= (uint8_t) (mask); 
	}
}

void digitalWrite(uint8_t pin, uint8_t status){
	uint8_t mask = 1 << (pin % 8);
	if (status == LOW){
		*out_reg[pin/8] &= (~mask);
	}else{
		*out_reg[pin/8] |= mask; 
	}
}

uint8_t digitalRead(uint8_t pin){
	uint8_t mask = 1 << (pin % 8);
	return *in_reg[pin/8] & mask?HIGH: LOW;
}