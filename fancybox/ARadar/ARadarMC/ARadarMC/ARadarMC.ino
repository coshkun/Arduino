/*
 Name:		ARadarMC.Arduino.Based.Ulra-Sonic.Radar.MC-Unit
 File Name:	ARadarMC.ino
 Created:	4/16/2017 8:12:51 PM
 Author:	coskun
*/

char serial_buffer[96];

// the setup function runs once when you press reset or power the board
void setup() {
	// 7,2KB for 75 sentence (each has 5 angels) makes 375 scan per sec.
	Serial.begin(57600); 
	while(!Serial){} //wait for connection;
	initializeSerCom();

}

// the loop function runs over and over again until power down or reset
void loop() {
  
}

void initializeSerCom(){
	for each (char c in serial_buffer) {c = 0;}

	NMEAword w; 
	w.coma1 = ','; 
	w.coma2 = ','; 
	w.coma3 = ','; 
	w.orientation = 'R';

	for each (char c in w.angle) {c = '0';}
	
	NMEAsentence s; 
	s.comma1 = ','; 
	s.startMark = '$'; 
	s.checksum[0] = '*';

	int index=0;
	for each (char c in "RARAW") { s.command[index] = c; index++;}
	for each (NMEAword word in s.sentence) {word = w;}

	NMEAbuffer b;
	for each (char c in b.reserved) {c = 0;}
	b.stream = s;
	b.states[1] = 0; b.states[0] = 0;

	memcpy(serial_buffer, &b, sizeof(b));
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
	char checksum[8];
};

struct NMEAbuffer
{	// 96 char lenght
	char states[2];
	char reserved[14];
	NMEAsentence stream;
};