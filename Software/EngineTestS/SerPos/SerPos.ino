#include <Servo.h>

Servo servo;
int position;

void setup() {
  digitalWrite(13,HIGH);
  servo.attach(9);
}

void loop() {
  for(position = 0; position < 180; position++) { 
    servo.write(position); //Schreiben des aktuellen Wertes der Variable 'position' (1...180)
    delay(50); //Pause
  } 

  delay(1000);
  servo.write(0);
  delay(1000);
  servo.write(180);
  delay(1000);

  for(position = 180; position >0; position--){
    servo.write(position);
    delay(50);
  }
}
