#include <PubSubClient.h>
#include "states.h"

// Auxiliar variables to store the current output state
String output1State = "off";
String output2State = "off";
String output3State = "off";
String output4State = "off";
String output5State = "off";
String output6State = "off";
String output7State = "off";
String output8State = "off";

//device information (instance) from cloudMqtt
const char* mqttServer = " ";    //for example "postman.cloudmqtt.com"
const int mqttPort = 12082;    //enter your instance port
const char* mqttUser = "*******";    //
const char* mqttPassword = "*******";

WiFiClient espClient;
PubSubClient MQTTclient(espClient);

void connectMQTT() {
  while (!MQTTclient.connected()) {
    Serial.println("Connecting to MQTT...");
    if (MQTTclient.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(MQTTclient.state());
      delay(2000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");

  char line = (char)payload[4];
  char onOff = (char)payload[6];

  // relay 1 controls
  if (line == '1') {
    if (onOff == '1') {
      SR_bitClear(0);
      digitalWrite(loadPin, HIGH);
    } else if (onOff == '0') {
      output1State = "off";
      SR_bitSet(0);
    }
  }
  //relay 2 controls
  if (line == '2') {
    if (onOff == '1') {
      output2State = "on";
      SR_bitClear(1);
    }
    else if (onOff == '0') {
      output2State = "off";
      SR_bitSet(1);
    }
  }
  // relay 3 controls
  if (line == '3') {
    if (onOff == '1') {
      output3State = "on";
      SR_bitClear(2);
    }
    else if (onOff = '0') {
      output3State = "off";
      SR_bitSet(2);
    }
  }
  // relay 4 controls
  if (line == '4') {
    if (onOff == '1') {
      output4State = "on";
      SR_bitClear(3);
    }
    else if (onOff = '0') {
      output4State = "off";
      SR_bitSet(3);
    }
  }
  // relay 5 controls
  if (line == '5') {
    if (onOff == '1') {
      output5State = "on";
      SR_bitClear(4);
    }
    else if (onOff == '0') {
      output5State = "off";
      SR_bitSet(4);
    }
  }
  //relay 6 controls
  if (line == '6') {
    if (onOff == '1') {
      output6State = "on";
      SR_bitClear(5);
    }
    else if (onOff == '0') {
      output6State = "off";
      SR_bitSet(5);
    }
  }
}
