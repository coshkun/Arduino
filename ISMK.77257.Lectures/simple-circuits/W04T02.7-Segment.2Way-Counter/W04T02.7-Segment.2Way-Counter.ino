/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W04T02.Simple-Circutis.7-Segment.2Way-Counter
 * https://circuits.io/circuits/4413194-w04t02-7-segment-2way-counter
 * 
 * Bu projede 7-segment gösterge kullandık, iki butondan 
 * biri degerleri arttırmak, digeri azaltmak için PULLDOWN
 * yöntemi ile bağlandı
 * 
 * Not: Bu devre display'imiz olmadığı için simülaterde kuruldu.
 */
int cntr=0;
bool btn1 = false;
bool btn2 = false;

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
  //Serial.begin(9600);
  for(int i=0;i<7;i++) {pinMode(i,OUTPUT);}
  pinMode(11, INPUT);pinMode(12, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool yukselt = digitalRead(11);
  bool alcalt  = digitalRead(12);
  yukseltButton(yukselt);
  alcaltButton(alcalt);

  for(int j=0;j<8;j++)
  {
    digitalWrite(j, gosterge[(cntr%10)][j]);
  }

  delay(200);
}

//Butona Bak:
void yukseltButton(bool b){
  if (b==HIGH)
  {
    if (btn1 == false)
    {
      cntr++;
    btn1 = true;
    }
  }
  else
  {
    btn1=false;
  }
}
//Butona Bak:
void alcaltButton(bool b){
  if (b==HIGH)
  {
    if (btn2 == false)
    {
      cntr--;
      if(cntr==-1){cntr=99;}
    btn2 = true;
    }
  }
  else
  {
    btn2=false;
  }
}
