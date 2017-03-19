/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W03T02.Simple-Circutis.3POT.controlled.RGB.MulticolorLED
 * https://circuits.io/circuits/4363950-w03t02-3pot-controlled-rgb-multicolorled
 * 
 * Bu projede 3 ayrı pottan okunan analog değerler,
 * RGB çokrenkled üzerinde 3 ayrı renk kanalını 
 * kontrol etmek içi kullanıldı
 * 
 * Not: Bu test.te fiziksel devre kullandık. 
 */

int O=12,R=11,B=10,G=9;
int vR,vG,vB;

void setup() {
  // put your setup code here, to run once:
  for (int i=12; i>8 ; i--){ digitalWrite(i,OUTPUT);}
}

void loop() {
  // read data by 10-bit
  vR = analogRead(A0);
  vG = analogRead(A1);
  vB = analogRead(A2);

  digitalWrite(O, HIGH); // fire the anode pin.
  analogWrite(R, 255 - (vR/4));
  analogWrite(G, 255 - (vG/4));
  analogWrite(B, 255 - (vB/4));
}
