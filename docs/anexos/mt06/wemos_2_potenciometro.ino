#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "test";
const char* password = "test123";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

const int potPin = A0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi conectado");
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("WemosA")) {
      Serial.println("Conectado al broker");
    } else {
      delay(2000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int potValue = analogRead(potPin);
  int grados = map(potValue, 0, 1023, 0, 180);

  char msg[10];
  sprintf(msg, "%d", grados);
  client.publish("grados_mqtt", msg);

  Serial.print("Publicado: ");
  Serial.println(grados);

  delay(500);
}