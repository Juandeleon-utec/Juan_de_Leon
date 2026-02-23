#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

const char* ssid = "test"; // Cambiado por seguridad
const char* password = "test123"; // cambiado por seguridad
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
Servo myServo;

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";

  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  int grados = message.toInt();
  grados = constrain(grados, 0, 180);

  myServo.write(grados);

  Serial.print("Grados recibidos: ");
  Serial.println(grados);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("Wemos_Jpdeleon_C")) {
      client.subscribe("grados_mqtt_efdi");
    } else {
      delay(2000);
    }
  }
}




void setup() {
  Serial.begin(115200);
  myServo.attach(D4);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}