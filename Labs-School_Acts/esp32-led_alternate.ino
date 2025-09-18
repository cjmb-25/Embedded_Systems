const int led1 = 13;
const int led2 = 14;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop()
{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  delay(500);

  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(500);
}