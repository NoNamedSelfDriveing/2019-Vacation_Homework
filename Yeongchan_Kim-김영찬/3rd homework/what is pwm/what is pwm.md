## PWM이란?
### 정의
Pulse Width Modulation 의 약자이며
일정한 주기 내에서 Duty 비를 변화 시켜서 평균전압을 제어하는 방법 입니다.
### 특징

주로 LED 조명제품의 광량이나 DC모터의 속도제어를 조절하는 컨트롤러에 많이 사용됩니다. 
 PWM 제어라고 하면 펄스의 폭을 조정하여 부하에 전력의 크기를 조절하는 것이며,
이렇게 PWM의 duty ratio를 바꾸어줌으로서 자신이 원하는 밝기로 조명을 Dimming 할 수 있게 됩니다.
12V를 만들고 싶으면 0V와 24V를 같은 비율로 하여(Duty ratio 50%) 빠른 속도로 바꿔 줍니다.
그럼 출력은 같은 비율을 유지하면서 0,25,0,25,0,25 로 빠르게 바뀌게 되는데요
이때 조명은 입력전압이 12V인 것처럼 인식한다는 것이 PWM의 핵심입니다.

### ![pwm](C:\\/실습/pwm.png)
* 장점 : 전원효율이 좋아진다.
* 단점 : 회로가 복잡해진다, 스위칭될때 발생하는 노이즈로 인해 전자기파가 많이 발생한다. 

