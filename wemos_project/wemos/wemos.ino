#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "base64.h"

// Setup WiFi network
const char* ssid = "Sanzu";
const char* password = "menjadimesin";

// setup pin sensor and speaker buzzer
const int sensorPin = A0;
int speakerPin = D5;
int state = 0;

void setup() {
  Serial.begin(9600);
  // wifi auth check
  WiFi.begin(ssid, password);
  
  // setup pin mode 
  pinMode(sensorPin,INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(successPin, OUTPUT);
  pinMode(errorPin, OUTPUT);
  
  // check wifi authenticate
  // jika wifi autentikasi gagal
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // jika autentikasi berhasil
  Serial.println("Connected to WiFi");
}
 
void loop() {
state = analogRead(sensorPin);
Serial.println(state);

  if(state < 500) {
      
      if ((WiFi.status() == WL_CONNECTED)) { 

        WiFiClient client;
        HTTPClient http;
    
        String link = "http://www.agilamanesu/api/sender";
  
        http.begin(client, link);
        int httpCode = http.GET();
        Serial.println("ini http Code");
        Serial.println(httpCode);
        
        if (httpCode > 0) { 
            String payload = http.getString();
            Serial.println(link);
            Serial.println(httpCode);
            Serial.println(payload);
        }
        else {
            Serial.println("Error on HTTP request");
        }
        http.end();
        
      }

      digitalWrite(speakerPin, HIGH);
      delay(3000);
      digitalWrite(speakerPin, LOW);
      delay(1000);
      }
  
  delay(200);
 
}