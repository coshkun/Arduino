/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W02T03.Simple-Circutis.Analog.Level.Indicating.Leds
 * https://circuits.io/circuits/4256316-w02t03-analog-level-indicating-leds
 * 
 * Bu projede, pot ile girilen analog seviye okunarak, led.ler 
 * üzerinde seviye göstergesi yapılmıştır. Konunun amacı, 
 * karar yapıları kullanılarak, if - else if - else yapılarının 
 * kullanımı ve karşılaştırma operatörlerinden 
 * istifade edilmesidir.
 */

int ana;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  for(int i = 7; i >3; i--) {
    pinMode(i, OUTPUT);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  ana = analogRead(A0);
  Serial.println(ana);
  //   0-250 arası 1 led
  if(ana <251)
  {
    digitalWrite(7, HIGH);
    
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
  }
  // 250-500 arası 2 led
  else if(ana > 250 && ana < 501)
  {
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
    
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
  }
  // 500-750 arası 3 led
  else if(ana > 500 && ana < 751)
  {
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
    
    digitalWrite(4, LOW);
  }
  // 750-... 4 led
  else if(ana > 750)
  {
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
  }
}
