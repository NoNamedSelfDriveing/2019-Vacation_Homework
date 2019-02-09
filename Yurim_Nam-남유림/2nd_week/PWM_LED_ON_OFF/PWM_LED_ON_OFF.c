#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
	DDRB = 0xff;
	TCCR0 = 0b01111010;
	
	while (1) {
		OCR0 = 0x00;
		_delay_ms(1000);
		OCR0 = 0x3f;
		_delay_ms(1000);
		OCR0 = 0x7f;
		_delay_ms(1000);
		OCR0 = 0xbf;
		_delay_ms(1000);
		OCR0 = 0xff;
		_delay_ms(1000);
		OCR0 = 0xbf;
		_delay_ms(1000);
		OCR0 = 0x7f;
		_delay_ms(1000);
		OCR0 = 0x3f;
		_delay_ms(1000);
		OCR0 = 0x00;
		_delay_ms(1000);
	}
}