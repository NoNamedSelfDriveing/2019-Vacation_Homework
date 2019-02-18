/짝수 
#include <avr/io.h>

int main(void)
{
    DDRA = 0xff;
    PORTA = 0b00001010;

    return 0;
}


/홀수
#include <avr/io.h>

int main(void)
{
    DDRA = 0xff;
    PORTA = 0b00010101;

    return 0;
}
