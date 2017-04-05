/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W05T05.Meters-Sensors.Ultrasonic.Piano
 *
 * Ultrasonic-Sensor ile notalar arası mesafe ölcen piano
 * 
 */
#include <Ultrasonic.h>
#define BZR 10

Ultrasonic usonic(8,9,23200);  // (Trig PIN,Echo PIN, TimeOut)
int mesafe=0; int tune=300;
               //do, re, mi, fa,sol, la, si, do
int nota[] = {0,523,587,659,698,784,880,988}; // +585

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(BZR, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  mesafe = usonic.Ranging(CM);
  //Serial.print(usonic.Ranging(CM)); // CM or INC
  //Serial.println(" cm" );
  int range = map(mesafe, 10, 70, 0, 10);

  switch(range){
        case 0:
        notaCal(nota[range], tune);
    break;
        case 1:
        notaCal(nota[range], tune);
    break;
        case 2:
        notaCal(nota[range], tune);
    break;
        case 3:
        notaCal(nota[range], tune);
    break;
        case 4:
        notaCal(nota[range], tune);
    break;
        case 5:
        notaCal(nota[range], tune);
    break;
        case 6:
        notaCal(nota[range], tune);
    break;
        case 7:
        notaCal(nota[range], tune);
    break;
        default:
        notaCal(nota[0], tune);
  }

  Serial.println(mesafe);
  delay(100);
}

void notaCal(int nota, int latency){
  if(nota<1){noTone(BZR); return;}
  unsigned long duration=150;
  for(int i=0; i<latency; i++){
    duration -= i;
    tone(BZR, nota, duration);
  }
  //noTone(BZR);
}

