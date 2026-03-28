#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "xxxx";
const char* password = "xxxxx";

ESP8266WebServer server(80);

#define RELAY1 D1
#define RELAY2 D2

bool estado1 = false;
bool estado2 = false;

// HTML PRO
String pagina() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>EFDI - MT07 - Control de Lámparas</title>

<style>
  body {
    font-family: Arial;
    text-align: center;
    background: #f0f2f5;
  }

  h1 {
    margin-top: 20px;
  }

  .container {
    display: flex;
    flex-direction: column;
    align-items: center;
  }

  .card {
    background: white;
    padding: 20px;
    margin: 15px;
    width: 250px;
    border-radius: 12px;
    box-shadow: 0 4px 10px rgba(0,0,0,0.1);
  }

  .estado {
    font-size: 18px;
    margin: 10px;
    font-weight: bold;
  }

  .on { color: green; }
  .off { color: red; }

  button {
    padding: 12px 20px;
    font-size: 16px;
    border: none;
    border-radius: 8px;
    cursor: pointer;
    background-color: #007BFF;
    color: white;
  }

</style>
</head>

<body>

<h1>EFDI - MT07 - Control de Lámparas</h1>

<div class="container">

  <div class="card">
    <h2>Lámpara 1</h2>
    <div id="estado1" class="estado">...</div>
    <button onclick="toggle(1)">Cambiar estado</button>
  </div>

  <div class="card">
    <h2>Lámpara 2</h2>
    <div id="estado2" class="estado">...</div>
    <button onclick="toggle(2)">Cambiar estado</button>
  </div>

</div>

<script>
function toggle(id) {
  fetch('/toggle' + id);
}

function actualizar() {
  fetch('/estado')
    .then(r => r.json())
    .then(data => {

      let e1 = document.getElementById('estado1');
      let e2 = document.getElementById('estado2');

      e1.innerHTML = data.r1 ? "Encendido " : "Apagado";
      e1.className = "estado " + (data.r1 ? "on" : "off");

      e2.innerHTML = data.r2 ? "Encendido " : "Apagado";
      e2.className = "estado " + (data.r2 ? "on" : "off");
    });
}

setInterval(actualizar, 1000);
actualizar();
</script>

</body>
</html>
)rawliteral";

  return html;
}

// --- HANDLERS ---

void handleRoot() {
  server.send(200, "text/html", pagina());
}

void toggle1() {
  estado1 = !estado1;
  digitalWrite(RELAY1, estado1 ? HIGH : LOW);
  server.send(200, "text/plain", "OK");
}

void toggle2() {
  estado2 = !estado2;
  digitalWrite(RELAY2, estado2 ? HIGH : LOW);
  server.send(200, "text/plain", "OK");
}

void handleEstado() {
  String json = "{";
  json += "\"r1\":" + String(estado1 ? "true" : "false") + ",";
  json += "\"r2\":" + String(estado2 ? "true" : "false");
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.on("/toggle1", toggle1);
  server.on("/toggle2", toggle2);

  server.on("/estado", handleEstado);

  server.begin();
}

void loop() {
  server.handleClient();
}