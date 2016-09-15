#include "MQTT/MQTT.h"

int led = D2;
String TOKEN = "W0KmbwPs4qcEqPfb1FXL9m0Ke6VycZdwL6Z-DkD1y_g"; //"YOUR TOKEN";
String TOPIC = "v2/things/"+TOKEN;
String WIFI_SSID = "Wifi-ssid";
String WIFI_PASSWORD = "Wifi-passw";

void callback(char* topic, byte* payload, unsigned int length) {
    // handle message arrived
    String text = "";
    for (int i = 0; i < length; i++)
        text.concat((char)payload[i]);
    Particle.publish(text);
    text.replace(" ", "");
    if (text.indexOf("\"key\":\"blink\"") >= 0) {
        if (text.indexOf("\"value\":\"1\"") >= 0) {
          digitalWrite(led, HIGH);
          delay(500);
          digitalWrite(led, LOW);
          delay(500);
          digitalWrite(led, HIGH);
          delay(500);
          digitalWrite(led, LOW);
          delay(500);
          digitalWrite(led, HIGH);
          delay(500);
          digitalWrite(led, LOW);
        }
    }
}

MQTT client("mqtt.thethings.io", 1883, callback);

void setup() {
    pinMode(D1,INPUT_PULLDOWN);
    pinMode(led, OUTPUT);
    digitalWrite(D1, LOW);
    WiFi.on();
    WiFi.setCredentials(WIFI_SSID, WIFI_PASSWORD); 
    while(!WiFi.ready()) {
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected ssid");
    while (!client.connect("photonclient")) {
        Serial.println("Could not subscribe, retrying...");
    }
    client.subscribe(TOPIC);
}

void loop() {
    if (digitalRead(D1) == HIGH) {
        String message = "{\"values\":[{\"key\":\"buttonPressed\",\"value\":\"1\"}]}";
        client.publish(TOPIC, message);
        delay(200);         // ADDED A LITTLE BIT DELAY TO REDUCE BOUNCES
    }
    if (client.isConnected()) {
        client.loop();
    }
    
}
