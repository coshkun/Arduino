// #include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads


#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
String mesaj = "iyi gunler!";

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(mesaj.length());
  lcd.home();
  for(int i = 15; i>0; i--){
    lcd.setCursor(i,0);
    lcd.print(mesaj);
    delay(100);
    lcd.clear();
    }
    lcd.clear();
    delay(500);
    lcd.print(mesaj);
    delay(500);
    
    for(int i = 0; i<=16; i++){
    lcd.setCursor(i,0);
    lcd.print(mesaj);
    delay(100);
    lcd.clear();
    }
  //lcd.setCursor(10,1);
}
