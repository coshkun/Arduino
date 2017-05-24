/* 
* SerCom96.cpp
*
* Created: 5.05.2017 01:10:28
* Author: coskun
* 
*/
#include "SerCom96.h"
#include "Arduino.h"

volatile static voidFuncPtr usrFncPtr;

// default constructor
SerCom96::SerCom96()
{
  CurrentBuffer = new NMEAbuffer();
} //SerCom96 new instance

SerCom96::SerCom96(NMEAbuffer* buffer)
{
  CurrentBuffer = buffer;
} //SerCom96 standart initializer

// default destructor
SerCom96::~SerCom96()
{
  delete [] CurrentBuffer;
} //~SerCom96


