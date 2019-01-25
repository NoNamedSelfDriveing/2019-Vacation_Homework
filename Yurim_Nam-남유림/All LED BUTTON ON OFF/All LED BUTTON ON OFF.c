#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main (void) {
	
	while (1) {
		DDRA = 0xff;
		if (PINC0 == 1) {
			PORTA = 0x00;
			} else {
			PORTA = 0xff;
		}
	}
}