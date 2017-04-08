/*
 Name:		vs_lcd_example.ino
 Created:	4/6/2017 9:17:37 PM
 Author:	coskun
*/
#include <Wire.h>
#include <NewliquidCrystal\LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
String mesaj = "iyi geceler istanbullu dostlarim.";

// the setup function runs once when you press reset or power the board
void setup() {
	lcd.begin(16,2);
	Serial.begin(9600);

}

// the loop function runs over and over again until power down or reset
void loop() {
	// put your main code here, to run repeatedly:
	int uzunluk = mesaj.length();
	String pasaj = "";
	Serial.print(uzunluk);
	lcd.home();

		int j = 0;
		while (j<16)
		{
			lcd.setCursor(15-j,0);
			lcd.print(mesaj);
			delay(400);
			lcd.clear();
			j++;
		}

	for(int i = 0; i <= uzunluk - 16; i++)
	{
		lcd.setCursor(0,0);
		pasaj = mesaj.substring(i, 16+i);
		lcd.print(pasaj);
		delay(400);
		lcd.clear();
	}
	delay(600);
	//lcd.setCursor(10,1);
}
