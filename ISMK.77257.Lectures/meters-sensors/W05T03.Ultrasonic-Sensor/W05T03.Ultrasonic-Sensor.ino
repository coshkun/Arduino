/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W05T03.Meters-Sensors.Ultrasonic-Sensor
 * https://circuits.io/circuits/4522738-w05t03-ultrasonic-sensor-distance-measuring
 *
 * Ultrasonic-Sensor ile mesafe ölçümü yapıldı.
 * Bizdeki mesafe sensörlerini sürebilmek için,
 * sensörün data-sheet'inde gösterilen kütüphane
 * koda eklenmştir.(https://github.com/JRodrigoTech/Ultrasonic-HC-SR04)
 * 
 * Not: Bu devre iki pin.li mesafe sensörü kullandık.
 * simülatördeki mesafe sönsüründe, okuma yazma bacakları 
 * aynı olduğundan, simülatöre eklenen kodda farklılıklar 
 * gözlemlenebilir.
 */
#include <Ultrasonic.h>

Ultrasonic usonic(8,9,23200);  // (Trig PIN,Echo PIN)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(usonic.Ranging(CM)); // CM or INC
  Serial.println(" cm" );
  delay(100);
}
