/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W02T01.Simple-Circutis.Reading.Analog.Values
 * https://circuits.io/circuits/4255625-w02t01-reading-analog-values
 * 
 * Bu projede pot.tan okunan gerilim değeri, 
 * 0-1023 bit aralığında degerler üretmektedir. 
 * Çıktılar, serial monitörden izlenmektedir.
 */

int deger;

void setup() {
  //pinMode(4, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  deger = analogRead(A0);
  Serial.println(deger);
}

