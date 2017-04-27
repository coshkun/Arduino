/*
  Name:    ARadarMC.Arduino.Based.Ulra-Sonic.Radar.MC-Unit
  File Name: ARadarMC.ino
  Created: 4/16/2017 8:12:51 PM
  Author:  coskun
*/
#include <IRremote.h>
#include <IRremoteInt.h>

unsigned long int durum;
int infrared_giris = 13, LEDPin = 12, Volume = 0;
IRrecv irrecv(infrared_giris);
decode_results sonuc;
bool LED = false, yukari_durum = false, asagi_durum = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  digitalWrite(LEDPin, LED);
  //Serial.println("Volume: +" + String(Volume));//Debug

  // put your main code here, to run repeatedly:
  if (irrecv.decode(&sonuc)) {
    durum = sonuc.value;
    Serial.println(durum, HEX); //Debug
    if (durum == 0xFF02FD) // ok tusu
    {
      LED = !LED;
    }
    if (durum == 0xFF629D) //yukarı ses
    {
      yukari_durum == true;
    }
    if ( (durum == 0xFFFFFFFF) && yukari_durum == true) {
      durum = sonuc.value;
      Volume++;
      Serial.println("Volume: +" + String(Volume));
      yukari_durum = false;
    }

    if (durum == 0xFFA857) //asagi ses
    {
      asagi_durum == true;
    }
    if ( (durum == 0xFFFFFFFF) && asagi_durum == true) {
      Volume--;
      Serial.println("Volume: +" + String(Volume));
      asagi_durum = false;
    }


    irrecv.resume();
  }
}
