#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main (void) {
	int i, j;
	unsigned char h = 0b0000001;
	while (1) {
		DDRA = 0xff;
		if (PINC0 == 1) {
			for (i=0; i<18; i++) {
				if (PINC0 == 1) break;
				else if(i<8) {
					PORTA = h << i;
				} else if (i<14) {
					j = i-8;
				} else if (i<17) {
					j = i-14;
					PORTA = 0b11100000 | (0b00000111 << j);
				} else {
					PORTA = 0b11000000;
				}
				_delay_ms(1000);
			}
		}
	}
}