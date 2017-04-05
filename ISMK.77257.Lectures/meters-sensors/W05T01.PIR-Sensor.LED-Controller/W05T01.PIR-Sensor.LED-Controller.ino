/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W05T01.Meters-Sensors.PIR-Sensor.LED-Controller
 * https://circuits.io/circuits/4501198-w05t01-pir-sensor-led-controller
 *
 * PIR ile anahtarlama kontrolü yapıldı.
 * 
 * Not: Bu devre lamba rölesi yerine LED kullandık.
 */

#define LED 12
#define PIR 8
bool sensor;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
  //Debug
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor = digitalRead(PIR);

  if(sensor){
    digitalWrite(LED, HIGH);
    //Debug
    Serial.println(sensor);
  }
  else{
    digitalWrite(LED, LOW);
    //Debug
    Serial.println(sensor);
  }
}


