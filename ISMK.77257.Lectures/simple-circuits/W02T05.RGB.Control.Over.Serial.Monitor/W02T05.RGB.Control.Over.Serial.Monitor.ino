/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W02T05.Simple-Circutis.RGB.Control.Over.Serial.Monitor
 * https://circuits.io/circuits/4270259-w02t05-rgb-control-over-serial-monitor
 * 
 * Bu projede serial monitör.den girilen komutlar ile seçilen 
 * rengin RGB (çok-renkli) led üzerinde tonlaması yapılmıştır. 
 * PWM çıkış elde edebilmek amacıyla 'analogWrite()' kullanılmıştır.
 * 
 * Not: Bu test.te simulator arızası yüzünden fiziksel devre 
 * kullandık. Kullandığımız RGB ortak anotlu olması sebebiyle 
 * HIGH degeri için 0, LOW degeri için 255 çıkış degerleri 
 * kullanıldı.
 */
 
int R=11, G=10, B=9;
String oku;

void setup() {
  Serial.begin(9600);
  pinMode(R, OUTPUT); 
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {
  oku = Serial.readString();
  if(oku=="RED"||oku=="red"){
    analogWrite(R, 0); delay(500); oku = "";
    }
  else if(oku=="GREEN"||oku=="green"){
    analogWrite(G, 0); delay(500); oku = "";
    }
  else if(oku=="BLUE"||oku=="blue"){
    analogWrite(B, 0); delay(500); oku = "";
    }
  else{
    analogWrite(R, 255);
    analogWrite(G, 255);
    analogWrite(B, 255);
    }
}
