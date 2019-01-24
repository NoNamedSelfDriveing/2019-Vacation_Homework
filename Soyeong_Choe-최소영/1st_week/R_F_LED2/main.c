
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
    /* Replace with your application code */
    
	DDRB = 0xff; //모든 B포트를 출력으로 설정
	DDRD = 0x00; //모든 D포트를 입력으로 설정
	
	int i;	//반복변수
	int n;
	
	while (1) 
    {
		if(PIND == 1)
		{
			for(i=0;i<18;i++)
			{
				if(PIND == 0) break;
				
				else if(i<8)
				PORTB = 0b00000001 << i;
				
				else if(i<14)
				{
					n = i - 8;
					PORTB = (0b11111111 ^ (0b00000011 << n)) & 0b01111111;	
				}
				
				else if(i<17)
				{
					n = i -14;
					PORTB = 0b11100000 | (0b00000111 << n);	
				}
				
				else if(i==17)
				PORTB = ~PORTB;
				
				_delay_ms(1000);		
			}
		}
    }
}