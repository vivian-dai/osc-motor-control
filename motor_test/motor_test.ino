#include <ESP32Servo.h>

#define SERVO_PIN 23

Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  servo.attach(SERVO_PIN);

}

void loop() {
  // put your main code here, to run repeatedly:
  // servo.write(0);
  // delay(1000);
  // servo.write(180);
  // delay(1000);
  Serial.println("ok");
  for(int i = 0;i <= 180;i++) {
    servo.write(i);
    delay(15);
  }
  for(int i = 180;i >= 0;i--) {
    servo.write(i);
    delay(15);
  }

}
