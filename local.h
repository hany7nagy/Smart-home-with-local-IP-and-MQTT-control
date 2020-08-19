
#include <ESP8266WiFi.h>
#include "states.h"

// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void Local_connect() {
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off and the opposit bit in sh reg is 0
            if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("GPIO 1 on");
              output1State = "on";
              SR_bitClear(0);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("GPIO 1 off");
              output1State = "off";
              SR_bitSet(0);
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              SR_bitClear(1);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";
              SR_bitSet(1);
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 3 on");
              output3State = "on";
              SR_bitClear(2);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 3 off");
              output3State = "off";
              SR_bitSet(2);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              SR_bitClear(3);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              SR_bitSet(3);
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              SR_bitClear(4);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              SR_bitSet(4);
            } else if (header.indexOf("GET /6/on") >= 0) {
              Serial.println("GPIO 6 on");
              output6State = "on";
              SR_bitClear(5);
            } else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("GPIO 6 off");
              output6State = "off";
              SR_bitSet(5);
            } else if (header.indexOf("GET /reset") >= 0) {
              SR_reset();
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>@font-face{font-family:hemiHead;src:url('./hemi head bd it.ttf')}*{box-sizing:border-box}body{margin:0;padding:0;font-family:hemiHead,Tahoma,Geneva,Verdana,sans-serif;text-align:center}");
            // 3 lins headiong
            client.println(".my-title .title{position:relative}.my-title .title h2{color:#333;font-size:38px;font-weight:bolder;position:relative;text-transform:capitalize;padding-bottom:30px;margin-bottom:30px}");
            client.println(".my-title .title .line{display:block;width:160px;height:2px;background-color:#ff305b;position:absolute;top:65px;left:50%;transform:translate(-50%,0)}");
            client.println(".my-title .title h2::after{content:'';display:block;width:80px;height:2px;background-color:#ff305b;position:absolute;top:60px;left:50%;transform:translate(-50%,0)}.my-title .title h2::before{content:'';display:block;width:80px;height:2px;background-color:#ff305b;position:absolute;top:70px;left:50%;transform:translate(-50%,0)}");
            //-----------------------------
            client.println(".controls{display:flex;justify-content:space-between;align-items:center;flex-flow:row wrap;border:1px solid #ccc;text-align:center;border-radius:15px;box-shadow:0 2px 8px rgba(0,0,0,.26);padding:20px 15px;width:90%;margin:auto}");
            client.println(".control{padding: 1rem;width:180px;height:130px;margin:10px;display:flex;justify-content:space-evenly;align-items:center;flex-flow:column nowrap;padding-bottom:10px;border:1px solid #ccc;text-align:center;border-radius:15px;box-shadow:0 2px 8px rgba(0,0,0,.26)}");
            client.println(".control .btn-control{font:inherit;padding:.5rem 2rem;outline:0;color:#fff;border-radius:6px;box-shadow:0 1px 8px rgba(0,0,0,.26);cursor:pointer;margin:0 .5rem .5rem;transition:background-color .2s ease-in-out}");
            client.println(".btn-on{border:1px solid #00329e;background-color:#375fb7}");
            client.println(".btn-on:hover{background-color:#00329e}");
            client.println(".btn-off{background-color:#ff3217;border:1px solid #d30808;color:#fff}");
            client.println(".btn-off:hover{background-color:#d30808}@media (max-width:570px){.control{width:70%;margin:15px auto;height:140px;}.btn-control{font-size:1.5rem;padding:1rem 3rem}}</style>");

            // Web Page Heading
            client.println("<body><div class=\"my-title\"> <div class=\"title\"> <h2>VTS Smart Office</h2> <div class=\"line\"></div></div></div>");
            client.println("<div class=\"controls\">");
            //---------------------------------------
            // Relay 1 controls
            client.println("<div class=\"control\"> <h4>line 1 state: " + output1State + "</h4>");
            if (output1State == "off") {
              client.println("<a href=\"/1/on\"> <button class=\"btn-control btn-on\">ON</button> </a></div>");
            } else {
              client.println("<a href=\"/1/off\"> <button class=\"btn-control btn-off\">OFF</button> </a></div>");
            }
            //----------------------------------------
            // Relay 2 controls
            client.println("<div class=\"control\"> <h4>line 2 state: " + output2State + "</h4>");
            if (output2State == "off") {
              client.println("<a href=\"/2/on\"> <button class=\"btn-control btn-on\">ON</button> </a></div>");
            } else {
              client.println("<a href=\"/2/off\"> <button class=\"btn-control btn-off\">OFF</button> </a></div>");
            }
            //----------------------------------------

            //---------------------------------------
            // Relay 3 controls
            client.println("<div class=\"control\"> <h4>line 3 state: " + output3State + "</h4>");

            if (output3State == "off") {
              client.println("<a href=\"/3/on\"> <button class=\"btn-control btn-on\">ON</button> </a></div>");
            } else {
              client.println("<a href=\"/3/off\"> <button class=\"btn-control btn-off\">OFF</button> </a></div>");
            }
            //----------------------------------------

            //---------------------------------------
            // Relay 4 controls
            client.println("<div class=\"control\"> <h4>line 4 state: " + output4State + "</h4>");

            if (output4State == "off") {
              client.println("<a href=\"/4/on\"> <button class=\"btn-control btn-on\">ON</button> </a></div>");
            } else {
              client.println("<a href=\"/4/off\"> <button class=\"btn-control btn-off\">OFF</button> </a></div>");
            }
            //----------------------------------------

            //---------------------------------------
            // Relay 5 controls
            client.println("<div class=\"control\"> <h4>line 5 state: " + output5State + "</h4>");

            if (output5State == "off") {
              client.println("<a href=\"/5/on\"> <button class=\"btn-control btn-on\">ON</button> </a></div>");
            } else {
              client.println("<a href=\"/5/off\"> <button class=\"btn-control btn-off\">OFF</button> </a></div>");
            }
            //----------------------------------------

            //---------------------------------------
            // Relay 6 controls
            client.println("<div class=\"control\"> <h4>line 6 state: " + output6State + "</h4>");
            client.println("");

            if (output6State == "off") {
              client.println("<a href=\"/6/on\"> <button class=\"btn-control btn-on\">ON</button> </a></div>");
            } else {
              client.println("<a href=\"/6/off\"> <button class=\"btn-control btn-off\">OFF</button> </a></div></div>");
            }
            //---------------------------------------

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
