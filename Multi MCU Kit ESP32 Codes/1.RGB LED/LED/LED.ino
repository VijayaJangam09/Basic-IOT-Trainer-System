#define R 5
#define G 16
#define B 17

void setup() {
// initialize digital pin LED_BUILTIN as an output.
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}
// the loop function runs repeatedly forever
void loop() {
  digitalWrite(R, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(2000); // wait for a second
  digitalWrite(R, LOW); // turn the LED off by making the voltage LOW
  delay(2000); // wait for a second

  digitalWrite(G, HIGH);
  delay(2000); 
  digitalWrite(G, LOW); 
  delay(2000);

  digitalWrite(B, HIGH); 
  delay(2000); 
  digitalWrite(B, LOW); 
  delay(2000);
}
