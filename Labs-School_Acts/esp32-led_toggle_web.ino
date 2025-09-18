#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ssid";
const char* password = "password";

const int ledPin = 5;  // GPIO5 for LED
bool ledState = false;

WebServer server(80);

void handleRoot() {
  String html = "<html><body><h1>ESP32 LED Control</h1>";
  html += "<p>LED is " + String(ledState ? "ON" : "OFF") + "</p>";
  html += "<form action=\"/toggle\" method=\"POST\">";
  html += "<button type=\"submit\">Toggle LED</button></form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleToggle() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState ? HIGH : LOW);
  server.sendHeader("Location", "/");
  server.send(303);  // Redirect to root
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/toggle", HTTP_POST, handleToggle);
  server.begin();
}

void loop() {
  server.handleClient();
}
