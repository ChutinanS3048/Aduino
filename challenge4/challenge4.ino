// Manual servo control - PWM Sweeping
// Copyright 2012 by Zipwhip.
// Modified July 2013 by LinuxCircle.com team
// You are free to use and modify this code in your own software.
// Please give us credit to by mentioning LinuxCircle.com
// in the header of your published code.

#define SERVO_PIN         11  // Any pin on the Arduino or Gertboard will work.
int val = 0;

void setup()
{
  pinMode(SERVO_PIN, OUTPUT);
  Serial.begin(9600);
}

int lenMicroSecondsOfPeriod = 25 * 1000; // 25 milliseconds (ms)
int lenMicroSecondsOfPulse = 1 * 1000; // 1 ms is 0 degrees
int first = 0.7 * 1000; //0.5ms is 0 degrees in HS-422 servo =700



int increment = 0.01 * 1000; //10

void loop()
{

  if (Serial.available() > 0)
  {

    val = Serial.available();
    analogWrite(13, val);
    Serial.println(val);

    }

    int end = val * 1000; // 3700

    int current = 0;

    

    for (current = first; current < end; current += increment) {
      // Servos work by sending a 25 ms pulse.
      // 0.7 ms at the start of the pulse will turn the servo to the 0 degree position
      // 2.2 ms at the start of the pulse will turn the servo to the 90 degree position
      // 3.7 ms at the start of the pulse will turn the servo to the 180 degree position
      // Turn voltage high to start the period and pulse
      digitalWrite(SERVO_PIN, HIGH);

      // Delay for the length of the pulse
      delayMicroseconds(current);

      // Turn the voltage low for the remainder of the pulse
      digitalWrite(SERVO_PIN, LOW);

      // Delay this loop for the remainder of the period so we don't
      // send the next signal too soon or too late
      delayMicroseconds(lenMicroSecondsOfPeriod - current);
    }

    for (current = end; current > first; current -= increment) {
      // Servos work by sending a 20 ms pulse.
      // 0.7 ms at the start of the pulse will turn the servo to the 0 degree position
      // 2.2 ms at the start of the pulse will turn the servo to the 90 degree position
      // 3.7 ms at the start of the pulse will turn the servo to the 180 degree position
      // Turn voltage high to start the period and pulse
      digitalWrite(SERVO_PIN, HIGH);

      // Delay for the length of the pulse
      delayMicroseconds(current);

      // Turn the voltage low for the remainder of the pulse
      digitalWrite(SERVO_PIN, LOW);

      // Delay this loop for the remainder of the period so we don't
      // send the next signal too soon or too late
      delayMicroseconds(lenMicroSecondsOfPeriod - current);
    }
  


}
