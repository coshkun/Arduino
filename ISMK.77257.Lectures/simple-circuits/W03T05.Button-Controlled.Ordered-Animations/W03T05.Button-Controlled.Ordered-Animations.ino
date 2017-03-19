/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W03T05.Simple-Circutis.Button-Controlled.Ordered-Animations
 * https://circuits.io/circuits/4367148-w03t05-button-controlled-ordered-animations
 * 
 * Bu projede 4 ayrı LED dizilmiş olup, butona her basıldıkça
 * her adımda, LED.lerin değişik animasyoklar yapması sağlanmıştır.
 * 
 * Not: Bu test.te fiziksel devre kullandık. 
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
  int secenek = cntr %5;

  switch (secenek){
  case 1:
    //Animasyon1
    an_anim1();
    break;
  case 2:
    //Animasyon2
    an_anim2();
    break;
  case 3:
    //Animasyon3
    an_anim3();
    break;
  case 4:
    //Animasyon4
    for(int i=0;i<4;i++){an_anim4();}
    break;
  case 0:
    an_hepsiniSondur();
    break;
  default:
    an_hepsiniSondur();
    break;
  }
}

//Animasyonlar:
void an_hepsiniSondur(){
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
      digitalWrite(L3, LOW);
      digitalWrite(L4, LOW);
}

void an_hepsiniYak(){
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(L3, HIGH);
      digitalWrite(L4, HIGH);
}

void an_anim1(){
  for (int i=0;i<4;i++){
      digitalWrite(L1+i,HIGH);
      delay(50);
    }
  for (int i=0;i<4;i++){
      digitalWrite(L1+i,LOW);
      delay(50);
    }
}

void an_anim2(){
  for (int i=0;i<4;i++){
      digitalWrite(L4-i,HIGH);
      delay(50);
    }
  for (int i=0;i<4;i++){
      digitalWrite(L4-i,LOW);
      delay(50);
    }
}

void an_anim3(){
  for (int i=0;i<4;i++){
      an_hepsiniYak();
      delay(50);
      an_hepsiniSondur();
      delay(50);
    }
}

void an_anim4(){
  for (int i=0;i<4;i++){
    if (i%2 == 0)
      digitalWrite(L1+i,HIGH);
    else
      digitalWrite(L1+i,LOW);
    }
    delay(100);
    an_hepsiniSondur();
  for (int i=0;i<4;i++){
    if (i%2 == 1)
      digitalWrite(L1+i,HIGH);
    else
      digitalWrite(L1+i,LOW);
    }
    delay(100);
    an_hepsiniSondur();
}

//Butona Bak:
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

