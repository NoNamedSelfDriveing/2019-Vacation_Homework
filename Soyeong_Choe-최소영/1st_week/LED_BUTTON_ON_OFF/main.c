
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


int main(void)
{
    /* Replace with your application code */
	DDRB = 0xff;	//모든 B포트를 출력으로 설정
	DDRD = 0x00;	//모든 D포트를 입력으로 설정
	
    while (1) 
    {
		if(PIND &0x01) PORTB = 0xff;	//버튼이 눌렸다면 led를 켬
		else PORTB = 0x00;	//버튼이 눌리지 않았다면 led를 끔
    }
}

