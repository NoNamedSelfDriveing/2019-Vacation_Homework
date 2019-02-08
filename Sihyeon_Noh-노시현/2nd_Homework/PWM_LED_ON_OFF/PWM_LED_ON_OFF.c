/*
 * PWM_LED_ON_OFF.c
 *
 * Created: 2019-02-09 오전 12:45:14
 * Author : tlgus
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void Io_setting(void);
void Timer_setting(void);

int main(void)
{
	int i;		//for문 제어변수
	Io_setting();				
	Timer_setting();			
    
	/* Replace with your application code */
    while (1) 
    {
		OCR0 = 0;			//출력 비교 레지스터, TCNT0의 값에 따라 값이 바뀜. 값이 같아질 때, 비교매치가 발생하고 OC0이 클리어(0V)출력된다. 그리고 TOP에서 BOTTOM이 될 떄 셋(5V)된다. (비 반전 출력 모드 기준)
		
		for(i=0;i<256;i++)		//10ms마다 duty비 1/256씩 증가
		{
			OCR0++; 	
			_delay_ms(10);
		}
		
		for(i=255;i>=0;i--)		//10ms마다 duty비 1/256씩 감소
		{
			OCR0--;
			_delay_ms(10);
		}
    }
	return 0;
}

void Io_setting(void)
{
	DDRB |= (1<<PORTB4);		
	//PB4(OC0) 출력으로 설정, OC0(타이머0 출력, 8비트), OC뒤에 숫자는 타이머 번호를 말한다. 0과2는 8비트 타이머, 1과3은 16비트 타이머를 말한다.
}

void Timer_setting(void)
{
	TCCR0 |= (1<<CS02);			//프리스케일러 64로 설정
	TCCR0 |= (1<<WGM01) | (1<<WGM00);	//FAST PWM 모드로 설정 (0 0 = Normal, 0 1 = Phase Correct PWM, 1 0 = CTC, 1 1 = FAST PWM)
	TCCR0 |= (1<<COM01) | (0<<COM00);	//Source current방식을 사용하였으므로 조금 더 이해가 편한 non-inverting mode로 설정했다. (0<<COM00)는 굳이 안해도 됨.
	TCNT0 = 0;		//카운터 초기화, 클럭이 카운트 될 떄마다 자동으로 1씩 증가한다. 값이 255일 때마다 오버플로우 인터럽트가 발생한다.
}

//1초 주기 점등은 자고 일어나서 하겠습니다.