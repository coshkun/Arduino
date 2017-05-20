/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
// include the SD library:
//#include <SPI.h>
//#include <SD.h>
#define ANTENNA_TURN_DELAY 637 //uS for 1 degree
#define ANTENNA_PIN 9
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
void Process();
void initSDCard(bool *LogFlag);
void logToFile();
//variables
static NMEAbuffer sercom_buffer;
static int antennaAngle;
//File logFile;
bool isLoggingPosibble = false;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	while(!Serial){};
	
	pinMode(ANTENNA_PIN, OUTPUT);
	digitalWrite(ANTENNA_PIN, LOW);
	antennaAngle = -1;
	
	Serial.println("Booting..");
	//initSDCard(&isLoggingPosibble);
	sercom_buffer.process(Process); //attach your ISR function once.
}

void loop() {
	sercom_buffer.syncronize();
	//you can override the process() for incoming duties

	//Mega2560 builds:
	//if(sercom_buffer._newData == true && isLoggingPosibble == true){
		//logToFile();}
}

void turnAntenna()
{
	  digitalWrite(9, HIGH);
	  delayMicroseconds(ANTENNA_TURN_DELAY);
	  digitalWrite(9, LOW);
}

void Process(){
	char *sync = &(sercom_buffer.states[0]);
	char *remote = &(sercom_buffer.states[1]);
	
	if (*sync == '0') // calculate new package in to buffer
	{
		Serial.println(*sync);
		for (byte i=0;i<5;i++)
		{
			Serial.print(" " + i);
			antennaAngle +=1;
			turnAntenna(); // 1 degree at each call
			delayMicroseconds(2777); // this is total time for now. substract wave fly time from this.
			//float distance = 3.14;
			//sercom_buffer.stream->sentence[i].SetValue(antennaAngle, distance, BearingType::TRUE);
			//sercom_buffer.stream->GetValue();
		}
		//Serial.print(sercom_buffer.stream->fullSentence);
		if(antennaAngle == 359) //that means after 359 sended.
			antennaAngle = -1;
		return;
	}
	if (*sync == '2')
	{
		//process incoming commands here..
		Serial.println("something comming.."); //debug
		return;
	}
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