const int enB = 5; // Enable pin for Motor A
const int in3 = 6; // Input 1 for Motor A
const int in4 = 7; // Input 2 for Motor A

void setUpForward()
{
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void setDownForward()
{
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void StopLinear()
{
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void setUpLinear()
{
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  setUpForward();
}

void AccelLinear(char pwm)
{
  analogWrite(enB, pwm);
}
