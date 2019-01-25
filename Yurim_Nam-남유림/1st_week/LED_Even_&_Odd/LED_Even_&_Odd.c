#include <asf.h>
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main (void) {
	
	while (1) {
		DDRA = 0xff;
		
		PORTA = 0b10101010;
		_delay_ms(1000);
		PORTA = 0b01010101;
		_delay_ms(1000);
	}
}
