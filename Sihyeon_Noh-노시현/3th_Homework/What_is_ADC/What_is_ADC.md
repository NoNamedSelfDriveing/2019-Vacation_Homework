# ADC(Analog to Digital Coverter)

 아날로그 신호(0V ~ 최대입력V 사이의 전압)을 디지털 값으로 변환해주는 기능

쉽게 말해 핀으로 인가되는 전압값이 ARef를 기준으로 했을 때 어느 정도의 비율을 가지는지 숫자로 알려주는 것이 ADC이다.

- 반대로 디지털 신호를 아날로그 신호로 바꿔주는 것을 DAC라고한다.

- ADC와 각종 센서를 이용하여 온도, 기울기, 속도, 조도 등을 디지털 값으로 변환하는 것이 가능하다.



## Avr의 ADC

### A/D   컨버터의 특징

- 8채널/내부 아날로그 멀티 플렉서 탑재
- 10비트 해상도를 지원하기 때문에 받아오는 값을 1024등분해서 0~1023 범위의 값으로 표현된다.

### A/D 컨버터의 구성

- 범용 PORTF의 특수 기능

  - ADC0 ~ ADC7 : 8채널 10비트 A/D컨버터의 아날로그 입력 단자

- ADC 정확도 성능 향상을 위한 독립 전원 구성

  - AVCC : Analog Supply Voltage(VCC의 전압의 ±0.3V유지 해야 함)
  - AGND : Analog Ground (반드시 GND와 연결)
  - AREF : Analog Reference Voltage

- 입력전압의 범위

  - 일반 모드 입력전압의 범위(0v ~ Vref)

  - 차동입력 모드 입력전압의 범위(-Vref ~ Vref)

- Vref의 범위
  - 전원전압 VCC를 초과할 수 없다.(Vref = VGND ~ VCC, 내부 기준전압 2.56V)



### 관련 레지스터

CPU가 ADC의 동작을 제어하기 위해서는 ADMUX, ADCSRA, ADCH/ADCL 레지스터들을 사용한다. 

1. ADMUX(ADC Multiplexer Selection Register)

   AVR에는 여러개의 ADC 입력 핀들이 있는데 그중에 하나를 선택해야 한다. 또한 AREF도 선택가능하다. 이러한 선택을 ADMUX를 통해서 한다. 그리고 ADC의 핵심인 Conversion Logic에서는 ADMUX에 의해 선택된 ADC입력 전압과 AREF 전압을 이용하여 입력전압 레벨을 측정하고, 그 결과를 ADCH/ADCL에 저장하는 기능을 담당한다.

2. ADCSRA(ADC Control and Status Register A)

   ADC값을 읽기 위해서는 conversion start명령을 주어야 한다. Conversion logic에서는 start 명령을 받으면 입력 전압을 측정하여 그 값을 ADCH/ADCL레지스터에 기록하는 것이다. 이 때 한 번만 ADC변환을 수행하여 값을 읽어 올수도 있고, 계속해서 자동으로 Conversion 시킬 수도 있다.

   - A/D 컨버터의 동작
     - 단일변환모드(Single conversion mode) : 한 번만 변환하는 모드
     - 프리런닝모드(Free running mode) : 연속해서 변환하는 모드

    이 떄 start명령과 값을 몇번 읽어올지 설정하는 것이 ADCSRA레지스터이다. 그 밖에도 프리스케일러를 지정해줄 수 있다. ADC가 정상동작하기 위해서 50~200kHz의 클럭을 인가해주어야하기 때문이다.

3. ADCH/L (ADC Data Register)

   ADC의 변환결과를 저장한다.

### 레지스터 세부 사항

1. ADMUX

   - Bit 7, 6 - REFS1, REFS0 (Reference Selection Bit)

     - ADC에서 사용하는 기준전압을 설정한다.

       | REFS1 | REFS0 | 기준전압                                   |
       | ----- | ----- | ------------------------------------------ |
       | 0     | 0     | 외부의 AREF 단자로 입력된 전압을 사용한다. |
       | 0     | 1     | 외부의 AVCC 단자로 입력된 전압을 사용한다. |
       | 1     | 0     | -                                          |
       | 1     | 1     | 내부의 2.56V를 사용한다.                   |

   - Bit 5 - ADLAR (ADC Left Adjust Result)

     - 변환 결과가 ADC레지스터에 저장될 때 정렬 방식을 정하는데 사용한다.

     - ADLAR = 1 : 변환결과 값을  ADCH/L에 저장할 때 좌측으로 끝을 맞추어 저장한다.
     - ADLAR = 0 : 변환결과 값을 ADCH/L에 저장할 떄 우측으로 끝을 맞추어 저장한다.

   - Bit 4,3,2,1,0 - MUXn(Analog Channel and Gain Selection Bit)

     - ADC변환기의 아날로그 입력 채널 및 Gain을 결정한다.

2.  ADCSRA

   - Bit 7 - ADEN (ADC Enable)

     - ADEN = 1 : ADC 활성화
     - ADEN = 0 : ADC 비활성화

   - Bit 6 - ADSC (ADC Start Conversion)

     - ADSC = 1 : ADC의 변환이 시작된다. (단일 변환모드일 때 1번만작동, 프리런닝 모드일 때 변환 동작 반복)
     - ADSC = 0 : ADC변환이 시작되지 않는다.

   - Bit 5 - ADFR (ADC Free Running Select)

     - ADFR = 1 : 프리런닝 모드
     - ADFR = 0 : 단일변환 모드

   - Bit 4 - ADIF (ADC Interrupt Flag)

     - ADC변환완료 인터럽트가 요청되고 그 상태를 이 비트에 표시한다.

   - Bit 3 - ADIE (ADC Interrupt Enable)

     - ADIE = 1 : ADC Interrupt 활성화 (이 때 SREG레지스터의 I비트가 SET되어 있어야한다. )
       - SREG(Status Register) : 모든 종류의 인터럽트를 사용하기 위해서는 SREG의 7번비트가 SET되어 있어야한다.
     - ADIE = 0 : ADC Interrupt 비활성화

   - Bit 2, 1, 0 - ADPS 2 ~ 0 (ADC Prescaler Select Bit)

     - ADC에 인가되는 클럭의 분주비를 설정한다.

       | ADPS2 | ADPS1 | ADPS0 | 분주비 |
       | ----- | ----- | ----- | ------ |
       | 0     | 0     | 0     | 2      |
       | 0     | 0     | 1     | 2      |
       | 0     | 1     | 0     | 4      |
       | 0     | 1     | 1     | 8      |
       | 1     | 0     | 0     | 16     |
       | 1     | 0     | 1     | 32     |
       | 1     | 1     | 0     | 64     |
       | 1     | 1     | 1     | 128    |

       