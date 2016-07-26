#include "MQTT/MQTT.h"

void callback(char* topic, byte* payload, unsigned int length) {
    // MESSAGE HAS ARRIVED FROM THE THETHINGS.IO
    String text = "";
    for (int i = 0; i < length; i++)
        text.concat((char)payload[i]);
    Serial.println(text);
}

MQTT client("mqtt.thethings.io", 1883, callback);

int a;
String TOKEN = "YOUR TOKEN";
String TOPIC = "v2/things/"+TOKEN;
String WIFI_SSID = "your wifi";
String WIFI_PASSWORD = "your password";

void setup() {
    pinMode(D1,INPUT_PULLDOWN);
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
    client.subscribe(TOPIC);            // SUBSCRIBE TO RECEIVE CHANGED VALUES FROM YOUR RESOURCES
}

void loop() {
    a = random(0,10);
    if (digitalRead(D1) == HIGH) {
        message = "{\"values\":[{\"key\":\"fun\",\"value\":"+String(a, DEC)+"}]}";
        client.publish(TOPIC, message);
        delay(200);         // ADDED A LITTLE BIT DELAY TO REDUCE BOUNCES
    }
    if (client.isConnected()) {
        client.loop();
    }
    
}