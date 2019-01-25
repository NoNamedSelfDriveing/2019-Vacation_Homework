#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main (void) {
	
	int i, o, t, h;
	while (1) {
		DDRA = 0xff;
		h = 0b00000000;
		for (i=0; i<=4; i++) {
			PORTA = h;
			o = 0b00000001 << i;
			t = 0b10000000 >> i;
			h = h | (o | t);
			_delay_ms(1000);
		}
		for (i=0; i<=4; i++) {
			PORTA = h;
			o = 0b00001000 >> i;
			t = 0b00010000 << i;
			h = h ^ (o | t);
			_delay_ms(1000);
		}
	}
}
