/* Sample Use of realistic Button Controler
 * author : Coskun Caner
 * version: 1.0
*/

#include<Button.h>

Button myButton1;
Button myButton2;
int counter1 = 10, counter2 = 10;
bool a,b;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  
}

// the loop function runs over and over again until power down or reset
void loop() {
  a = (bool) digitalRead(11);
  b = (bool) digitalRead(12);

  myButton1.processButton(a);
  if (myButton1.isPressed())
  {
    counter1++;
  } 
  
  // Or you can use like this
  counter2 = myButton2.processButton(b, counter2);

  Serial.println("C1 : " + String(counter1)); // you can use that   myButton1.Counter;  instead of counter1
  Serial.println("C2: " + String(myButton2.Counter));
  delay(500);
}