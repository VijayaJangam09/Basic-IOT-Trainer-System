

#include <Ultrasonic.h>

Ultrasonic ultrasonic(12, 13); // Trig Pin - 12, Echo Pin - 13
int distance;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Pass INC as a parameter to get the distance in inches
  distance = ultrasonic.read();
  
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  delay(1000);
}
