/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W05T04.Meters-Sensors.Ultrasonic.Parking-Helper
 *
 * Problem:
 * Ultrasonic-Sensor ile mesafe ölçen ve metraja
 * göre alarmda ton değiştiren park yardımcısını
 * yazınız.
 * 
 * Not: Bu devre iki pinli Ultrasonik ve hazır kütüphane
 * kullandık.
 */
#include <Ultrasonic.h>
#define BZR 10

Ultrasonic usonic(8,9,23200);  // (Trig PIN,Echo PIN, TimeOut)
int mesafe=0;
int nota[3] = {330,220,110};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(BZR, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  mesafe = usonic.Ranging(CM);
  Serial.print(usonic.Ranging(CM)); // CM or INC
  Serial.println(" cm" );

  if(mesafe > 50 && mesafe < 200)
    alarmVer(nota[2], 3);
  else if(mesafe > 10 && mesafe < 50)
    alarmVer(nota[1], 3);
  else if(mesafe > 4 && mesafe < 10)
    alarmVer(nota[0], 3);
  else
    noTone(BZR);
  
  delay(100);
}

void alarmVer(int nota, int tekrar){
  for(int i=0; i<tekrar; i++){
    tone(BZR, nota);
    delay(50);
    noTone(BZR);
    delay(25);
  }
}

