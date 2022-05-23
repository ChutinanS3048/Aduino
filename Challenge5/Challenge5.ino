#define MDC_EN 3 // Pin D3 connects to EN signal from DC motor circuit board
#define MDC_IN1 51 // Pin D51 connects to IN1 signal from DC motor circuit board
#define MDC_IN2 52 // Pin D52 connects to IN2 signal from DC motor circuit board
#define MDC_OPA 2 // Pin D2 (int.0) connects to OPA signal from DC motor circuit board
#define left 1 // a variable to indicate left direction
#define right 2 // a variable to indicate right direction


int mdc_target_speed = 50;         // DC motor speed: 0=stop, 255=max speed
volatile unsigned long pulses_counted = 0;   // store number of pulses being counted (32bit). The pulses are
                                    // from the OPA signal from DC motor circuit board 
volatile int mdc_estimated_speed = 0;  // The estimated speed by the software

void setup()
{
  pinMode(MDC_EN, OUTPUT); // set pin as output
  pinMode(MDC_IN1, OUTPUT); // set pin as output
  pinMode(MDC_IN2, OUTPUT); // set pin as output

  
  attachInterrupt(0, ISR_OPA, RISING); // Attach interrupt function "ISR_OPA" to the OPA signal
                                     // connected to pin D2 (int.0) 
  // setup timer 1
  noInterrupts(); // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;  
  TCNT1  = 0; // reset the timer/counter value

  OCR1A = 62500; // set the compare match register value (16MHz/256/1Hz)
  TCCR1B |= (1 << WGM12); // set timer to CTC mode
  TCCR1B |= (1 << CS12); // use 256 prescaler 
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  interrupts(); // enable all interrupts

  Serial.begin(9600); // Sets up communication with the serial monitor
}

ISR(TIMER1_COMPA_vect) // timer compare ISR
{
  mdc_estimated_speed = pulses_counted*30;  // speed (round per minutes) is equal to 
                                         // number of pulses counted per second*30 
                                         // (we received 2 pulses per one rotation)
  pulses_counted = 0;  // reset pulses_counted variable for the next round
}

//ISR_OPA
void ISR_OPA()
{
  pulses_counted++; // increase the count variable
}

// A function that set motor direction
void setMotorDir(byte dir)
{
  if(dir==left)
  {
    // set IN1 and IN2 to rotate motor to the left
    digitalWrite(MDC_IN1, 0);
    digitalWrite(MDC_IN2, 1);
  }
  else if(dir==right)
  {
    // set IN1 and IN2 to rotate motor to the right    
    digitalWrite(MDC_IN1, 1);
    digitalWrite(MDC_IN2, 0);
  }
}


void loop()
{
  // set motor speed according to the user input from serial monitor
  if (Serial.available()>0) // if some information is available from serial connection
  {
    mdc_target_speed  = Serial.parseInt();
    Serial.print("Set DC motor speed to ");
    Serial.print(mdc_target_speed);
    Serial.print("\n");
  }

  // Generate signal to drive a DC motor at desired speed
  setMotorDir(right);    
  analogWrite(MDC_EN, mdc_target_speed);

  //analogWrite function

  Serial.print("Estimated speed =");
  Serial.print(mdc_estimated_speed);
  Serial.print(" rpm\n");
}
