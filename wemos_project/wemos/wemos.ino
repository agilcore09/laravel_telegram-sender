#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "base64.h"

// Setup WiFi network
const char* ssid = "Sanzu";
const char* password = "menjadimesin";

// read sensor
const int sensorPin = A0;
int speakerPin = D5;
int errorPin = D6;
int successPin = D1;
int state = 0;

void setup() {
 
  // Serial.begin(115200);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  pinMode(sensorPin,INPUT);
  pinMode(speakerPin, OUTPUT);

  pinMode(successPin, OUTPUT);
  pinMode(errorPin, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
    digitalWrite(errorPin, HIGH);
    delay(300);
    digitalWrite(errorPin, LOW);
    delay(300);
  }

  Serial.println("Connected to WiFi");
}
 
void loop() {
state = analogRead(sensorPin);
Serial.println(state);

  if(state < 500) {
      
      if ((WiFi.status() == WL_CONNECTED)) { 

        WiFiClient client;
        HTTPClient http;
     
        int nilai = random(29,37);
        String data = (String) nilai;
    
        String link = "http://127.0.0.1:8000/api/sender";
      
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
        digitalWrite(successPin, HIGH);
        delay(3000);
        digitalWrite(successPin, LOW);
        delay(1000);

      digitalWrite(speakerPin, HIGH);
      delay(3000);
      digitalWrite(speakerPin, LOW);
      delay(1000);
      }
  
  delay(200);
 
}