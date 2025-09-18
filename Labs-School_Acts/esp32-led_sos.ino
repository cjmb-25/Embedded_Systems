const int led = 5;
const int delay_short = 500;
const int delay_long = 1000;
const int delay_next = 1500;

void setup()
{
  pinMode(led, OUTPUT);
}

void loop()
{
  for (int i = 0; i<3; i++)
  {
    s_morse();
  }
  delay(delay_next);
  for (int i = 0; i<3; i++)
  {
    o_morse();
  }
  delay(delay_next);
  for (int i = 0; i<3; i++)
  {
    s_morse();
  }
  delay(delay_next);
}

void s_morse()
{
  digitalWrite(led, HIGH);
  delay(delay_short);
  digitalWrite(led, LOW);
  delay(delay_short);
}

void o_morse()
{
  digitalWrite(led, HIGH);
  delay(delay_long);
  digitalWrite(led, LOW);
  delay(delay_long);
}