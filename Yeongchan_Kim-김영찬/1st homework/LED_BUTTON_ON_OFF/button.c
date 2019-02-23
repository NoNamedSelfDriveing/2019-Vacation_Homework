#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main (void) {
    DDRA = 0xff;
    DDRD = 0x00

   while (1) {
        if (PIND == 1) {
	PORTA = 0x00;
}
       else {
       PORTA = 0xff;
		}
	}
}
