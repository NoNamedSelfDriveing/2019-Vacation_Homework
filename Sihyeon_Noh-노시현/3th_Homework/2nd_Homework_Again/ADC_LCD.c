/*
 * ADC_LCD.c
 *
 * Created: 2019-02-15 오전 2:06:37
 * Author : tlgus
 */ 

#define FUNCSET 0x28 //function set, 데이터 선 4비트, 2줄로 표시, 5X7비트 사용
#define ENTMODE 0x06 //entry mode set, LCD표시창에 문자를 표시하고 커서를 오른쪽으로 이동 
#define ALLCLR 0x01 //all clear, LCD표시창을 클리어시키고 커서를 첫 줄의 첫 칸에 위치
#define DISPOFF 0x08 //display off, 표시 off
#define DISPON 0x0c //display on, 표시 on
#define LINE2 0xc0 //2nd line move, 커서를 2번째 줄로
#define HOME 0x02 //Cursor Home, 커서를 홈 위치로
#define F_CPU 16000000
  
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void COMMAND(unsigned char Byte);
void DATA(unsigned char byte);
void LCD_INIT(void);
void LCD_String(char * str);
void ADC_INIT();
unsigned int ADC_READ();
void IO_SETTING();

int main(void)
{
	IO_SETTING(); //입출력 설정
	LCD_INIT();	//LCD초기화
	ADC_INIT(); //ADC 초기화
	
	char string[16];	//문자열을 저장
    int value;			//adc 결과 값
	/* Replace with your application code */
    while (1) 
    {
		value = ADC_READ();	//adc 결과 값 읽어서 value변수에 저장
		sprintf(string, "Value = %4d", value); //문자열 변수에 adc 결과 값 저장
		_delay_ms(10);
		
		
		COMMAND(HOME);		//커서를 홈으로 
		LCD_String(string); //string 변수에 저장된 값 LCD에 출력
    }
	return 0;
}

void IO_SETTING()
{
	DDRE = 0xFF; //PORTE를 출력으로 설정
	DDRF = 0x00; //PORTF를 입력으로 설정
}

void COMMAND(unsigned char byte)
{
	_delay_ms(2);
	
	PORTE = byte & 0xf0; // Byte 상위 4비트 입력
	PORTE &= 0b11111100; //RS = 0, R/W = 0, 제어 명령 쓰기
	
	_delay_us(1);
	PORTE |= 0b00000100; //en = 1, 동작 허가
	_delay_us(1);
	PORTE &= 0b11111011; //en = 0, 동작 허가 안함
	
	PORTE =(byte<<4) & 0xf0; //명령어 하위 4비트 입력
	PORTE &= 0b11111100;		//RS = 0, R/W = 0, 제어 명령 쓰기
	
	_delay_us(1);
	PORTE |= 0b00000100;		//en = 1, 동작 허가
	_delay_us(1);
	PORTE &= 0b11111011;		//en = 0, 동작 허가 안함
}

void DATA(unsigned char byte)
{
	_delay_ms(2);
	
	PORTE = byte & 0xf0; //Byte의 상위 4비트 입력
	
	PORTE |= 0b00000001; //DR에 데이터 값 쓰기로 설정
	PORTE &= 0b11111101; //DR에 데이터 상위 4비트 쓰는 것을 허가
	
	_delay_us(1);
	PORTE |= 0b00000100; //동작 허가
	_delay_us(1);
	PORTE &= 0b11111011; //동작 허가 안함
	
	PORTE =(byte<<4) & 0xf0; //Byte 하위 4비트 입력
	PORTE |= 0b00000001; //DR에 데이터 값 쓰기로 설정
	PORTE &= 0b11111101; //DR에 데이터 하위 4비트 쓰는 것을 허가
	
	_delay_us(1);
	PORTE |= 0b00000100; //동작 허가
	_delay_us(1);
	PORTE &= 0b11111011; //동작 허가 안함
}

void LCD_INIT(void)
{
	COMMAND(FUNCSET);
	_delay_us(40);
	
	COMMAND(ENTMODE);
	_delay_us(40);
	
	COMMAND(DISPON);
	_delay_us(40);
	
	COMMAND(ALLCLR);
	_delay_ms(1.64);
}

void LCD_String(char * str)
{
	char *pstr = 0; //문자 하나를 가리키는 char 포인터 변수 선언
	pstr=str; //포인터 변수에 문자열 주소 넣기
	while(*pstr)	// 문자열이 EOF가 아닐 때 까지
	DATA(*pstr++);	//문자 하나 씩 출력
}

void ADC_INIT()
{
	ADMUX  = 0b00000000;						//ADC0 단극성 입력
	ADMUX  |= (0<<REFS1) | (1<<REFS0);			//외부의 AVCC단자로 입력된 전압 사용
	ADMUX  |= (0<<ADLAR);						//변환 결과를 오른쪽 정렬
	
	ADCSRA |= (1<<ADSC);					    //변환 시작
	ADCSRA |= (1<<ADFR);					   	//프리런닝 모드
	ADCSRA |= (1<<ADEN);						 //ADC 허가
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0));// 프리스케일러 64로 설정
	
}
unsigned int ADC_READ()
{
	unsigned int adcValue;
	
	while(!(ADCSRA & (1<<ADIF)));			//인터럽트 플래그를 확인하여 변환이 완료될 때까지 기다린다.
	ADCSRA |= (1<<ADIF);					//인터럽트 플래그 클리어
	adcValue = ADCL + (ADCH<<8);	//ADCH레지스터와 ADCH레지스터의 결과를 합쳐서 adcValue변수에 저장
	
	return adcValue;				//adc결과 값을 리턴한다.
}