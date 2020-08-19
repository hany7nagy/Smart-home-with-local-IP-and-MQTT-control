#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>

#include "cloudMQTT.h"
#include "wifi.h"
#include "local.h"
#include "states.h"

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(2000);

  pinMode(dataPin, OUTPUT);
  pinMode(loadPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  SR_reset();
  SR_lastStates();
  
  setupWifi(ssid, password);
  
  MQTTclient.setServer(mqttServer, mqttPort);
  MQTTclient.setCallback(callback);
  connectMQTT();
  MQTTclient.publish("enter your topic name here", "hello"); //Topic name
  MQTTclient.subscribe("enter your topic name here");

  server.begin();
  
}

void loop() {
  if (!MQTTclient.connected())
  {
    connectMQTT();
  }
  MQTTclient.loop();
  
  Local_connect();
}
