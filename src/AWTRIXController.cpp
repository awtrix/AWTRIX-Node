#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "awtrix-conf.h"

//////////////////////////////////////////////////////////////
//////////////////////// Don't touch /////////////////////////

WiFiClient espClient;
PubSubClient client(espClient);

bool updating = false;
unsigned long previousMillis = 0;

void sendToAwtrix(char * text, int icon) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["name"] = nodename;
  JsonObject& command = root.createNestedObject("command");
  command["icon"] = icon;
  command["text"] = text;
  String JS;
  root.printTo(JS);
  client.publish("awtrixnode", JS.c_str());
}

void doJob() {
  sendToAwtrix("test", iconID);
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "AWTRIXnode-";
    clientId += String(random(0xffff), HEX);
    if (!client.connect(clientId.c_str())) {
      delay(5000);
    }
  }
}

void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  client.setServer(awtrix_server, 7001);
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();

  if (!updating) {
    if (!client.connected()) {
      reconnect();
    } else {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        doJob();
      }
    }
    client.loop();
  }
}