<div align="justify">
<h2>사회적 약자를 위한 계단 자율 주행 시스템</h2>
요즘 사회는 장애인을 비롯한 사회적 약자분들을 위한 시스템이 잘 구축되어 있다. 그러나 아직 세밀한 부분에서는 사회적 약자분들을 위한 장치가 잘 마련되어 있지 않다는 것이 현실이다.
<br/><br/>
활용할 기술들 중 이미 완성 되어있는 기술들은 많지만, 우리가 목표로 하는 사회적 약자분들을 위한 운송 수단의 경우 아직 자동화나 자율주행 측면, 계단과 같은 Z축 운송이 필요한 측면에서 미흡한 모습을 보이고, 단순히 자동차와 같은 운송 수단의 자율 주행에 중점을 둔 기술들은 상용화된 운송수단의 자율 주행 쪽에만 기술이 편중되어 사회적 약자분들의 편의성은 잘 고려하지 못하고 있는 것을 발견했다.
<br/><br/>
따라서 우리는 학부 과정에서 배운 내용과 여러 논문 자료를 바탕으로 개선된 시스템을 만들어 기계공학(재료 응력 해석, 동역학적 거동 파악, 리니어모터의 구현), 전기전자공학(모터 제어, 전동화 장비), 컴퓨터공학(자율주행 시스템)이 한데 엮인 계단 자율 주행 시스템 운송 수단을 제작하였다.
</div>

<p align="center">
  <br>
  <img src="https://github.com/HarrysK99/EV-Autonomous/assets/81846798/7e3aea43-6339-4dac-994a-9a40ad21df3e">
  <br>
</p>

## 목차
  - [개요](#개요) 
  - [구현 기능](#구현-기능)
  - [보완할 점](#보완할-점)

<br>

## 개요
- 프로젝트 지속기간: 2023.04-2023.10 (6개월) 중 개발기간: 2023.10 (**2주**)
- 개발 언어 및 기술: C++ & ROS
- 팀 규모: 5인 1팀 *(개발 1인 1팀)*
- 개발 환경
  - Raspberrypi4B
  - Ubuntu 20.04
  - ROS noetic
- HW 구성
  - 아두이노 UNO (ECU 역할)
  - 리니어 모터, 구동 모터
  - 초음파 센서
  - IMU (MPU 6050)
  - 적외선 센서
  - 타코미터 (모터 엔코더)
  - 모터 드라이버 (L298n)

### 팀원 구성
|김현우|송근호|정석권|백호용|한승헌|
|:---:|:---:|:---:|:---:|:---:|
|![image](https://github.com/HarrysK99/Climbing-AV/assets/81846798/854e934d-51e9-49e6-a3a8-07890be511d7)|![image](https://github.com/HarrysK99/Climbing-AV/assets/81846798/b56516ea-5759-4fa2-bc6b-9cc398810f8c)|![image](https://github.com/HarrysK99/Climbing-AV/assets/81846798/3004f31a-2e94-4d12-85f2-0a1cae14699a)|![image](https://github.com/HarrysK99/Climbing-AV/assets/81846798/5f55221d-bbac-48c7-9d4b-8cb49804f99c)|![image](https://github.com/HarrysK99/Climbing-AV/assets/81846798/5ef86061-ba47-42b7-8d65-c5ac1bd0db72)|
|**센서 선정**|동역학 분석|팀장(재무, 행정)|재료/규격 선정|기계매커니즘 제작|
|**회로 제작**|전력 및 에너지 분석|재료역학 분석|동/재료역학 및 진동 분석|전장 및 배선|
|**자율주행 알고리즘 구현**|구동부 설계/조립|바디 설계/조립|INVENTOR 3D 모델링|바디 설계 및 조립|
|**컴퓨터 제어**|전장 및 배선|구동부 조립|구동부 설계/조립|구동부 조립|

### 수상
- 🥈**우수상** - 2023 한양대 컨소시엄 창의적 종합설계 경진대회
- 🥉**장려상** - 2023 건국대 제15회 창의설계경진대회
- 🏅**인기상** - 2023 건국대 제15회 창의설계경진대회

<br>

## 구현 기능

### 시스템 구성

<img src="https://github.com/HarrysK99/Climbing-AV/assets/81846798/5b33de75-c138-4fa5-9202-35c80aa5ba83" width="500" height="400"> <img src="https://github.com/HarrysK99/Climbing-AV/assets/81846798/51d135c8-ac69-4d7a-a287-c3446e49bfdb" width="500" height="400">
- **IMU**: 각변위, 각속도 측정, 바디 또는 각 캐터필러의 현재 기울기를 파악함.
- **초음파 센서**: 센서와 물체가 이격되어 있는 거리 측정, 계단 각도 구하기 위해 사용.
- **적외선 센서**: 일정 거리 안쪽에 물체가 있으면 신호를 주고 그렇지 않으면 신호를 보내지 않음. 전륜과 후륜의 타코미터 역할 및 전륜 캐터필러와 계단이 닿아있는지 확인할 때 사용.
<br>

### 구현
### 1. 계단 진입 전

![image](https://github.com/HarrysK99/Climbing-AV/assets/81846798/253e4c03-92ee-40ae-9169-881005b7d4ec)

본체가 계단에 가까워지면 전면의 초음파 센서가 계단의 경사를 측정하는데, 그 메커니즘은 다음과 같다. 

![image](https://github.com/HarrysK99/Climbing-AV/assets/81846798/495605af-5f04-406a-98c1-7e5ac1845c7c)

초음파 센서의 음파가 방사되는 것과 계단이 꺾이는 지점에서 초음파 센서가 송신해주는 값이 미분 불가능이 되는 것을 이용해 바디가 앞으로 이동하며 두 번의 미분 불가능이 되는 지점을 각각 측정하면 계단의 단높이와 단너비를 알 수 있다.
<br/>
각도를 측정한 후 전륜 캐터필러의 각도를 리니어 모터를 활용해 계단 각도에 맞게 세팅한다. 이때 전륜 IMU 센서를 활용해 전륜의 각도를 확인한다.

### 2. 계단 진입

![image](https://github.com/HarrysK99/Climbing-AV/assets/81846798/2b29ac05-ecad-4933-8185-f5ee26365ac4)

초음파 센서 하단에 부착된 적외선 센서를 활용해 계단에 전륜 캐터필러가 닿아 있는지 확인한다.<br/>
전륜 캐터필러와 적외선 센서가 닿아있는 것이 확인되면 바퀴를 구동하여 위로 올라가면서
전륜, 후륜, 바디 IMU 센서를 활용해 세 요소와 계단과의 상대적 기울기를 확인해
전륜 캐터필러의 리니어 모터를 서서히 줄여가며 (전륜의 각도를 서서히 줄여가며)
다음 사진과 같이 바디와 계단, 전륜과 후륜 캐터필러가 평행을 이루게끔 만든다.

![image](https://github.com/HarrysK99/Climbing-AV/assets/81846798/ad89937d-0e06-48b9-b907-08f4aecfa25b)

이후 계단 탈출 시까지 주행한다.

### 3. 계단 탈출

![image](https://github.com/HarrysK99/Climbing-AV/assets/81846798/f09d4de8-5983-43e0-a147-4907c679517a)

탈출 상황 인지를 위해 앞서 언급한 초음파 센서 아래의 적외선 센서를 활용한다.<br/>
계단과 전륜이 닿아 있어 일정 거리 이내일 때는 신호를 보내주고, 일정 거리 이상 떨어지면
신호를 보내지 않는 것을 활용해 전륜 캐터필러가 계단 위로 어느 정도 올라와 다음과 같이
탈출 해야할 상황이 되면
(무게중심이 뒤쪽에 있어 계단 탈출 상황에서 전륜은 필연적으로 공중에 떠있게 된다.)

![image](https://github.com/HarrysK99/Climbing-AV/assets/81846798/64469770-e3a3-4853-b23d-d8f7729ae130)

후륜 캐터필러의 리니어 모터를 늘려서 (후륜의 각도를 크게 해서) 전륜이 쿵 하고 떨어지는 것을 방지하고,

![image](https://github.com/HarrysK99/Climbing-AV/assets/81846798/417c7cfd-8f1b-4e96-b956-d51e67bca41a)

위와 같이 네개의 캐터필러가 안정적으로 바닥에 접촉한 채 올라오는 것을 마무리하도록
세개의 IMU 센서를 활용해 점차적으로 후륜 리니어모터를 줄여준다.

<br>

## 보완할 점
- [ ] 장애물이 존재하는 시나리오도 추가하기 (현재: ***No Obstacle*** Condition)
- [ ] 적정 하중을 이겨낼 수 있는 모터로 교체 (현재: ***No Driver*** Condition)
- [ ] 강화학습 적용해보기

</p>

<br>

## 라이센스

MIT &copy; [NoHack](mailto:lbjp114@gmail.com)
