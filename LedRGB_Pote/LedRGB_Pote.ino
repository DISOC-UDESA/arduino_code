#define LED_RGB_R 5 // D1
#define LED_RGB_G 4 // D2
#define LED_RGB_B 0 // D3



void setup() {
  pinMode(LED_RGB_R, OUTPUT);
  pinMode(LED_RGB_G, OUTPUT);
  pinMode(LED_RGB_B, OUTPUT);
}

void loop() {
  int PoteValue = analogRead(A0);
  if (PoteValue <= 341) {
    digitalWrite(LED_RGB_R, LOW);
    digitalWrite(LED_RGB_G, HIGH);
    digitalWrite(LED_RGB_B, HIGH);
  }
  if (PoteValue > 341 && PoteValue <= 682) {
    digitalWrite(LED_RGB_R, HIGH);
    digitalWrite(LED_RGB_G, LOW);
    digitalWrite(LED_RGB_B, HIGH);
  }
  if (PoteValue > 682) {
    digitalWrite(LED_RGB_R, HIGH);
    digitalWrite(LED_RGB_G, HIGH);
    digitalWrite(LED_RGB_B, LOW);
  }
}
