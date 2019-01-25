/*
 * All LED ON OFF.c
 *
 * Created: 2019-01-26 오전 12:36:18
 * Author : tlgus
 */ 

#define F_CPU 16000000UL	//사용중인 크리스탈 값을 상수로 설정
#include <avr/io.h>			//AVR 입출력 설정 헤더파일
#include <util/delay.h>		//delay지연 헤더파일

int main(void)
{
	PORTA = 0x00;			//포트A의 초기값
	DDRA = 0xFF;			//포트A의 모든 포트를 출력으로 사용
	
    /* Replace with your application code */
    while (1) 
    {
		PORTA = 0xFF;		//모든 포트A에 5V출력
		_delay_ms(1000);	//1초 지연
		PORTA = 0x00;		//모든 포트A에 0V출력
		_delay_ms(1000);	//1초 지연	
    }
	return 0;
}

