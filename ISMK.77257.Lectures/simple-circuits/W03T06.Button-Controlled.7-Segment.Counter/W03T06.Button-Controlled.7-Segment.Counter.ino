/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W03T06.Simple-Circutis.Button-Controlled.7-Segment.Counter
 * https://circuits.io/circuits/4350641-w03t06-button-controlled-7-segment-counter
 * 
 * Bu projede 7-segment gösterge kullandık, butona her basıldıkça
 * her adımda, sayacı 0-9 arası degerlerde 1 arttırarak göstergeden
 * rakamları görüntüledik.
 * 
 * Not: Bu devre display'imiz olmadığı için simülaterde kuruldu.
 * PULLDOWN button kullandık.
 */
int cntr=0;
bool chk = false;

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
  for(int i=0;i<7;i++) {pinMode(i,OUTPUT);}
  pinMode(12,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool b = digitalRead(12);
  renderButton(b);
  
  for(int i=0;i<10;i++){
    if((cntr%10)==i)
    {
      for(int j=0;j<8;j++)
      {
        digitalWrite(j, gosterge[i][j]);
      }
    }
  }
}

//Butona Bak:
void renderButton(bool b){
  if (b==HIGH)
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


