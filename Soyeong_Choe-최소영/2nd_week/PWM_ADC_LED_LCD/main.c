#define FUNCSET 0x28 //function set
#define ENTMODE 0x06 //entry mode set
#define ALLCLR 0x01 //all clear
#define DISPOFF 0x08 //display off
#define DISPON 0x0c //display on
#define LINE2 0xc0 //2nd line move
#define HOME 0x02 //Cursor Home

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

//lcd
void COMMAND(unsigned char byte)	// 명령어
// 위에 정의 되어있음
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

void LCD_INIT(void)	//초기화
{
	DDRA = 0xFF;
	PORTA &= 0xFB;
	
	_delay_ms(30);
	COMMAND(0b00101000);
	_delay_us(39);
	
	COMMAND(0b00001100);
	_delay_us(39);
	
	COMMAND(0b00000001);
	_delay_ms(1.53);
	
	COMMAND(0b00000110);
}

void LCD_String(char * str)	//글씨표시
{
	char *pstr =0;
	pstr=str;
	while(*pstr)
	DATA(*pstr++);
}


//adc
int adc_read(int channel)
{
	ADMUX = (channel << MUX4) | (channel << MUX3) | (channel << MUX2) | (channel << MUX1);	// mux는 사용할 adc채널을 결정하는 비트
	
	ADCSRA |= (1<<ADSC);	// 1로 변하는 순간 변환 시작	끝나면 자동으로 0으로 변함
	while(!(ADCSRA & (1<<ADSC)));	// 변환이 끝날때까지 기다린다
	
	return ADC;	// ADLAR이 0으로 설정되어있기때문에 ADCH에 상위2비트 ADCL하위 8비트를 저장
	// 따라서 return (ADCH << 2) | ADCL이지만
	// ADC를 return해도 된다 (avr에서 만들어줌)
}

void adc_init(void)
{
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));// 16Mhz/128= 125Khz
	ADMUX  |= (1<<REFS0);						// 어떤 전원 공급원을 사용할지 결정 01이므로 AVCC(5V)
	ADCSRA |= (1<<ADEN);						// 1로 설정하면 adc를 허용
}

int main(void)
{
	LCD_INIT();
	adc_init();
	DDRB = 0xFF;
	TCCR0 = 0b01101010;	//2~0비트는 분주비: 8분주		6과3비트는 모드: fastpwm		5~4비트는 00일때 ocn차단, 10은 비반전, 11은반전: 10(비반전)
	
	while(1)
	{
		int val = adc_read(0);	// val이라는 변수에 저장
		char string[8];
		
		sprintf(string, "%4d", val);	//val는 int이므로 lcd에 띄우기 위해 sprintf를 사용
		
		COMMAND(HOME);
		LCD_String("val");
		COMMAND(LINE2);
		LCD_String(string);
		
		OCR0 = 255*((float)val)/1024;		// val:1024 = x : 255	->	1024x = 255*val		->		x = 255*val/1024
	}
	return 0;
}
