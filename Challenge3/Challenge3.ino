int ledpin = 11;

void setup()
{
    Serial.begin(9600);
    pinMode(ledpin, OUTPUT);
    digitalWrite(ledpin, HIGH);
}

void loop()
{
    Serial.println("Please input 1 to turn on the LED || OR || 0 to turn off the LED!");
   if (Serial.available())
    {
        String val = Serial.readString();
        if (val == "0"){
           digitalWrite(ledpin, HIGH);
            Serial.println("OFF");
            
        }
           
        else if (val == "1"){
          digitalWrite(ledpin, LOW);
          Serial.println("ON");
           
        }
            
    }
    delay(1000);
}
