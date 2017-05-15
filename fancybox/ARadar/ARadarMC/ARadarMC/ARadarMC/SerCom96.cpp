/* 
* SerCom96.cpp
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


#include "SerCom96.h"
#include "Arduino.h"

// default constructor
SerCom96::SerCom96()
{
} //SerCom96

// default destructor
SerCom96::~SerCom96()
{
} //~SerCom96

// default constructor
NMEAword::NMEAword()
{
	angle = "000"; // max 3 char
	coma1 = ",";
	distance = "000000"; // max 6 char
	coma2 = ",";
	orientation = "R";
	coma3 = ",";
} //NMEAword
NMEAword::NMEAword(String Angle, String Distance, String Orientation)
{
	angle = Angle; // max 3 char
	coma1 = ",";
	distance = Distance; // max 6 char
	coma2 = ",";
	if (Orientation == "T" || Orientation == "t")
	orientation = "T";
	else if (Orientation == "R" || Orientation == "r" || Orientation == NULL)
	orientation = "R";
	else
	orientation = "R";
	coma3 = ",";
} //NMEAword
NMEAword::NMEAword(String Angle, String Distance, BearingType Orientation)
{
	angle = Angle; // max 3 char
	coma1 = ",";
	distance = Distance; // max 6 char
	coma2 = ",";
	if (Orientation == 1)
		orientation = "T";
	else if ((Orientation == 0) || Orientation == NULL)
		orientation = "R";
	else
		orientation = "R";
	coma3 = ",";
} //NMEAword
void NMEAword::SetValue(String Angle, String Distance, BearingType Orientation)
{
	angle = Angle; // max 3 char
	distance = Distance; // max 6 char
	if (Orientation == 1)
	orientation = "T";
	else if ((Orientation == 0) || Orientation == NULL)
	orientation = "R";
	else
	orientation = "R";
}
void NMEAword::SetValue(int Angle, float Distance, BearingType Orientation)
{
	if (Angle>359)
		Angle = Angle % 360;
		
	if (Angle <= 0 || Angle == NULL)
		angle = "000";
	else if(Angle<100 && Angle > 0)
		angle = "0" + String(Angle);
	else if(Angle>=100 && Angle<360)
		angle = String(Angle);
		
	if(Distance <= 0 || Distance == NULL)
		distance = "00.000";
	else if(Distance >= 100)
		distance = "99.999";
	else 
	{
		char str_temp[6];
		// workaround
		/* 4 is mininum width, 3 is precision; float value is copied onto str_temp*/
		dtostrf(Distance, 4, 3, str_temp);
		distance = String(str_temp);
		int i = String(distance).indexOf('.');
		while(i<2){
			distance = "0" + distance; i++;}
	}
	
	//distance = Distance; // max 6 char
	if (Orientation == 1)
	orientation = "T";
	else if ((Orientation == 0) || Orientation == NULL)
	orientation = "R";
	else
	orientation = "R";
}
String NMEAword::GetValue()
{
	return (angle + coma1 + distance + coma2 + orientation + coma3);
}// returns "000,00.000,R," formated value
// default destructor
NMEAword::~NMEAword()
{
} //~NMEAword

// default constructor
NMEAsentence::NMEAsentence()
{
	startMark = "$";
	command = "RARAW"; // max 5 char
	comma1 = ",";
	//sentence = new NMEAword[5];
	checkStar = "*";
	checksum = "00000"; // max 5 char
	CR = 0x0d; //13;
	LF = 0x0a; //10;
	
	//for (int i = 0; i < 5; i++)
	//{
		//NMEAword *w = new NMEAword();
		//sentence[i] = w;
		////memcpy(sentence[i], &w, sizeof(NMEAword));
	//}
		
	_sumstr = command + comma1;
	for (int i = 0; i < 5; i++)
	{
		_sumstr += sentence[i].angle +
		sentence[i].coma1 +
		sentence[i].distance +
		sentence[i].coma2 +
		sentence[i].orientation +
		sentence[i].coma3;
	}
	unsigned int chk = _checksum(_sumstr);
	checksum = checkStar + String(chk);
	//fill rest chars with zeroes
	while (checksum.length() < 6) { checksum = checksum  + "0"; }
	fullSentence = startMark + _sumstr + checksum + CR + LF;
	//_intptr = 0;
	
} //NMEAsentence
String NMEAsentence::GetValue()
{
	_sumstr = command + comma1;
	for (int i = 0; i < 5; i++)
	{
		_sumstr += sentence[i].angle +
		sentence[i].coma1 +
		sentence[i].distance +
		sentence[i].coma2 +
		sentence[i].orientation +
		sentence[i].coma3;
	}
	unsigned int chk = _checksum(_sumstr);
	checksum = checkStar + String(chk);
	//fill rest chars with zeroes
	while (checksum.length() < 6) { checksum = checksum  + "0"; }
	fullSentence = startMark + _sumstr + checksum + CR + LF;
	return fullSentence;
}
void NMEAsentence::SetValue(NMEAword (*parameters)[5])
{
	for (int i=0; i<5;i++)
	{
		NMEAword* w = new NMEAword((*parameters)[i].angle, (*parameters)[i].distance, (*parameters)[i].orientation);
		memcpy(&sentence[i], &w, sizeof(w));
		//*sentence[i] = w;
	}
}
bool NMEAsentence::SetValue(NMEAword& Word, int Index)
{
	if(Index<0 || Index > 4)
		return false;
	//NMEAword* w = new NMEAword(Word.angle, Word.distance, Word.orientation);
	memcpy(&sentence[Index], &Word, sizeof(Word));
	return true;
}
void NMEAsentence::SetCommand(String Command)
{
	SetCommand(Command, CommandType::REGULAR);
}
void NMEAsentence::SetCommand(String Command, CommandType Type)
{
	if(Command != "" || Command != NULL)
		command = Command;
	else
		command = "RARAW";

	if (Type == CommandType::PRODUCER)
		startMark = "!";
	else if(Type == CommandType::REGULAR || Type == NULL)
		startMark = "$";
	else
		startMark = "$";
}
unsigned int NMEAsentence::_checksum(String& s) {
	unsigned int c = 0;
	int eof = s.length();

	while(eof>0) {
	eof--; c ^= s[eof]; }

	return c;
} //private
// default destructor
NMEAsentence::~NMEAsentence()
{
	//delete [] sentence;
} //~NMEAsentence

// default constructor
NMEAbuffer::NMEAbuffer()
{
	//states[0] = '0'; states[1] = '0';
	//for (int i = 0; i<14; i++)
		//{reserved[i] = '0';}
	states= "00";
	reserved = "00000000000000";
	
	//memcpy(&stream, &s, sizeof(NMEAsentence));
	delete stream;
	NMEAsentence *s = new NMEAsentence();
	stream = s;
	
	// Prepare privates
	_isInputReaded = false;
	_newData = false;
} //NMEAbuffer
void NMEAbuffer::syncronize()
{
	char* sync = &states[0];
	//Serial.println(*sync); //Debug
	//char *b = (char*) this;
	char *b;
	
	  if (Serial.available() && *sync == '0') // gelen veri olduðunda oku, yoksa gönderime devam et
	  {
		  byte byts = Serial.readBytes(b, sizeof(NMEAbuffer));
		  //String _inboud = Serial.readString();
		  //memcpy(b,&_inboud,sizeof(char[96]));
		  if(byts == 96)
			*sync = '1'; // alert me with new data
	  }
	  else
	  {
		  //debug_Buffer(buffer);
		  if(*sync == '1') // iþlenmemiþ veriler var, git iþle, sonra yine gel
		  return;

		  //buffer'ý karsýya gönder
		  else if (*sync == '0')
		  {
			  *sync = '1'; //alert receiver with new data
			  Serial.print(String(states) + String(reserved) + stream->fullSentence); //((NMEAbuffer*)b)->stream->fullSentence
			  *sync = '0'; //start listen port for next cmd
			  delayMicroseconds(13334);
		  }
	  }
}
void NMEAbuffer::process()
{
	  char* sync = &states[0]; //senkron bayragýný yakala
	  //Serial.println("fmPrc: " + String(*sync));
	  //Serial.write(*buffer, sizeof(char[96]));
	  if(*sync == '0') // gonderime hazýr degilsen, defol git sonra gel
	  return;
	  
	  if (*sync == '1')
	  {
		  Serial.println(String("Incoming Data:"));
		  Serial.print(String(states) + String(reserved) + stream->fullSentence);
		  //delete stream;
		  //stream = new NMEAsentence();
		  
		  *sync = '0'; // Exit after processing
	  }
}

void NMEAbuffer::getInputStr(){

	recvWithEndMarker();
	if (_newData == true) {
		Serial.println(receivedChars);
		_isInputReaded = true; _newData = false;
	}
}
void NMEAbuffer::parseInputStr(){
	if (_isInputReaded)
	{
		Serial.println("Lenght: " + String(String(receivedChars).length())); //Debug
		states = String(receivedChars[0]) + String(receivedChars[1]);
		Serial.println("States: " + states); //Debug
		reserved = "";
		for (byte i=2;i<16;i++)
			reserved += String(receivedChars[i]);
		Serial.println("Reserved: " + reserved); //Debug
		
		memcpy(stream, &receivedChars[16], sizeof(char[80]));
		Serial.print("Stream: ");
		Serial.println((char*)stream);
		//_inputstr = "";
		_isInputReaded = false; // reset Flag before exit
	}
}
void NMEAbuffer::recvWithEndMarker() {
	static byte ndx = 0;
	byte numChars = 95;
	char endMarker = '\n';
	char rc;


	while (Serial.available() > 0 && _newData == false) {
		rc = Serial.read();

		if (rc != endMarker) {
			receivedChars[ndx] = rc;
			ndx++;
			if (ndx >= numChars) {
				ndx = numChars - 1;
			}
		}
		else {
			receivedChars[ndx] = '\0'; // terminate the string
			ndx = 0;
			_newData = true;
		}
	}
}
// default destructor
NMEAbuffer::~NMEAbuffer()
{
} //~NMEAbuffer

// default constructor
NMEAlog::NMEAlog()
{
	//Serial.println("Start default log creation..");
	*p = new NMEAbuffer[10];
	_MAX = 10; _ES = 0;
	//Serial.println("Log Created..");
}
NMEAlog::NMEAlog(int Capacity)
{
	NMEAbuffer n[Capacity];
	delete [] p;
	*p = n;
	//memcpy(p, &n, (sizeof(NMEAbuffer) * Capacity) );
	//delete n;

	_MAX = Capacity; _ES = 0;
	Serial.println("Exiting constructor..");
}
void NMEAlog::genislet(int boyut)
{
	NMEAbuffer *yeniAlan = new NMEAbuffer[_MAX + boyut];
	memcpy(yeniAlan, &p, (sizeof(NMEAbuffer) * _ES));
	delete [] p;
	*p = yeniAlan;
}
void NMEAlog::Add(NMEAbuffer b)
{
	if(_ES ==_MAX)
		genislet(_MAX);
	
	//p[_ES] = b;
	memcpy(&p[_ES], &b, sizeof(b));
	_ES++;
}
bool NMEAlog::GetValue(int Index, NMEAbuffer& output)
{
	if (Index<0 || Index >= _ES)
	return false;
	
	//output = p[Index];
	memcpy(&output, &p[Index], sizeof(NMEAbuffer));
	return true;
}
// default destructor
NMEAlog::~NMEAlog()
{
	
}
