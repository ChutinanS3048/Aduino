

const int buttonPin0 = 2;    // button for change the mode
const int buttonPin1 = 3;    // button for turn on - off

const int ledPin = 13;       // the pin for RGB lamp


// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonMode = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin0, INPUT);
  // initialize putton the RGB mode :

   pinMode(buttonPin1, INPUT);
  // initialize putton turn on amd turn off :

  
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  buttonMode = digitalRead(buttonPin0);


  // compare the buttonState to its previous state
  if (buttonMode != lastButtonState) {
    // if the state has changed, increment the counter

      

    if (buttonMode == HIGH) {
      // if the current state is HIGH then the button went from off to on:

      buttonPushCounter++;
    
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);

      switch (buttonPushCounter) {
        case 4 :
          mode4 ();
          break;
        case 3 :
          mode3 ();
          break;
        case 2 :
          mode2 ();
          break;
        case 1 :
          mode1 ();
          break;
      }

    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonMode;

  if (buttonPushCounter > 3) {
    buttonPushCounter = 0;
  }

}

int mode1 ()
{
  Serial.println("Yello");
}

int mode2 ()
{
  Serial.println("Red");
}

int mode3 ()
{
  Serial.println("switch light");
}

int mode4 ()
{
  Serial.println("White");
}
