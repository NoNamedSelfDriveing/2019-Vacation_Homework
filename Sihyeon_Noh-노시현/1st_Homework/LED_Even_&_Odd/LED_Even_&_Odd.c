#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;			//포트A를 모두 출력으로 설정
	PORTA = 0x00;			//포트A에 모두 0V출력 (초기값)
    
	int i = 0;				//for문 제어 변수
	int turn = 0;			//if문에서 홀수나 짝수 중 어떤 것을 ON해야 할 지 확인하는 변수		짝수 == 0, 홀수 == 1
	/* Replace with your application code */
    while (1) 
    {
		for (i = 0; i < 8; i++)			//PORTA0 ~ PORTA7까지 반복
		{
			if(i%2==turn)		//짝수라면	혹은	  홀수하면
			{
				PORTA |= 1<<i;		//짝수 또는 홀수 번 째 LED를 1개씩 ON 한다.
			}
		}
		_delay_ms(1000);		//1초 상태 유지
		PORTA = 0x00;			//모든 LED에 0V를 출력해서 초기화한다.
		if (turn==0)	turn = 1;	//만약 방금 짝수 LED에 5V출력을 했다면 이번에는 홀수 번째에 5V를 출력하기 위해 turn값을 1로 바꾼다.
		else            turn = 0;	//만약 방금 홀수 LED에 5V출력을 했다면 이번에는 짝수 번째에 5V를 출력하기 위해 turn값을 0으로 바꾼다.

    }
	return 0;
}

