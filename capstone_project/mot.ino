const int enA = 11; // Enable pin for Motor A
const int in1 = 12; // Input 1 for Motor A
const int in2 = 13; // Input 2 for Motor A

void setForward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void setBackward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void setStop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void setupAcc()
{
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  setForward();
}

void Accel(char pwm)
{
  analogWrite(enA, pwm);
}
