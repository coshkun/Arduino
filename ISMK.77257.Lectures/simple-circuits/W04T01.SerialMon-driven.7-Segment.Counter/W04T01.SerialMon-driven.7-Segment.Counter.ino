/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W04T01.Simple-Circutis.SerialMon-driven.7-Segment.Counter
 * https://circuits.io/circuits/4412499-w04t01-serialmon-driven-7-segment-counter
 * 
 * Bu projede 7-segment gösterge kullandık, seri monitörden
 * gönderilen her sayı için 0-9 arası degerler gösterdik.
 * 
 * Not: Bu devre display'imiz olmadığı için simülaterde kuruldu.
 */

int cntr=0, s = -1;
bool chk = false;

// int a=0,b=1,c=2,d=3,e=4,f=5,g=6;
int gosterge[10][7]= {
                     //a, b, c, d, e, f, g
                      {0, 0, 0, 0, 0, 0, 1},  // 0
                      {1, 0, 0, 1, 1, 1, 1},  // 1
                      {0, 0, 1, 0, 0, 1, 0},  // 2
                      {0, 0, 0, 0, 1, 1, 0},  // 3
                      {1, 0, 0, 1, 1, 0, 0},  // 4
                      {0, 1, 0, 0, 1, 0, 0},  // 5
                      {0, 1, 0, 0, 0, 0, 0},  // 6
                      {0, 0, 0, 1, 1, 1, 1},  // 7
                      {0, 0, 0, 0, 0, 0, 0},  // 8
                      {0, 0, 0, 0, 1, 0, 0}   // 9
                     };
                      
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=2;i<9;i++) {pinMode(i,OUTPUT);}
  SayiGoster(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  s = Serial.parseInt();
  Serial.println(s);
  
  if(s != -1){SayiGoster(s); s = -1;}
}

void SayiGoster(int a){
  if (a>=0 && a<=9)
  {
    for(int j=2;j<9;j++)
    {
      digitalWrite(j, gosterge[a][j-2]);
    }
  }
  else
  {
    for(int j=2;j<9;j++)
    {
      digitalWrite(j, HIGH);
    }
  }
}

