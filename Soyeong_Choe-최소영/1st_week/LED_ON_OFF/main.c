
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void)
{	
	
    /* Replace with your application code */
    while (1) 
    {
		DDRB = 0xff;	// B포트를 모두 출력모드로 설정
		PORTB = 0x00;	// 모든 led를 끔
		_delay_ms(1000);// 1초 딜레이
		
		PORTB = 0xff;	// 모든 led를 켬
		_delay_ms(1000);// 1초 딜레이
    }
}

