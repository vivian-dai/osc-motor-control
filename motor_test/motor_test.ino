#include <ESP32Servo.h>
#include <WiFi.h>

#include <env.h>

#define L_SERVO_PIN 23
#define R_SERVO_PIN 22

#define PORT 53000 // change later to default port

Servo l_servo;
Servo r_servo;
NetworkServer server(PORT);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  l_servo.attach(L_SERVO_PIN);
  r_servo.attach(R_SERVO_PIN);

  delay(10);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("address:");
  Serial.println(WiFi.localIP() + ":" + PORT);

  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  // servo.write(0);
  // delay(1000);
  // servo.write(180);
  // delay(1000);

  // Serial.println("ok");
  // for(int i = 0;i <= 180;i++) {
  //   servo.write(i);
  //   delay(15);
  // }
  // for(int i = 180;i >= 0;i--) {
  //   servo.write(i);
  //   delay(15);
  // }

  NetworkClient client = server.accept();
  if(client) {
    String cur_line = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        cur_line += c;
        if(c == '\n') {
          Serial.println(cur_line);
          // based on curline move things
        }
      }
    }
    client.stop();
  }

}
