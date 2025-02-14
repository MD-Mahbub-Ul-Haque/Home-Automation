
#define BLYNK_TEMPLATE_ID "TMPL6fyeTZK52"
#define BLYNK_TEMPLATE_NAME "Home Auto"
#define BLYNK_AUTH_TOKEN "QKon8T2QQyQhOa8u5-6CxL0VKvEfAoYM"


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>  // Include the Adafruit sensor dependency for DHT

// Relay and Sensor Pin Definitions
#define RELAY1 25
#define RELAY2 26
#define RELAY3 27
#define RELAY4 14
#define MQ2_PIN 34   // Analog input for MQ2 gas sensor
#define BUZZER 12    // Digital pin for buzzer
#define DHTPIN 4     // Digital pin for DHT11 sensor
#define DHTTYPE DHT11

char ssid[] = "Wi-Fi SSID";         // Wi-Fi SSID
char pass[] = "Wi-Fi Password";     // Wi-Fi Password

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
 

  WiFi.begin(ssid, pass);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);
  digitalWrite(BUZZER, LOW);

  dht.begin();
}

void loop() {
  checkGasSensor();
  readDHTSensor();
  Blynk.run();

  checkWiFiConnection();

  delay(2000);
}

// Read Gas Sensor and Handle Alarm
// Replace Blynk.notify() with Blynk.logEvent()
void checkGasSensor() {
  int gasValue = analogRead(MQ2_PIN);
  if (gasValue > 600) {
    digitalWrite(BUZZER, HIGH);  // Turn on buzzer
    Blynk.logEvent("gas_alert", "Gas/Smoke detected! Please check immediately.");
    Blynk.virtualWrite(V7, 1);  // Virtual pin for sound/alarm widget
  } else {
    digitalWrite(BUZZER, LOW);  // Turn off buzzer
    Blynk.virtualWrite(V7, 0);
  }
}


// Read Temperature and Humidity from DHT11
void readDHTSensor() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  
  if (!isnan(temp) && !isnan(hum)) {
    Blynk.virtualWrite(V5, temp);  // Temperature to Virtual Pin V5
    Blynk.virtualWrite(V6, hum);   // Humidity to Virtual Pin V6
  }
}

// Blynk virtual pin handlers for relay control
BLYNK_WRITE(V1) {
  digitalWrite(RELAY1, param.asInt() ? LOW : HIGH);
}

BLYNK_WRITE(V2) {
  digitalWrite(RELAY2, param.asInt() ? LOW : HIGH);
}

BLYNK_WRITE(V3) {
  digitalWrite(RELAY3, param.asInt() ? LOW : HIGH);
}

BLYNK_WRITE(V4) {
  digitalWrite(RELAY4, param.asInt() ? LOW : HIGH);
}

void checkWiFiConnection() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi is connected.");
  } else {
    Serial.println("Wi-Fi is disconnected! Reconnecting...");
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nReconnected to Wi-Fi.");
  }
}
