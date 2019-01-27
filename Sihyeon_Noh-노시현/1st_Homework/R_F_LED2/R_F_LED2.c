/*
 * R_F_LED2.c
 *
 * Created: 2019-01-27 오후 8:16:27
 * Author : tlgus
 */ 

#include <avr/io.h>			//AVR 입출력 설정 헤더파일
#define F_CPU 16000000UL	//사용중인 크리스탈 값을 상수로 설정
#include <util/delay.h>		//delay지연 헤더파일

int main(void)
{
	DDRA = 0xFF;
	DDRC = 0x00;
	int num = 0b10000000;		
	unsigned char btStat = 0;	
	int i = 0;
	
    /* Replace with your application code */
    while (1) 
    {
		btStat = PINC & 0b00000001;		//버튼의 입력상태 저장
		if(btStat)						//버튼을 눌렀을 때
		{
			PORTA = 0x00;				//모든 LED를 끈다.
			PORTA |= num;				//num과 or연산을 해서 정해진 LED를 킨다.
			num = num>>1;				//num에 시프트 연산을 해서 다음 켜야할 LED를 변수에 담는다.
			_delay_ms(1000);			//1초 기다린다.
			
			if(i==7)					//만약 마지막 LED까지 켰다면
			{	
				num = 0b10000000;		//다시 처음부터 켜기위해 num값을 바꾼다.
				i = 0;					//다시 처음부터 켠다는 것을 알기위해서 i값을 초기화한다.
			}
			else
				i++;					//마지막까지 켜지 않았다면 다음 LED를 켰다는 것을 확인하기 위해 i값을 1증가시킨다.
		}	
	}
	return 0;
	/*
	그 다음 시퀀스부터는 알고리즘이 이해가 잘 안되서 8번 시퀀스까지만 했습니다.
	*/
}

