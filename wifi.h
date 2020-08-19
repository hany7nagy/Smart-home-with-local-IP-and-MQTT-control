#include <ESP8266WiFi.h>

//the wifi credentials
const char* ssid = "########";   //put your wifi name
const char* password = "********";   //put your wifi password

//the wifi default credentials to connect after resetting the router setings
const char* ssid_def = "########";  //put your default wifi name
const char* password_def = "********";  //put your default wifi password

//function to connect to wifi
void setupWifi(const char* ssid, const char* pass)
{
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  // Set your Static IP address to control the esp8266 with it
  IPAddress local_IP(192, 168, 1, 184);
  // Set your Gateway IP address
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 0, 0);
  IPAddress primaryDNS(8, 8, 8, 8);   //optional
  IPAddress secondaryDNS(8, 8, 4, 4); //optional

  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  int timout = millis();
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    int timnow = millis();
    //if wifi credentials changed to default
    if ((timnow - timout) >= 30000) {
      Serial.println(ssid_def);
      setupWifi(ssid_def, password_def);
    }
  }

  Serial.println("Connected to wifi");
  Serial.println(WiFi.localIP());
}
