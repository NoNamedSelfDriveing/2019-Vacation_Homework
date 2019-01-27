/*
 * R_F_LED1.c
 *
 * Created: 2019-01-27 오후 1:34:01
 * Author : tlgus
 */ 

#include <avr/io.h>			//AVR 입출력 설정 헤더파일
#define F_CPU 16000000UL	//사용중인 크리스탈 값을 상수로 설정
#include <util/delay.h>		//delay지연 헤더파일


int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x00;
	unsigned char downToUpBit;
	unsigned char upToDownBit;
	int i;
    /* Replace with your application code */
    while (1) 
    {
		downToUpBit= 0;
		upToDownBit = 7;
		for(i=0;i<4;i++)		//(0, 7), (1, 6), (2, 5), (3, 4)번 LED를 차례로 ON한다.
		{
			PORTA |= (1<<downToUpBit) | (1<<upToDownBit);
			upToDownBit--;
			downToUpBit++;
			_delay_ms(1000);
		}
	
		for(i=0;i<4;i++)		//(3, 4), (2, 5), (1, 6), (0, 7)번 LED를 차례로 OFF한다.
		{
			if((PORTA>>upToDownBit) % 2 && (PORTA>>downToUpBit) % 2)	
				PORTA -= (1<<upToDownBit) | (1<<downToUpBit);
			upToDownBit--;
			downToUpBit++;
			_delay_ms(1000);
		}
    }
	return 0;
}

