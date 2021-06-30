
#include <Servo.h>

Servo myservo_1, myservo_2;

int servo_1_pin = D1;
int servo_2_pin = D2;

void setup() {
  Serial.begin(9600);
  myservo_1.attach(servo_1_pin);
  myservo_2.attach(servo_2_pin);

  myservo_1.write(0);
  myservo_2.write(0);
}

void loop() {

  myservo_1.attach(servo_1_pin);
  delay(15);
  myservo_1.write(0);
  delay (1000);
  myservo_1.detach();
  delay(2000);

  myservo_1.attach(servo_1_pin);
  delay(15);
  myservo_1.write(90);
  delay (1000);
  myservo_1.detach();
  delay(2000);

  myservo_1.attach(servo_1_pin);
  delay(15);
  myservo_1.write(180);
  delay (1000);
  myservo_1.detach();
  delay(2000);

}
