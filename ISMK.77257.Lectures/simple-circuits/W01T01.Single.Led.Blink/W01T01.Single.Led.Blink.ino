/*
 * ISM.77257.Lectures
 * @author: coskun
 * 
 * W01T01.Simple-Circutis.Blink
 * https://circuits.io/circuits/4185064-w01t01-single-led-blink
 * 
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 6;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
