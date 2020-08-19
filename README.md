# Smart-home-with-local-IP-and-MQTT-control
# this project is created and licenced by :: https://github.com/hany7nagy 
# linkedin profile :: https://www.linkedin.com/in/hany-nagy-99b542162/
smart home code with esp8266 for six lines that is controlled with local IP page and also controlled over cloud using MQTT protocol over cloudMQTT.com
using shift regester >>>(74HC595)<<< and >>>(ULN2803AN)<<< 
and your output to the relays will be the output of the uln
the code stores the last states of the relays on the esp8266 rom so that if the electricity goes off and come back again it retrives the last states
used ESP8266WiFi.h , PubSubClient.h , EEPROM.h liberaries 
