/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W02T02.Simple-Circutis.Orientation.on.Analog.Values
 * https://circuits.io/circuits/4255895-w02t02-orientation-on-analog-values
 * 
 * Analog girişlerde ortalama almak üzere iki adet pot.tan 
 * gelen degerler okunarak, denkleme girilir. 
 * Cikişlar, serial monitörden gözlemlenir.
 */

int a;
int b;
int c;


void setup() {
  // initialize the digital pin as an output.
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  a = analogRead(A0);
  b = analogRead(A1);
  c = (a+b)/2;
  Serial.println(c);
  delay(500);
}

