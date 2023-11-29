#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "INFINITUM2060";  // Cambia esto con el nombre de tu red WiFi
const char *password = "Chispaxd10";  // Cambia esto con la clave de tu red WiFi

ESP8266WebServer server(80);

// Pin donde está conectado el LED en la placa (GPIO 2 para el LED integrado)
const int ledPin = 2;

void setup() {
  Serial.begin(9600);

  // Conéctate a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado a la red WiFi");

  // Imprime información en el Monitor Serie
  Serial.println("Información de la conexión:");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Red: ");
  Serial.println(WiFi.SSID());

  // Configura las rutas del servidor
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/plain", "¡Hola desde ESP8266!");
  });

  server.on("/encender", HTTP_GET, []() {
    analogWrite(ledPin, 0);  // Enciende el LED al 100%
    server.send(200, "text/plain", "LED encendido");
  });

  server.on("/apagar", HTTP_GET, []() {
    analogWrite(ledPin, 1023);  // Apaga el LED al 0%
    server.send(200, "text/plain", "LED apagado");
  });

  server.on("/info", HTTP_GET, []() {
    String info = "IP: " + WiFi.localIP().toString() + "\n";
    info += "Red: " + WiFi.SSID() + "\n";
    server.send(200, "text/plain", info);
  });

  // Inicia el servidor
  server.begin();
}

void loop() {
  // Maneja las solicitudes del servidor
  server.handleClient();
}