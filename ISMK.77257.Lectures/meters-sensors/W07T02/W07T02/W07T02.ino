/*
 Name:		W07T02.ino
 Created:	4/13/2017 8:43:14 AM
 Author:	coskun
*/
#include<Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String sifre;
char key;
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	lcd.begin(16,2);
	sifre = "";
}

// the loop function runs over and over again until power down or reset
void loop() {
	key = keypad.getKey();

	if (key)
	{
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("Enter password: ");
		lcd.setCursor(0,1);
		lcd.print(sifre);
		Serial.print(key);

		if (key=='c'||key=='C')
			sifre = "";
		else if(key=='#')
		{
			if (sifre=="1234")
			{
				lcd.clear();
				lcd.setCursor(0,0);
				lcd.print("Hello Admin,");
				lcd.setCursor(0,1);
				lcd.print("CMD: ");
				
				while (true) // Mission loop :)
				{
					//delay(500);
					sifre="";
					key = keypad.getKey();
					if(key=='c'||key=='C')
						break;
				}
			}
			else {sifre = ""; return;}
		}
		else
		{
			sifre += key;
			lcd.setCursor(0,1);
			lcd.print(sifre);
		}

	}
	else
	{
		if(sifre.length()>0)
			return;
		lcd.clear();
		delay(200);
		lcd.setCursor(0,0);
		lcd.print("Hello Admin,");
		lcd.setCursor(0,1);
		lcd.print("Enter password: ");
		delay(500);
	}
	
}
