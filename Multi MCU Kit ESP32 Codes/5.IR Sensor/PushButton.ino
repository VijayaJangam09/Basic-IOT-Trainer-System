
int pushButton = 15;//Touch Snsor Signal Pin,  IR Signal Pin
int led = 2; // Led Pin
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(led,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  if (buttonState==1){
    digitalWrite(led,HIGH);
  }
  else {
    digitalWrite(led,LOW);
  }
  // print out the state of the button:
  Serial.println(buttonState);
  delay(1000);  // delay in between reads for stability
}
