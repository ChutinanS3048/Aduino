int val = 0;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
  {
    val = Serial.available();
    analogWrite(13, val);
    Serial.println(val);

  }

}
