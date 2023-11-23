int sensor = 3;
int val;
unsigned long lastPulseTime = 0;  // 이전 하강 펄스의 시간
int pulseCount = 0;              // 하강 펄스 수
float rotationTime = 0;          // 회전당 시간 (2개의 하강 펄스 간격)
float rps = 0;                   // 초당 회전수

void initEncoder()
{
  pinMode(sensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensor), pulseCounter, FALLING);  // 인터럽트 설정
}

float& getRPS()
{
  return rps;
}

void pulseCounter() {
  // 적외선 센서에서 하강 펄스를 감지할 때 호출됩니다.
  unsigned long currentTime = millis();  // 현재 시간을 가져옵니다.
  float pulseInterval = (currentTime - lastPulseTime) / 1000.0;  // 두 하강 펄스 간의 시간 간격 (초 단위)를 계산합니다.
  lastPulseTime = currentTime;  // 이전 하강 펄스의 시간을 업데이트합니다.
  pulseCount++;  // 하강 펄스 수를 증가시킵니다.

  // 2개의 하강 펄스 간격을 사용하여 회전당 시간을 계산하고, 초당 회전수를 업데이트합니다.
  if (pulseInterval > 0) {
    rotationTime = pulseInterval * 2;  // 회전당 시간을 계산합니다.
    rps = 1 / rotationTime;  // 초당 회전수를 계산합니다.
  }
}
