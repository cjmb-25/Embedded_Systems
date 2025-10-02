#include <WiFi.h>
#include <FirebaseESP32.h>

// Replace with your network credentials
#define WIFI_SSID "xxx"
#define WIFI_PASSWORD "xxx"

// Replace with your Firebase project credentials
#define API_KEY "xxx"
#define DATABASE_URL "xxx" 

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Ultrasonic pins
#define TRIG_PIN 19
#define ECHO_PIN 18

long duration;
float distance;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");

  // Firebase setup
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Anonymous sign-up (requires Anonymous Auth enabled in Firebase Console)
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase sign-up OK");
  } else {
    Serial.printf("Sign-up failed: %s\n",
                  config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  // Trigger ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // cm

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send to Firebase
  if (Firebase.setFloat(fbdo, "/distance", distance)) {
    Serial.println("Data sent to Firebase");
  } else {
    Serial.println("Failed to send: " + fbdo.errorReason());
  }

  // Read back from Firebase
  if (Firebase.getFloat(fbdo, "/distance")) {
    Serial.print("Data from Firebase: ");
    Serial.println(fbdo.floatData());
  } else {
    Serial.println("Failed to read: " + fbdo.errorReason());
  }

  delay(2000);
}
