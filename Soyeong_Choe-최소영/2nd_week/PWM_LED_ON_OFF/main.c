
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
	DDRB = 0xff;
	TCCR0 = 0b01101010;	//2~0��Ʈ�� ���ֺ�: 8����		6��3��Ʈ�� ���: fastpwm		5~4��Ʈ�� 00�϶� ocn����, 10�� �����, 11������: 10(�����)
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

