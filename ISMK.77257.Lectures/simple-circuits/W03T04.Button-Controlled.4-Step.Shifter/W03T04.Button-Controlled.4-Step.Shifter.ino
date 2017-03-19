/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W03T04.Simple-Circutis.Button-Controlled.4-Step.Shifter
 * https://circuits.io/circuits/4366789-w03t04-button-controlled-4-step-shifter
 * 
 * Bu projede 4 ayrı LED dizilmiş olup, butona basıldıkça
 * her adımda, soldan sağa dogru LED.lerden ışık geçmesi
 * sağlandı.
 * 
 * Not: Bu test.te fiziksel devre vu PULLUP bağlantısı 
 * kullandık.
 */
int cntr=0;
bool chk = false;
int L1=8,L2=9,L3=10,L4=11;

void setup() {
  // put your setup code here, to run once:
  pinMode(12, INPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool b = digitalRead(12);
  renderButton(b);

  switch (cntr%5){
    case 1:
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
      digitalWrite(L3, LOW);
      digitalWrite(L4, LOW);
      break;
        case 2:
      digitalWrite(L1, LOW);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, LOW);
      digitalWrite(L4, LOW);
      break;
        case 3:
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
      digitalWrite(L3, HIGH);
      digitalWrite(L4, LOW);
      break;
        case 4:
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
      digitalWrite(L3, LOW);
      digitalWrite(L4, HIGH);
      break;
        case 0:
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
      digitalWrite(L3, LOW);
      digitalWrite(L4, LOW);
      break;
    default:
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
      digitalWrite(L3, LOW);
      digitalWrite(L4, LOW);
  }
}

void renderButton(bool b){
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
