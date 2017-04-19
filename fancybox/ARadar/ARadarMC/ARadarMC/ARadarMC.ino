/*
 Name:		ARadarMC.Arduino.Based.Ulra-Sonic.Radar.MC-Unit
 File Name:	ARadarMC.ino
 Created:	4/16/2017 8:12:51 PM
 Author:	coskun

 NMEA Sample:

 SerCom96 Sample Senctence:
 cmd	00
 time	00000000000000
(ruler	0000000000000000000000000000000000000000000000000000000000000000000000000 00000 00)
 sentc	$RARAW,000,00.000,R,000,00.000,R,000,00.000,R,000,00.000,R,000,00.000,R,* chksum[5] CR LF
*/

volatile char serial_buffer[96];
char log_buffer[10][96];
//template <size_t row, size_t col>

//Delegates
void process(char *buffer, char (*log)[10][96]);
void syncronize(char *buffer);

// the setup function runs once when you press reset or power the board
void setup() {
	// 7,2KB for 75 sentence (each has 5 angels) makes 375 scan per sec.
	Serial.begin(57600);
	Serial.setTimeout(14); // 13,333 ms for 96bit
	while(!Serial){} //wait for connection;
	initializeSerCom();

}

// the loop function runs over and over again until power down or reset
void loop() {
	syncronize((char*)serial_buffer);
	process((char*)serial_buffer, &log_buffer);
}

void initializeSerCom(){
	for each (char c in serial_buffer) {c = 0;}

	NMEAword w; 
	w.coma1 = ','; 
	w.coma2 = ','; 
	w.coma3 = ','; 
	w.orientation = 'R';

	for each (char c in w.angle) {c = '0';}
	for each (char c in w.distance) {c = '0';}
	
	NMEAsentence s; 
	s.comma1 = ','; 
	s.startMark = '$'; 
	s.checkStar = '*';
	s.CR = 0x0d; //13;
	s.LF = 0x0a; //10;
	for each (char c in s.checksum) {c = '0';}

	int index=0;
	for each (char c in "RARAW") { s.command[index] = c; index++;}
	for each (NMEAword word in s.sentence) {word = w;}

	char sum_string[] = ""; // all between $ and *
	memcpy(sum_string, s.command, sizeof(char[5]) );
	memcpy(sum_string, &s.comma1, sizeof(char) );
	memcpy(sum_string, s.sentence, sizeof(s.sentence) );

	unsigned int chk = checksum(sum_string); //calculate 2-Byte parity
	memccpy(s.checksum, &chk, 0, sizeof(char[2])); //apply with little-endian

	NMEAbuffer b;
	for each (char c in b.reserved) {c = 0;}
	b.stream = s;
	b.states[1] = 0; b.states[0] = 0;

	memcpy((char*)serial_buffer, &b, sizeof(b));
}

struct NMEAword
{	//13 char lenght
	char angle[3];
	char coma1;
	char distance[6];
	char coma2;
	char orientation;
	char coma3;
};

struct NMEAsentence
{	// 80 char lenght
	char startMark;
	char command[5];
	char comma1;
	NMEAword sentence[5];
	char checkStar;
	char checksum[5];
	char CR;
	char LF;
};

struct NMEAbuffer
{	// 96 char lenght
	char states[2];
	char reserved[14];
	NMEAsentence stream;
};

unsigned int checksum(const char *s) {
	unsigned int c = 0;

	while(*s)
		c ^= *(s++);

	return c;
}

void syncronize(char *buffer)
{
	byte sync = buffer[0];

	if (Serial.available() >= 0 && sync == 0) // gelen veri olduðunda oku, yoksa gönderime devam et
	{
		byte byts = Serial.readBytesUntil('\n', buffer, sizeof(char[96]));
		if(byts == 96)
			sync = 1; // alert me with new data
	}
	else
	{
		if(sync == 1) // iþlenmemiþ veriler var, git iþle, sonra yine gel
			return;

		//buffer'ý karsýya gönder
		if (sync == 0)
		{
			sync = 1; //alert receiver with new data
			Serial.print(*buffer);
			sync = 0; //start listen port for next cmd
			delayMicroseconds(13334);
		}
	}
}

void process(char *buffer, char (*log)[10][96])
{
	byte sync = buffer[0]; //senkron bayragýný yakala
	if(sync == 0) // gonderime hazýr degilsen, defol git sonra gel
		return;

	if (sync == 1)
	{
		NMEAbuffer *last_logged_buffer, *new_buffer;

		byte i = 10, tmp[96];
		while ( *(log[i -1][95]) != '\n' && i > 0 )  //satýr sonlarýna bak
			i--;

		if(i==9){ //log is full, clear entire log and reset
			memccpy(tmp, log[i], 0, sizeof(char[96]));
			//last_logged_buffer = (NMEAbuffer*) tmp;
			//clr
			for(byte x=0;x<10;x++){ for(byte y=0;x<96;y++){
				*log[x][y] = 0;
			}}
			memccpy(log[i], tmp, 0, sizeof(char[96]));
			return;
		}
		//else if(i==0){ //log is empty, start from first line 
		//	new_buffer = (NMEAbuffer*) *log[0];
		//}
		else { // get the last buffer and last empty line
			last_logged_buffer = (NMEAbuffer*) *log[i];
			new_buffer = (NMEAbuffer*) *log[i+1];
		}

		// son buffer.la simdikini karþýlaþtýr burada..

	}
}