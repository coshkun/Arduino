#include <Arduino.h>

/*
 Name:    ARadarMC.Arduino.Based.Ulra-Sonic.Radar.MC-Unit
 File Name: ARadarMC.ino
 Created: 4/16/2017 8:12:51 PM
 Author:  coskun

 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11 on Arduino Uno/Duemilanove/Diecimila
 ** MISO - pin 12 on Arduino Uno/Duemilanove/Diecimila
 ** CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila
 ** CS - depends on your SD card shield or module.
 Pin 10 used here for consistency with pin ordering.

 NMEA Sample:

 SerCom96 Sample Senctence:
 cmd  00
 time 00000000000000
(ruler  0000000000000000000000000000000000000000000000000000000000000000000000000 00000 00)
 sentc  $RARAW,000,00.000,R,000,00.000,R,000,00.000,R,000,00.000,R,000,00.000,R,* chksum[5] CR LF
*/

#include "sercom96.h"
//global varies
SerCom96 sc;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //b = new NMEAbuffer();
  Serial.write((char*) sc.CurrentBuffer, sizeof(char[96]));
}

void loop() {
  // put your main code here, to run repeatedly:

}
