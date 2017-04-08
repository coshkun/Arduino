/*
  Button.cpp - Library for realistic button behaviour.
  Created by Coskun Caner, Appril 8, 2017.
  Licensed under MIT-1.0, free for commercial and personal use.
  Released into the public domain.
  Version 1.0
*/

#include "Arduino.h"
#include "Button.h"

Button::Button(void)
{
    /*btn_number=0;*/
    is_pressed = false;
    ButtonState = false;
    Name = "UNNAMED_BUTTON";
    Counter = 0;
}

// This sends only one TRUE value on user's tap time,
// than immediately return FALSE even button is still pressed.
bool Button::isPressed(void)
{
    return is_pressed;
}

// Sample: processButton(digitalRead(pinNo));
void Button::processButton(bool val){ 
  if (val==true)
  {
    if (ButtonState == false)
    {
        ButtonState = true;
        is_pressed = true;
        Counter++;
        return;
    }
    is_pressed = false;
  }
  else
  {
    ButtonState= false;
  }
}

int Button::processButton(bool val, int counter){
  if (val==true)
  {
    if (ButtonState == false)
    {
        ButtonState = true;
        is_pressed = true;
        Counter = ++counter;
        return;
    }
    is_pressed = false;
  }
  else
  {
    ButtonState= false;
  }

  return counter;
}