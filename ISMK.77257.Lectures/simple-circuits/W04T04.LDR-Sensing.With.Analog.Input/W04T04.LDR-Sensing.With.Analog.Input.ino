/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W04T04.Simple-Circutis.LDR-Sensing.With.Analog.Input
 * https://circuits.io/circuits/4440189-w04t04-ldr-sensing-with-analog-input
 * 
 * Bu projede LDR kullanıp analog girişten deger okuyarak
 * gelen ışıkla lamba kontrolü yaptık.
 * 
 * Not: Bu devre lamba rölesi yerine LED kllandık.
 */

int led = 13;
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int d = analogRead(A0);
  d = map(d,3,508,1,511);
  Serial.println(float(d));
  delay(500);
  
  if(d>200)
    digitalWrite(led,LOW);
  else
    digitalWrite(led,HIGH);
}
