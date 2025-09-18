#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Hatdog";
const char* password = "11111111";

const int led1Pin = 13;  // GPIO13 for LED1
const int led2Pin = 14;  // GPIO14 for LED2
bool led1State = false;
bool led2State = false;  

WebServer server(80);

void handleRoot() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>ESP32 Dual LED Control</title>
    <style>
      body {
        font-family: Arial, sans-serif;
        background: #f2f2f2;
        text-align: center;
        margin: 0;
        padding: 0;
      }
      h1 {
        background: #00796B;
        color: white;
        padding: 20px;
        margin: 0 0 20px 0;
      }
      p {
        font-size: 1.2em;
        color: #333;
      }
      button {
        padding: 15px 30px;
        margin: 10px;
        font-size: 1.1em;
        border: none;
        border-radius: 10px;
        cursor: pointer;
        background: #00796B;
        color: white;
        transition: 0.3s;
      }
      button:hover {
        background: #004D40;
      }
      .led-container {
        display: inline-block;
        background: white;
        border-radius: 15px;
        padding: 20px;
        margin: 15px;
        box-shadow: 0px 4px 8px rgba(0,0,0,0.1);
      }
    </style>
  </head>
  <body>
    <h1>ESP32 Dual LED Control</h1>

    <div class="led-container">
      <p>LED1 is %LED1%</p>
      <form action="/toggle1" method="POST">
        <button type="submit">Toggle LED1</button>
      </form>
    </div>

    <div class="led-container">
      <p>LED2 is %LED2%</p>
      <form action="/toggle2" method="POST">
        <button type="submit">Toggle LED2</button>
      </form>
    </div>
  </body>
  </html>
  )rawliteral";

  // Replace placeholders with actual states
  html.replace("%LED1%", (led1State ? "ON" : "OFF"));
  html.replace("%LED2%", (led2State ? "ON" : "OFF"));

  server.send(200, "text/html", html);
}

void handleToggle1() {
  led1State = !led1State;
  digitalWrite(led1Pin, led1State ? HIGH : LOW);
  server.sendHeader("Location", "/");
  server.send(303);  // Redirect to root
}

void handleToggle2() {
  led2State = !led2State;
  digitalWrite(led2Pin, led2State ? HIGH : LOW);
  server.sendHeader("Location", "/");
  server.send(303);  // Redirect to root
}

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/toggle1", HTTP_POST, handleToggle1);
  server.on("/toggle2", HTTP_POST, handleToggle2);
  server.begin();
}

void loop() {
  server.handleClient();
}