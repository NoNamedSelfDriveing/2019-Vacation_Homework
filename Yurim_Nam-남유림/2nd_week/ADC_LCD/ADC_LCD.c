#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <asf.h>
#include <stdio.h>

#define FUNCSET 0x28 //function set
#define ENTMODE 0x06 //entry mode set
#define ALLCLR 0x01 //all clear
#define DISPOFF 0x08 //display off
#define DISPON 0x0c //display on
#define LINE2 0xc0 //2nd line move
#define HOME 0x02 //Cursor Home

//LCD 커서 옮기는 함수
void COMMAND(unsigned char byte)
{
	_delay_ms(2);
	
	PORTA = byte & 0xf0;
	PORTA &= 0b11111100;
	
	_delay_us(1);
	PORTA |= 0b00000100;
	_delay_us(1);
	PORTA &= 0b11111011;
	PORTA =(byte<<4) & 0xf0;
	PORTA &= 0b11111100;
	_delay_us(1);
	PORTA |= 0b00000100;
	_delay_us(1);
	PORTA &= 0b11111011;
}

void DATA(unsigned char byte)
{
	_delay_ms(2);
	
	PORTA = byte & 0xf0;
	
	PORTA |= 0b00000001;
	PORTA &= 0b11111101;
	_delay_us(1);
	PORTA |= 0b00000100;
	_delay_us(1);
	PORTA &= 0b11111011;
	
	PORTA =(byte<<4) & 0xf0;
	PORTA |= 0b00000001;
	PORTA &= 0b11111101;
	_delay_us(1);
	PORTA |= 0b00000100;
	_delay_us(1);
	PORTA &= 0b11111011;
}

//LCD 초기화 함수
void LCD_INIT(void)
{
	DDRA = 0xff;
	PORTA &= 0xfb;
	_delay_ms(30);
	COMMAND(0b00101000);
	_delay_us(39);
	
	COMMAND(0b00001100);
	_delay_us(39);
	
	COMMAND(0b00000001);
	_delay_ms(1.53);
	
	COMMAND(0b00000110);
}

//문자열을 LCD에 띄우는 함수
void LCD_String(char * str)
{
	char *pstr =0;
	pstr=str;
	while(*pstr)
	DATA(*pstr++);
}

//ADC 초기화 함수
int ADC_INIT(void) {
	ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)); //ADCSRA 초기화
	ADMUX |= (1 << REFS0); //ADMUX 초기화
	ADCSRA |= (1 << ADEN); //ADCSRA 초기화
}

//ADC 값을 읽는 함수
int ADC_read(int channle) {
	ADMUX = (channle << MUX4) | (channle << MUX3) | (channle << MUX2) | (channle << MUX1); //채널 설정
	ADCSRA |= (1 << ADSC); //ADCSRA를 활성화 시켜 ADC를 불러옴
	
	while (!(ADCSRA & (1 << ADSC))); //ADC를 성공적으로 불러올 때까지 기다림
	
	return ADC; //ADC 값 반환
}

int main (void)
{
	int val;
	char string[8];
	LCD_INIT();
	ADC_INIT();
	
	while(1) {
		val = ADC_read(0);
		sprintf(string, "%4d", val);
		
		COMMAND(HOME);
		LCD_String("value");
		COMMAND(LINE2);
		LCD_String(string);
	}
	return 0;
}
