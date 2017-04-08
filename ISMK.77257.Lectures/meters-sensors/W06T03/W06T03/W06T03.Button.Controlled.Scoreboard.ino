/*
 Name:		W06T03.ino
 Test:		W06T03.I2C.2x16-LCD.Button.Controlled.Scoreboard
 Created:	4/7/2017 7:21:52 AM
 Author:	coskun
*/
#include "Button.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
String mesaj = "iyi gunler!";

bool buton1_state = false;
bool buton2_state = false;
int sayac1 = 0, sayac2 = 0;
bool a,b;
Button myButton1;
Button myButton2;

// the setup function runs once when you press reset or power the board
void setup() {
	lcd.begin(16,2);
	lcd.backlight();
	Serial.begin(9600);
	pinMode(11,INPUT);
	pinMode(12,INPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
	a = (bool) digitalRead(11);
	b = (bool) digitalRead(12);

	myButton1.processButton(a);
	sayac2 = myButton2.processButton(b, sayac2);

	if (myButton1.isPressed())
	{
		sayac1++;
	}

	//Butona Bak: (Inline Function Below)
	//sayac1 = processButton(a,buton1_state,sayac1,0);
	//sayac2 = processButton(b,buton2_state,sayac2,1);

	lcd.home();
	lcd.setCursor(0,0);
	lcd.print("Home   : " + String(sayac1)); // you can use that   myButton1.Counter;  instead of sayac1
	lcd.setCursor(0,1);
	lcd.print("Visitor: " + String(sayac2));
	//delay(500);
}


//Butona Bak:
int processButton(bool b, bool state, int sayac, int buton_no){
	Serial.println("b_Giris: " + String(b) + "state_Giris: " + String(state) + "sayac_G: " + String(sayac));
  if (b==true)
  {
	if (state == false)
	{
		state = true;
		sayac++;
	}
  }
  else
  {
	state=false;
  }
  if(buton_no==0)buton1_state = state;
  if(buton_no==1)buton2_state = state;

  return sayac;
}