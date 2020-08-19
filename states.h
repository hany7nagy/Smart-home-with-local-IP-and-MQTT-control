#include <EEPROM.h>

#ifndef states_H
#define states_H

// Auxiliar variables to store the current output state
extern String output1State;
extern String output2State;
extern String output3State;
extern String output4State;
extern String output5State;
extern String output6State;
extern String output7State;
extern String output8State;

// Assign output variables to GPIO pins for the shift regester
const int dataPin = 12;   //Outputs the byte to transfer
const int loadPin = 13;   //Controls the internal transference of data in SN74HC595 internal registers
const int clockPin = 15;  //Generates the clock signal to control the transference of data

//the address at whitch we store the shift reg data and retrive from:
int SR_address = 1;
byte output_bits ;

//set spesific bit to >>1<< and send the output to shift reg
void SR_bitSet(int b) {
  bitSet(output_bits, b);
  Serial.print("on bitSet : ");
  Serial.println(output_bits);
  EEPROM.write(SR_address, output_bits);    //update the >>output_bits<< in the address
  EEPROM.commit();                          //Store data to EEPROM
  digitalWrite(loadPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, output_bits);
  digitalWrite(loadPin, HIGH);
}
//set spesific bit to >>0<< and send the output to shift reg
void SR_bitClear(int b) {
  bitClear(output_bits, b);
  Serial.print("on bitClear : ");
  Serial.println(output_bits);
  EEPROM.write(SR_address, output_bits);    //update the >>output_bits<< in the address
  EEPROM.commit();                          //Store data to EEPROM
  digitalWrite(loadPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, output_bits);
  digitalWrite(loadPin, HIGH);
}
//on start function to reset all relays 
//by setting all bits to >1< and the uln output will be zeros 
void SR_reset(){
  digitalWrite(loadPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 255);
  digitalWrite(loadPin, HIGH);
}
//retrive the last value of output_bits from the rom and send it to the shift reg
void SR_lastStates(){
  Serial.println("last state : ");
  Serial.println(output_bits);
  output_bits = EEPROM.read(SR_address);    //read from >>SR_address<< address
  Serial.println(output_bits);
  digitalWrite(loadPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, output_bits);
  digitalWrite(loadPin, HIGH);
}

#endif
