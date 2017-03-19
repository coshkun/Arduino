/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W03T03.Simple-Circutis.Button-Controlled-Counter
 * https://circuits.io/circuits/4364626-w03t03-button-controlled-counter
 * 
 * Bu projede butona her bastığımızda parmağımızı çekmesek 
 * dahi bir'er bir'er artan bir sayaç yaptık ve delay fonksiyonu
 * kullanmadan kodumuzu geliştirerek revize ettik.
 * 
 * Not: Bu test.te fiziksel devre ve PULLUP bağlantısı 
 * kullandık. 
 */

int cntr=0;
bool chk = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(12, INPUT);
  Serial.begin(9600);
  digitalWrite(12, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool b = digitalRead(12);
  //Serial.println("Debug:  " + String(b));
  //Serial.println("Debug:  " + String(cntr));
  
  if (b==LOW)
  {
    if (chk == false)
    {
      cntr++;
    Serial.println("Sayaç: " + String(cntr));
    chk = true;
    }
  }
  else
  {
    chk=false;
  }
}
