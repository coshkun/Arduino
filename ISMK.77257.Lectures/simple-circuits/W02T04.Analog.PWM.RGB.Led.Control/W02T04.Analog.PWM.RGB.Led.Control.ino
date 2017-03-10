/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W02T04.Simple-Circutis.Analog.PWM.RGB.Led.Control
 * https://circuits.io/circuits/4269939-w02t04-analog-pwm-rgb-led-control
 * 
 * Bu projede PWM sinyali üreterek analog çıkış olarak üç pin 
 * belirledik. (çok renkli) RGB led, yardımıyla analog 
 * çıkışları renk kodlarına çevirdik. RGB led.i polis çakarı 
 * yapacak şekilde 2-kırmızı 3-mavi renlerde programladık. 
 */

int R = 11;
int B = 10;
int G = 9;

// the setup routine runs once when you press reset:
void setup(){
    pinMode(R, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(G, OUTPUT);
  }

// the loop routine runs over and over again forever:
void loop() 
{
 // Kırmızı Çakar
 analogWrite(R,255);
 analogWrite(B,0);
 analogWrite(G,0);
 delay(150);
 analogWrite(R,0);
 analogWrite(B,0);
 analogWrite(G,0);
 delay(150);
 analogWrite(R,255);
 analogWrite(B,0);
 analogWrite(G,0);
 delay(150);
 analogWrite(R,0);
 analogWrite(B,0);
 analogWrite(G,0);
 delay(200);
 // Mavi Çakar
 analogWrite(R,1);
 analogWrite(B,255);
 analogWrite(G,1);
 delay(150);
 analogWrite(R,0);
 analogWrite(B,0);
 analogWrite(G,0);
 delay(150);
 analogWrite(R,0);
 analogWrite(B,255);
 analogWrite(G,0);
 delay(150);
 analogWrite(R,0);
 analogWrite(B,0);
 analogWrite(G,0);
 delay(150);
 analogWrite(R,0);
 analogWrite(B,255);
 analogWrite(G,0);
 delay(150);
 analogWrite(R,0);
 analogWrite(B,0);
 analogWrite(G,0);
 delay(200);
}
