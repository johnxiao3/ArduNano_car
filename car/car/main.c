#include <avr/io.h>
#define F_CPU 16000000UL     //8MHz CPU frequency
#include <util/delay.h>     //To use _delay_ms()

void pwm_init()     //to initialize PWM
{
    /*
	TCCR0A
	-------------------------------------------------------------
	| COM0A1 | COM0A0 | COM0B1 | COM0B0 | - | - | WGM01 | WGM00 |
	-------------------------------------------------------------
	FastPWM mode: COM0x1:0 =	0 normal,OC0x disconnected; 
								1 Toggle OC0x on compare match; 
								2 clear OC0x on compare match, set at bottom
								3 set OC0x on compare match, clear at bottom
	
	*/
	TCCR0A = 0b10100011;
	  
    TCCR1B = 0b00000001;     //register TCCR1B
    DDRD = 0xff;     //set portd as output 
}

int main(void)
{   
    pwm_init();     //to initialize PWM
    //D0 and D1 for right motor, D2 and D3 for left motor
    while(1)
    {
        PORTD = 0b00000101;
        OCR1A = 1023;     //maximum
        OCR1B = 500;
        _delay_ms(2000);

        PORTD = 0b00000110;
        OCR1A = 500;
        OCR1B = 1023;     //maximum
        _delay_ms(2000);
    }
}
