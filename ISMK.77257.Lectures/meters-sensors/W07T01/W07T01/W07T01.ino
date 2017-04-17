/*
 Name:		W07T01.DHT11.Humidity.Temp.Sense
 File Name:	W07T01.ino
 Created:	4/13/2017 7:30:23 AM
 Author:	coskun
*/
#include<DHT11\dht11.h>

dht11 DHT11 = dht11(2);
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {
  int chk = DHT11.read();
  Serial.print("Read sensor: ");
  switch (chk)
  {
	case 0: Serial.println("OK"); break;
	case -1: Serial.println("Checksum error"); break;
	case -2: Serial.println("Time out error"); break;
	default: Serial.println("Unknown error"); break;
  }

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, DEC);

  Serial.print("Temperature (?C): ");
  Serial.println((float)DHT11.temperature, DEC);

  Serial.print("Temperature (?F): ");
  Serial.println(DHT11.fahrenheit(), DEC);

  Serial.print("Temperature (?K): ");
  Serial.println(DHT11.kelvin(), DEC);

  Serial.print("Dew Point (?C): ");
  Serial.println(DHT11.dewPoint(), DEC);

  Serial.print("Dew PointFast (?C): ");
  Serial.println(DHT11.dewPointFast(), DEC);

  delay(1000);
}
