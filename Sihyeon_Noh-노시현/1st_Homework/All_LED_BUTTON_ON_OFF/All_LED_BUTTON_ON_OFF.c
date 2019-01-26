/*
 * All_LED_BUTTON_ON_OFF.c
 *
 * Created: 2019-01-27 오전 2:33:37
 * Author : tlgus
 */ 

#include <avr/io.h>			//AVR 입출력 설정 헤더파일
#define F_CPU 16000000UL	//사용중인 크리스탈 값을 상수로 설정
#include <util/delay.h>		//delay지연 헤더파일


int main(void)
{
	DDRA = 0XFF;		//A포트를 출력포트로 설정	
	PORTA = 0x00;		//A포트에 0V출력(초기화)
	DDRC = 0X00;		//C포트를 입력포트로 설정
	PORTC = 0x00;		//C포트의 입력 상태를 LOW값으로 설정(초기화)
	unsigned char btStat;
    /* Replace with your application code */
    while (1) 
    {
		btStat = PINC & 0b00000001;			
		/*C포트의 상태를 읽어드리고 and 연산을 통해 현재 PC0의 입력상태를 확인한다.
		 예를 들어 버튼을 눌렀다면 PINC는 0b0000 0001이 되는데 and연산을 하고 나면 1(HIGH)가 된다. 
		 누르지 않았을 때는 PINC는 0b0000 0000을 돌려줄것이다. 여기에 and연산을 하고 나면 0(LOW)가 된다.	
		*/
		if (btStat)	//버튼의 입력 상태가 HIGH일 경우
			PORTA = 0xFF;	//모든 A포트에 5V출력
		else				//만약 버튼(PC0번)의 입력이 LOW라면
			PORTA = 0x00;	//모든 A포트에 0V 출력
    }
	return 0;
}

