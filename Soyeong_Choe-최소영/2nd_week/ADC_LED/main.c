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
void COMMAND(unsigned char byte)	// ��ɾ�
									// ���� ���� �Ǿ�����
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

void LCD_INIT(void)	//�ʱ�ȭ
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

void LCD_String(char * str)	//�۾�ǥ��
{
	char *pstr =0;
	pstr=str;
	while(*pstr)
	DATA(*pstr++);
}


//adc
int adc_read(int channel)
{
	ADMUX = (channel << MUX4) | (channel << MUX3) | (channel << MUX2) | (channel << MUX1);	// mux�� ����� adcä���� �����ϴ� ��Ʈ
	
	ADCSRA |= (1<<ADSC);	// 1�� ���ϴ� ���� ��ȯ ����	������ �ڵ����� 0���� ����
	while(!(ADCSRA & (1<<ADSC)));	// ��ȯ�� ���������� ��ٸ���
	
	return ADC;	// ADLAR�� 0���� �����Ǿ��ֱ⶧���� ADCH�� ����2��Ʈ ADCL���� 8��Ʈ�� ����
				// ���� return (ADCH << 2) | ADCL������
				// ADC�� return�ص� �ȴ� (avr���� �������)
}

void adc_init(void)
{
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));// 16Mhz/128= 125Khz
	ADMUX  |= (1<<REFS0);						// � ���� ���޿��� ������� ���� 01�̹Ƿ� AVCC(5V)
	ADCSRA |= (1<<ADEN);						// 1�� �����ϸ� adc�� ���
}

int main(void)
{
	LCD_INIT();
	adc_init();
	
	while(1)
	{
		int val = adc_read(0);	// val�̶�� ������ ����
		char string[8];
		
		sprintf(string, "%4d", val);	//val�� int�̹Ƿ� lcd�� ���� ���� sprintf�� ���
		
		COMMAND(HOME);
		LCD_String("val");
		COMMAND(LINE2);
		LCD_String(string);
	}
	return 0;
}
