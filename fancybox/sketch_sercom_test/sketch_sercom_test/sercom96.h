/* 
* SerCom96.cpp
*
* Created: 5.05.2017 01:10:28
* Author: coskun
* 
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
//Constants
typedef void (*voidFuncPtr)(void);

enum BearingType { RELATIVE, TRUE };
enum CommandType { REGULAR, PRODUCER };
//Structures
typedef struct NMEAword{
  char angle[3] = "000";
  char comma1 = ',';
  char distance[6] = "000000";
  char comma2 = ',';
  char orientation = 'R';
  char comma3 = ',';
};

typedef struct NMEAsentence{
  char startMark = '$';
  char cmd[5] = "RARAW";
  char comma1 = ',';
  NMEAword sentence[5];
  char checkStar = '*';
  char checksum[5] = "00000";
  char CR = '\r';
  char LF = '\n';
};

typedef struct NMEAbuffer{
  char states[2] = "00";
  char reserved[14] = "00000000000000";
  NMEAsentence stream;
};
//Classrooms
class SerCom96
{
//variables
public:
  NMEAbuffer *CurrentBuffer;
protected:
private:
//functions
public:
  SerCom96();
  SerCom96(NMEAbuffer* buffer);
  ~SerCom96();
protected:
private:
  SerCom96( const SerCom96 &c );
  SerCom96& operator=( const SerCom96 &c );

}; //SerCom96


//helpers
static void nothing(void) {}

#endif //__SERCOM96_H__
