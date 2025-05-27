#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include "DHT.h"

// WiFi credentials
#define WIFI_SSID "Jio1"
#define WIFI_PASSWORD "tlm75#2@xq"

// Firebase credentials
#define FIREBASE_HOST "sensormonitor-27136-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "1En5qGorFIyVjafEVp8E0EzFL6OEhwzLSgrbr"

// DHT setup
#define DHTPIN 2  // GPIO2 (D4)
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Firebase setup objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);

  // Connect WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");

  // Configure Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int phValue = analogRead(A0); // raw PH value

  Serial.printf("Temp: %.2f C, Hum: %.2f %%, PH: %d\n", temperature, humidity, phValue);

  Firebase.setFloat(fbdo, "/temperature", temperature);
  Firebase.setFloat(fbdo, "/humidity", humidity);
  Firebase.setInt(fbdo, "/ph", phValue);

  delay(5000); // update every 5 seconds
}
