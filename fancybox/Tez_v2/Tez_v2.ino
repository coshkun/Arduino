#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
#include <EEPROM.h>

#define _BUZZER_ 13
#define _GASS_ 12
#define _PIR_ 2
#define _SERVO_ 4
#define _KAPAT_BUTTON_ 3

//Flags
bool FIRST_BOOT = false;   // <- ilk çalıştırmada burası true yapılarak kurum işlemi yapılır.
bool ALARM_DURUM = false;
bool YANGIN_DURUM = false;
bool HIRSIZ_DURUM = false;
bool SIFRE_HAZIR_DURUM = false;
bool ARMED = false;


// RS,E,D4,D5,D6,D7
//LiquidCrystal lcd(6, 7, 8, 9, 10, 11);
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
Servo servo;

// keypad setup
char tus_takimi[4][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte satir_pin[4] = {5, 6, 7, 8};
byte sutun_pin[3] = {9, 10, 11};
Keypad tustakim = Keypad(makeKeymap(tus_takimi), satir_pin, sutun_pin, 4, 3);
int karakterSay = 0;

// sifreler
char sifre[5] = {'1', '4', '0', '4', '7'};
char puk[8] = {'8', '8', '8', '8', '8', '8', '8', '8'};
String guncelSifre = "";
String userInput = "";
// unsigned long sifreSayac = 0;
// int GecikmeSuresi = 3; //sn. cinsinden
int HataliSifreSayisi = 3;

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
    for (int i = 0; i < 5; i++)
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
  AlarmiKur();

  delay(50);

  AlarmCal();
  //sifreSayac = millis();
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

  if (ARMED) { // Savunma Pozisyonu
    if (sensor && !HIRSIZ_DURUM)  //<- Giriş
    {
      /* Gecikme fonsiyonu eklenecek
      if(!SifreyiBekle())
        return; */
      
      // Sifre gelmedi alarm veriyoruz:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("HIRSIZ VAR");
      lcd.setCursor(0, 1);
      lcd.print("enter password:");
      ALARM_DURUM = true;
      HIRSIZ_DURUM = true;
    }
    else if (sensor || HIRSIZ_DURUM)
    {
       if(sifreDogrumu()){
        HIRSIZ_DURUM = false;
        ALARM_DURUM = false;
        ARMED = false;
        HataliSifreSayisi = 3;
      }
      return;
    }
    else if(HIRSIZ_DURUM==false){
       if(sifreDogrumu()){
        // Kapıyı burada acarız:
        ARMED = false;
        HataliSifreSayisi = 3;
        return;
      }
      else{
//       if(userInput.length() < 5)
//            return;
//
//        if ((char)tustakim.getKey() == '#'){
//          if (guncelSifre != userInput)
//            HataliSifreSayisi--;
//            
//          return;
//        }
        
        
        if(HataliSifreSayisi < 1)
          {
            HataliSifreSayisi = 0;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("HIRSIZ VAR");
            lcd.setCursor(0, 1);
            lcd.print("enter password:");
            ALARM_DURUM = true;
            HIRSIZ_DURUM = true;
          }
      }
    }
  }

}

void KeypadOku() {
  char key = (char)tustakim.getKey();

  if (key == NO_KEY)
    return;

  if (key != '#' || key != '*')
    karakterSay++;

  if (YANGIN_DURUM == true && key == '#') {
    ALARM_DURUM = false;
    // YANGIN_DURUM==true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FIRE ALARM");
    lcd.setCursor(0, 1);
    lcd.print("alarm suppresed!");
  }

  if (key == '#')
  {
    // sifre kontrolleri
    if (SIFRE_HAZIR_DURUM == true)
    {
      if (sifreDogrumu())
        Serial.println("Sifre dogru..");
      else{
        HataliSifreSayisi--;
        lcd.clear();
        lcd.print(HataliSifreSayisi);
        lcd.print(" enter pswd:");
        lcd.setCursor(0,1);
        SIFRE_HAZIR_DURUM = false;
        return;
      }

      SIFRE_HAZIR_DURUM = false;
    }
    karakterSay = 0;
    userInput = "";
    lcd.clear();
    if(ARMED)
      lcd.print("ARMED");
    else
      lcd.print("Hazir..");
  }
  else {
    // userInput = "*****";
    if (karakterSay > 0)
    {
      lcd.clear();
      lcd.print("password:");
      lcd.setCursor(0, 1);

      if (userInput.length() < 5) {
        userInput += key;
      }
      else {
        karakterSay = 0;
      }

      lcd.print(userInput);
    }
    if (userInput.length() == 5)
      SIFRE_HAZIR_DURUM = true;
    else
      SIFRE_HAZIR_DURUM = false;
  }



  //Serial.println("Eski: " + String(eski_karakter) + " Key: " + String(key));
  //Serial.println(userInput + " " + String(karakterSay));
}

bool sifreDogrumu() {
  if (guncelSifre == userInput)
    return true;

  return false;
}

void AlarmiKur() {
  if (userInput == "*****") {
    ARMED = true;
    userInput = "";
    lcd.clear();
    lcd.print("ARMED");
    return;
  }
}

/** Experimental use only 
bool SifreyiBekle(){
  
  if(int(sifreSayac / 1000) == GecikmeSuresi){
    sifreSayac = 0;
    return true;
  }

  return false;
} */



