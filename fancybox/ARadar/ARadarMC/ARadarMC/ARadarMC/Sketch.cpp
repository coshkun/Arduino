/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
// include the SD library:
#include <SPI.h>
#include <SD.h>
/*End of auto generated code by Atmel studio */
#include "SerCom96.h"

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

//delegates
void initSDCard(bool *LogFlag);
void logToFile();
//variables
static NMEAbuffer sercom_buffer;
//File logFile;
bool isLoggingPosibble = false;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	while(!Serial){};
	  
	Serial.println("Booting..");
	//initSDCard(&isLoggingPosibble);
}

void loop() {
	//Serial.print(sercom_buffer.stream->fullSentence);
	//sercom_buffer.syncronize(); //(char*)&sercom_buffer
	//sercom_buffer.process();
	sercom_buffer._getInputStr();
	sercom_buffer._parseInputStr();
	
	//Mega2560 builds:
	//if(sercom_buffer._newData == true && isLoggingPosibble == true){
		//logToFile();}
}

void initSDCard(bool *LogFlag){
	
	//if (!SD.begin(SERCOM_SD_CS)) {
		//Serial.println("SDC failed! or Card Holder is Empty.");
		//return;
	//}
	//Serial.println("initializing SDC");
	//if(!SD.exists(SERCOM_LOGFILE_NAME)){
		//logFile = SD.open(SERCOM_LOGFILE_NAME, FILE_WRITE);
	//}else{
		//SD.remove(SERCOM_LOGFILE_NAME);
		//logFile = SD.open(SERCOM_LOGFILE_NAME, FILE_WRITE);}
		//
	//if (logFile){
		//Serial.println(String(logFile.name()) +" is ready to logging.");
		//logFile.close();		
		//}   //This breaks memory integrity
//
	//*LogFlag = true;
	//Serial.println("SDC initialized.. Flag: " + String(isLoggingPosibble));
}

void logToFile(){
	//logFile = SD.open(SERCOM_LOGFILE_NAME, FILE_WRITE);
	//if(logFile){
		//logFile.println(sercom_buffer.stream->fullSentence);
	//logFile.close();}
	//else{
	//Serial.println("Err.openning file.");}
	
}