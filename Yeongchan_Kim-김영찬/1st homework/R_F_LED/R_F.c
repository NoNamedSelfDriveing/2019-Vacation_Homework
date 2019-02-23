#define F_CPU 16000000UL 
#define SPEED 100

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRA = 0xff;
    
    while(1)
    {
        PORTA = 0b00000000;
        _delay_ms(SPEED);

	PORTA = 0b10000001;
        _delay_ms(SPEED);

	PORTA = 0b11000011;
        _delay_ms(SPEED);

	PORTA = 0b11100111;
        _delay_ms(SPEED);

	PORTA = 0b11111111;
        _delay_ms(SPEED);

	PORTA = 0b11100111;
        _delay_ms(SPEED);

	PORTA = 0b11000011;
        _delay_ms(SPEED);

	PORTA = 0b10000001;
        _delay_ms(SPEED);
    }
}

소스 이렇게 때려박지 말라고 하셨는데 어떻게 해야할지 잘몰라서 이렇게라도 올립니다 
