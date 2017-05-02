/*
 Name:    ARadarMC.Arduino.Based.Ulra-Sonic.Radar.MC-Unit
 File Name: ARadarMC.ino
 Created: 4/16/2017 8:12:51 PM
 Author:  coskun

 NMEA Sample:

 SerCom96 Sample Senctence:
 cmd  00
 time 00000000000000
(ruler  0000000000000000000000000000000000000000000000000000000000000000000000000 00000 00)
 sentc  $RARAW,000,00.000,R,000,00.000,R,000,00.000,R,000,00.000,R,000,00.000,R,* chksum[5] CR LF
*/

//#include<string.h>
bool booting = true;
char sercom_buffer[96];
char log_buffer[10][96];
//template <size_t row, size_t col>

//Delegates
void process(char *buffer, char (*log)[10][96]);
void syncronize(char *buffer);
void initializeSerCom();
unsigned int checksum(const char *s);
//Structures
struct NMEAword
{ //13 char lenght
  String angle; // max 3 char
  String coma1;
  String distance; // max 6 char
  String coma2;
  String orientation;
  String coma3;
};
struct NMEAsentence
{ // 80 char lenght
  String startMark;
  String command; // max 5 char
  String comma1;
  NMEAword* sentence;
  String checkStar;
  String checksum; // max 5 char
  char CR;
  char LF;
};
struct NMEAbuffer
{ // 96 char lenght
  char states[2];
  char reserved[14];
  NMEAsentence stream;
} b;

// the setup function runs once when you press reset or power the board
void setup() {
  // 7,2KB for 75 sentence (each has 5 angels) makes 375 scan per sec.
  Serial.begin(115200);
  //Serial.setTimeout(14); // 13,333 ms for 96bit
  while(!Serial){}; //wait for connection;
}

// the loop function runs over and over again until power down or reset
void loop() {
  if (booting){ initializeSerCom(); booting = false; }
  syncronize(sercom_buffer);
  process(sercom_buffer, &log_buffer);
}

void initializeSerCom(){

  //Serial.begin(115200);
  //while(!Serial){}

  for (int i=0 ; i<96 ; i++)
	sercom_buffer[i] = '0';

  ////Serial.write(sercom_buffer, sizeof(sercom_buffer)); //Debug
  ////Serial.print("\r\n"); //Debug
  NMEAword w;
  w.coma1 = ','; 
  w.coma2 = ','; 
  w.coma3 = ','; 
  w.orientation = 'R';

  if(w.angle.length() <=0 || w.angle.length() > 3)
	w.angle = "000";
  if(w.distance.length() <=0 || w.distance.length() > 6)
	w.distance = "000000";

  ////Serial.print(w.angle + w.coma1 + w.distance + w.coma2 + w.orientation + w.coma3);
  NMEAsentence s;
  s.sentence = new NMEAword[5];
  s.comma1 = ","; 
  s.startMark = "$"; 
  s.checkStar = "*";
  s.CR = 0x0d; //13;
  s.LF = 0x0a; //10;
  s.checksum = "00000";
  s.command = "RARAW";

  for (int i = 0; i < 5; i++)
  {
	//w.angle = String( i* 10); //Debug
	//memcpy(&s.sentence[i], &w, sizeof(NMEAword));  //this copies same buffer
	s.sentence[i] = w;
  }

  ////Serial.print("\r\n"); //Debug
  String sum_str = s.command + s.comma1;
  for (int i = 0; i < 5; i++)
  {
	sum_str += s.sentence[i].angle + 
	  s.sentence[i].coma1 + 
	  s.sentence[i].distance + 
	  s.sentence[i].coma2 + 
	  s.sentence[i].orientation + 
	  s.sentence[i].coma3;
  }
  ////Serial.print(sum_str); //Debug
  ////Serial.print("\r\n"); //Debug

  unsigned int chk = checksum(sum_str);
  //Serial.print(chk); //Debug
  s.checksum = s.checkStar + String(chk);
  //fill rest chars with zeroes
  while (s.checksum.length() < 6) { s.checksum = s.checksum  + "0"; }

  String full_sentence = s.startMark + sum_str + s.checksum + s.CR + s.LF;

  ////Serial.print(full_sentence);
  ////Serial.print(full_sentence.length());

  for (int i = 0; i < 80; i++)
  {
	sercom_buffer[16 + i] = full_sentence[i];
  }

  //b.stream = *( (NMEAsentence*) &full_sentence); //Experimental
  ////Serial.print("\r\n");//Debug
  ////Serial.write(sercom_buffer, sizeof(sercom_buffer)); Serial.print("\r\n");
}

unsigned int checksum(String& s) {
  unsigned int c = 0;
  int eof = s.length();

  while(eof>0) {
	eof--; c ^= s[eof]; }

  return c;
}

void syncronize(char *buffer)
{
  char* sync = &buffer[0];
  //sync = '1'; //Debug

  if (Serial.available() && *sync == '0') // gelen veri olduðunda oku, yoksa gönderime devam et
  {
	byte byts = Serial.readBytes(buffer, sizeof(char[96]));
	if(byts == 96)
	  *sync = '1'; // alert me with new data

  }
  else
  {
	//debug_Buffer(buffer);
	if(*sync == '1') // iþlenmemiþ veriler var, git iþle, sonra yine gel
	{return;}

	//buffer'ý karsýya gönder
	//else if (*sync == '0')
	{
	  *sync = '1'; //alert receiver with new data
	  //Serial.write(buffer, sizeof(char[96]));
	  *sync = '0'; //start listen port for next cmd
	  delayMicroseconds(13334);
	}
  }
  Serial.println(String("TEST"));
}

void process(char *buffer, char (*log)[10][96])
{
  char* sync = &buffer[0]; //senkron bayragýný yakala
  if(*sync == '0') // gonderime hazýr degilsen, defol git sonra gel
	return;
	
  if (*sync == '1')
  {
	NMEAbuffer *last_logged_buffer, *new_buffer;

	byte i = 10, tmp[96];
	while ( ( *(log[i -1][95]) != '\n') && i > 0 ){  //satýr sonlarýna bak
	  i--;}

	if(i==9){ //log is full, clear entire log and reset
	  memcpy(tmp, log[i], sizeof(char[96]));
	  //last_logged_buffer = (NMEAbuffer*) tmp;
	  //clr
	  for(byte x=0;x<10;x++){ for(byte y=0;x<96;y++){
		*log[x][y] = 0;
	  }}
	  memcpy(log[0][0], tmp, sizeof(char[96]));
	  return;
	}
	//else if(i==0){ //log is empty, start from first line 
	//  new_buffer = (NMEAbuffer*) *log[0];
	//}
	else { // get the last buffer and last empty line
	  last_logged_buffer = (NMEAbuffer*) log[i][0];
	  new_buffer = (NMEAbuffer*) log[i+1][0];
	}

	// son buffer.la simdikini karþýlaþtýr burada..
	Serial.write(log[i][0],sizeof(char[96]));
  }
}

void debug_Buffer(char *buffer)
{
  Serial.write(buffer, sizeof(char[96]));
}