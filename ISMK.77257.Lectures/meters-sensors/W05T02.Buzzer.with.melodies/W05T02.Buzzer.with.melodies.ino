/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W05T02.Meters-Sensors.Buzzer.with.melodies
 *
 * PIR ile anahtarlama kontrolü yapıldı.Devreye bağlanan Buzzer elemandan
 * alarm sinyali üretildi ve butona basılınca alarmın susturlması
 * sağlandı.
 * 
 * Not: Bu devre lamba rölesi yerine LED kullandık.
 */
#define PIR 12
#define BZR 11
#define BTN 13
bool btn,sense,durum=false;

void setup() {
  // put your setup code here, to run once:
  pinMode(BTN,INPUT);
  pinMode(PIR,INPUT);
  pinMode(BZR,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sense = (bool)digitalRead(PIR);
  btn = (bool)digitalRead(BTN);
  
  if(sense)
    durum = true;

  if(durum)
    alert(true);

  if(btn){
    durum=false;
    while(sense){ 
      noTone(BZR); 
      sense = digitalRead(PIR);
    }
  }


  delay(50);
  Serial.println(sense);
}

void alert(bool b){
  if(b)
  {
    tone(BZR,330); //(PIN to play buzzer sound, FREQUENCY for tone)
    delay(500);
    noTone(BZR);   //stop playing sound
    delay(200);
  }
  else{noTone(BZR);}
}

