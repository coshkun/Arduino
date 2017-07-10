#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <EEPROM.h>

#define _BUZZER_ 13
#define _GASS_ 12
#define _PIR_ 2
#define _SERVO_ 5

//Flags
bool FIRST_BOOT = false;   // <- ilk çalıştırmada burası true yapılarak kurum işlemi yapılır.
bool ALARM_DURUM = false;
bool YANGIN_DURUM = false;
bool HIRSIZ_DURUM = false;


// RS,E,D4,D5,D6,D7
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);
Servo servo;

// keypad setup
char tus_takimi[4][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte satir_pin[4] = {A5, A4, A3, A2};
byte sutun_pin[3] = {A1, 3, 4};
Keypad tustakim = Keypad(makeKeymap(tus_takimi), satir_pin, sutun_pin, 4, 3);
char eski_karakter;

// sifreler
char sifre[5] = {'1', '4', '0', '4', '7'};
char puk[8] = {'8', '8', '8', '8', '8', '8', '8', '8'};
String guncelSifre = "";
String userInput = "";

void setup() {
  // lcd setup:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Booting..");

  // digital i/o:
  pinMode(_BUZZER_, OUTPUT);
  pinMode(_GASS_, INPUT);
  pinMode(_PIR_, INPUT);
  digitalWrite(_GASS_, LOW);
  digitalWrite(_PIR_, LOW);

  // servo setup
  servo.attach(_SERVO_);
  servo.write(0);

  //Password Begin
  if (FIRST_BOOT)
  {
    for (int i = 0; i < 5; i++) {
      EEPROM.write(i, sifre[i]);
    }
    for (int i = 0; i < 8; i++) {
      EEPROM.write( 5 + i, puk[5 + i]);
    }
  } else {
          for(int i=0; i<5;i++)
          {
            guncelSifre += (char)EEPROM.read(i);
          }
  }


  //Standby
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hazir..");
  //DEBUG
  Serial.begin(9600);
  //Serial.println(guncelSifre);
}

void loop() {
  // put your main code here, to run repeatedly:
  KeypadOku();
  YanginVarmi();
  HirsizVarmi();

  delay(2000);
  
  AlarmCal();
}

void AlarmCal() {
  if (ALARM_DURUM)
  {
    digitalWrite(_BUZZER_, LOW);
    delay(200);
    digitalWrite(_BUZZER_, HIGH);
    delay(200);
  }
  else
  {
    digitalWrite(_BUZZER_, LOW);
  }
}

void YanginVarmi() {
  bool sensor = digitalRead(_GASS_);

  if (sensor && !YANGIN_DURUM)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FIRE ALARM");
    lcd.setCursor(0, 1);
    lcd.print("press # to close");
    ALARM_DURUM = true;
    YANGIN_DURUM = true;
  }
  else if (sensor == false)
  {
    if (YANGIN_DURUM)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Hazir..");
    }
    YANGIN_DURUM = false;
  }
}

void HirsizVarmi() {
  bool sensor = digitalRead(_PIR_);

  if (sensor && !HIRSIZ_DURUM)
  {
    //Gecikme fonsiyonu eklenecek
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("HIRSIZ VAR");
    lcd.setCursor(0, 1);
    lcd.print("enter password:");
    //sifre kontrolünü burda yap
    ALARM_DURUM = true;
    HIRSIZ_DURUM = true;
  }
  else if (HIRSIZ_DURUM /* + sifre kontrolü */)
{
  ALARM_DURUM = false;
}

}

void KeypadOku() {
  char key = tustakim.getKey();
  
  if (YANGIN_DURUM == true && key == '#'){
    ALARM_DURUM = false;
    // YANGIN_DURUM==true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FIRE ALARM");
    lcd.setCursor(0, 1);
    lcd.print("alarm suppresed!");
  }

  if(key == '#')
  {
    // sifre kontrolleri
  }
  else{
    // userInput = "*****";
    if(eski_karakter!=key && userInput.length() < 5)
    {
      userInput += key;
    }
  }
  
  eski_karakter = key;
}





