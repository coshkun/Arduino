/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W03T01.Simple-Circutis.POT.Value-Reading.Over.Serial.Monitor
 * https://circuits.io/circuits/4363867-w03t01-pot-value-reading-over-serial-monitor
 * 
 * Bu projede serial monitör.den kulanıcının ayarladığı pot
 * üzerinden voltaj seviyesi okunarak SM.den cıktı alınır.
 * 
 * Not: Bu test.te simulator arızası yüzünden fiziksel devre 
 * kullandık. 
 */
int val = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
val = analogRead(A0);
Serial.print("Potun degeri: ");
Serial.println(String(val* 10/1024) + " Kohm");
}
