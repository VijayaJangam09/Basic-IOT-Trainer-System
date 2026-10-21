#define POT 15

void setup() {
  // put your setup code here, to run once:
  pinMode(POT,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val=analogRead(POT);
  Serial.print("Value = ");
  Serial.println(val);
  delay(1000);
}
