#include <avr/interrupt.h>

#define twobyte uint16_t
#define TMR 500

ISR(TIMER0_COMPA_vect){
	static twobyte counter = 0;
	
	if(counter < TMR)
		counter++;
	else{
		counter = 0;
		PINB = 0x20;
	}
}

int main(void){
	DDRB = 0xFF;
	sei();
	TCCR0A = 0x02;
	TCCR0B = 0x03;
	OCR0A = 0xF9;
	TIMSK0 = 0x02;
	while(1){
		
	}
}