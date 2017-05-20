/* 
* SerCom96.h
*
* Created: 5.05.2017 01:10:28
* Author: coskun

	NMEA Sample:

	SerCom96 Sample Senctence:
	cmd  00
	time 00000000000000
	(ruler  0000000000000000000000000000000000000000000000000000000000000000000000000 00000 00)
	sentc  $RARAW,000,00.000,R,000,00.000,R,000,00.000,R,000,00.000,R,000,00.000,R,* chksum[5] CR LF
*/

#ifndef __SERCOM96_H__
#define __SERCOM96_H__

#include "Arduino.h"

#ifndef SERCOM_SD_CS
#define SERCOM_SD_CS 10
#endif
#ifndef SERCOM_LOGFILE_NAME
#define SERCOM_LOGFILE_NAME "SC96LOG.TXT"
#endif

typedef void (*voidFuncPtr)(void);

enum BearingType { RELATIVE, TRUE };
enum CommandType { REGULAR, PRODUCER };

class SerCom96
{
//variables
public:
protected:
private:

//functions
public:
	SerCom96();
	~SerCom96();
protected:
private:
	SerCom96( const SerCom96 &c );
	SerCom96& operator=( const SerCom96 &c );

}; //SerCom96

class NMEAword //13 char lenght
{
	//variables
	public:
		String angle; // max 3 char
		String coma1;
		String distance; // max 6 char
		String coma2;
		String orientation;
		String coma3;
	private:

	//functions
	public:
	NMEAword();
	NMEAword(String Angle, String Distance, String Orientation);
	NMEAword(String Angle, String Distance, BearingType Orientation);
	void SetValue(String Angle, String Distance, BearingType Orientation);
	void SetValue(int Angle, float Distance, BearingType Orientation);
	String GetValue();
	~NMEAword();
	private:
	//NMEAword( const NMEAword &c );
	//NMEAword& operator=( const NMEAword &c );

}; //NMEAword

class NMEAsentence // 80 char lenght
{
	//variables
	public:
		String startMark;
		String command; // max 5 char
		String comma1;
		//NMEAword *sentence[5];
		NMEAword sentence[5];
		String fullSentence;
		String checkStar;
		String checksum; // max 5 char
		char CR;
		char LF;
	private:
		String _sumstr;
		//static int _intptr;

	//functions
	public:
	NMEAsentence();
	~NMEAsentence();
	String GetValue();
	void SetValue(NMEAword (*parameters)[5]);
	bool SetValue(NMEAword& Word, int Index);
	void SetCommand(String Command, CommandType Type);
	void SetCommand(String Command);
	private:
	//NMEAsentence( const NMEAsentence &c );
	//NMEAsentence& operator=( const NMEAsentence &c );
	unsigned int _checksum(String& s);

}; //NMEAword

class NMEAbuffer // 96 char lenght
{
	//variables
	public:
		String states; // char[2] gibi kullan;
		String reserved; // char[14] gibi kullan;
		NMEAsentence *stream;
		
	private:
		char receivedChars[96];
		volatile bool _newData;
		bool _isInputReaded;
	
	//functions
	public:
	NMEAbuffer();
	~NMEAbuffer();
	void syncronize();
	void process();
	void process(void (*)(void));
	
	private:	
	void _getInputStr();
	void _parseInputStr();
	void _recvWithEndMarker();
	//NMEAbuffer( const NMEAbuffer &c );
	//NMEAbuffer& operator=( const NMEAbuffer &c );

}; //NMEAword

class NMEAlog
{
	// variables
	public:
	private:
		NMEAbuffer *p[];
		int _ES; // Eleman Sayýsý
		int _MAX;// Maximum Kapasite
	
	//functions
	public:
		NMEAlog();
		~NMEAlog();
		NMEAlog(int Capacity);
		void Add(NMEAbuffer b);
		bool GetValue(int Index, NMEAbuffer& output);
	//private:
		void genislet(int boyut);
		//NMEAlog( const NMEAlog &c );
		//NMEAlog& operator=( const NMEAlog &c );
};

//helpers
static void nothing(void) {}

#endif //__SERCOM96_H__
