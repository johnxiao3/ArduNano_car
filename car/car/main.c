#include <avr/io.h>
#define F_CPU 16000000UL     //8MHz CPU frequency
#include <util/delay.h>     //To use _delay_ms()

#include "include/motor.h"

/*
PIN Connection:
Servo Signal(yellow) -> PD6
*/
void pwm_TC0_init()     //to initialize PWM
{
    /*
	OC0A = PD6
	OC0B = PD5
	---------------------
	TCCR0A
	-------------------------------------------------------------
	| COM0A1 | COM0A0 | COM0B1 | COM0B0 | - | - | WGM01 | WGM00 |
	-------------------------------------------------------------
	FastPWM mode: COM0x1:0 =	0 normal,OC0x disconnected; 
								1 Toggle OC0x on compare match; 
								2 clear OC0x on compare match, set at bottom
								3 set OC0x on compare match, clear at bottom
	WGM02:0: WGM02 can be found in TCCR0B, WGM00 and WGM01 in TCCR0A.
	WGM02:0 =	0  Normal
				1  PWM phase correct
				2  CTC
				3  Fast PWM 0xff
				4  Reserved
				5  PWM phase correct
				6  Reserved
				7  Fast PWM OCRA 
	*/
	TCCR0A = 0b11000011;
	/*
	TCCR0B
	-----------------------------------------------------------
	| FOC0A | FOC0B | - | - | WGM02 | CS02 | CS01 | CS00 |
	------------------------------------------------------------
	*/
    TCCR0B = 0b00000101;     //register TCCR1B // no scale
    DDRD = 0xff;     //set portd as output 
}
void turn(unsigned char i){
	if (i == 0)
		OCR0A = 215;     
	else if (i == 1)
		OCR0A = 230;
	_delay_ms(1000);
}

int main(void)
{   
    pwm_TC0_init();     //to initialize PWM

    while(1)
    {
		motor_move(STOP);
		turn(0);
		motor_move(FORWARD);
        _delay_ms(2000);

		motor_move(STOP);
		turn(1);
		motor_move(FORWARD);
        _delay_ms(2000);
    }
}
