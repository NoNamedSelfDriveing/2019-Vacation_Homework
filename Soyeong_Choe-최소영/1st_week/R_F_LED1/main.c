
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
    /* Replace with your application code */
    DDRB = 0xff;
	
	unsigned char left;
	unsigned char right;
	int i;
	
	while (1) 
    {
		PORTB = 0x00;  // 다 꺼진 led로 설정
		_delay_ms(1000);
		for(i=0;i<4;i++)
		{
			left = 0b0000001 << i;  // 왼쪽으로 비트를 민다
			right = 0b10000001 >> i;  // 오른쪽 비트를 민다
			PORTB = PORTB ^ (left | right);  // 왼쪽으로 민 비트와 오른쪽으로 민 비트를 전의 비트와 합친다
			_delay_ms(1000);
		}
		for(i=0;i<3;i++)  //위의 과정을 한번 더 반복한다
		{
			left = 0b00001000 >> i;
			right = 0b00010000 << i;
			PORTB = PORTB ^ (left | right);
			_delay_ms(1000);
		}
		
    }
}

