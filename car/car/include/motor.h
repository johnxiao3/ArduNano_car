#include <avr/io.h>
#define F_CPU 16000000UL     //8MHz CPU frequency
#include <util/delay.h>     //To use _delay_ms()

/*
-----------------------------
PIN connection:
	A1 -> D2
	A2 -> D3
	B1 -> D4
	B2 -> D5
-----------------------------
*/

// if i = 1 forward, i=2 backward, i=0 stop,
void motor_move(unsigned char i){
	DDRD = 0xff;     //set portd as output
	if (i == 1){
		PORTD |= _BV(2);
		PORTD &= ~_BV(3);
		PORTD &= ~_BV(4);
		PORTD |= _BV(5);
	}
	else if(i == 2){
		PORTD &= ~_BV(2);
		PORTD |= _BV(3);
		PORTD |= _BV(4);
		PORTD &= ~_BV(5);
	}
	else if(i == 0){
		PORTD &= ~_BV(2);
		PORTD &= ~_BV(3);
		PORTD &= ~_BV(4);
		PORTD &= ~_BV(5);
	}
}

