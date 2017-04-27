/*
 Name:		W08T01.RFID.Read.Write.with.EEPROM
 File Name:	W08T01.ino
 Created:	4/20/2017 7:25:52 AM
 Author:	coskun
*/
#include <SPI.h>
#include <RFID.h>
#include <EEPROM.h>

RFID rf(10,5);

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	SPI.begin(); 
	
	
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
