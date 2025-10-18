#include <ESP32Servo.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include <env.h>

#define L_SERVO_PIN 23
#define R_SERVO_PIN 22

#define PORT 53000 // change later to default port

Servo l_servo;
Servo r_servo;
WiFiUDP udp_server;

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

  // WiFi.mode(WIFI_AP);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println(WiFi.localIP());

  udp_server.begin(PORT);
}

void loop() {
  int sz = udp_server.parsePacket();
  if(sz > 0) {
    Serial.println(sz);
    String packet = "";
    while(sz > 0) {
      char c = udp_server.read();
      packet += c;
      sz--;
    }
    Serial.println(packet);
    if(packet.startsWith("/left")) {
      int degree = packet.substring(5).toInt();
      if(degree >= 0 && degree <= 180) {
        l_servo.write(degree);
      }

    } else if(packet.startsWith("/right")) {
      int degree = packet.substring(6).toInt();
      if(degree >= 0 && degree <= 180) {
        r_servo.write(degree);
      }
    }
  }
}
