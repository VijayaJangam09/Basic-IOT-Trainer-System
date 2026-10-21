#define MQ135 15

void setup() {
  // put your setup code here, to run once:
  pinMode(MQ135,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val=analogRead(MQ135);
  Serial.print("Gas Value = ");
  Serial.println(val);
  delay(1000);
}
