/*
 * All LED ON OFF.c
 *
 * Created: 2019-01-26 오전 12:36:18
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	PORTA = 0x00;
	DDRA = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		PORTA = 0xFF;
		_delay_ms(1000);
		PORTA = 0x00;
		_delay_ms(1000);
    }
	return 0;
}

