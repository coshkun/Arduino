/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W01T02.Simple-Circutis.Walking.4.Leds
 * https://circuits.io/circuits/4186002-w01t02-walking-4-leds
 * 
 */

// give it a name:
int led4 = 7;
int led3 = 6;
int led2 = 5;
int led1 = 4;
int gecik =75;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led1, HIGH);
  delay(gecik);               
  digitalWrite(led2, HIGH);   
  delay(gecik);
  digitalWrite(led3, HIGH); 
  delay(gecik);            
  digitalWrite(led4, HIGH);   
  delay(gecik);  
  digitalWrite(led4, LOW);
  delay(gecik);  
  digitalWrite(led3, LOW);
  delay(gecik); 
  digitalWrite(led2, LOW);
  delay(gecik); 
  digitalWrite(led1, LOW); 
  delay(gecik+300); 
}
