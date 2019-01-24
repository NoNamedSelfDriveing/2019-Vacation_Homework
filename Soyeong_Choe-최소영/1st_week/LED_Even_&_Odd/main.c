
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
    /* Replace with your application code */
	
    DDRB = 0xff;	//모든 B포트를 출력으로 설정
	while (1) 
    {
		PORTB = 0b10101010;
		_delay_ms(1000);
		PORTB = 0b01010101;
		_delay_ms(1000);
    }
}

