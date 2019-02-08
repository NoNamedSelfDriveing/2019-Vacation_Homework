
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
	DDRB = 0xff;
	TCCR0 = 0b01101010;	//2~0비트는 분주비: 8분주		6과3비트는 모드: fastpwm		5~4비트는 00일때 ocn차단, 10은 비반전, 11은반전: 10(비반전)
	unsigned char i;
    /* Replace with your application code */
	while (1) 
    {
		for(i=0;i<256;i++)
		{
			OCR0 = i;
			_delay_ms(4);
		}
		for(i=255;i>=0;i--)
		{
			OCR0 = i;
			_delay_ms(4);
		}
    }
}

