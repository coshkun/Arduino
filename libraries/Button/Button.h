/*
  Button.h - Library for gettin realistic button actions into your code.
  Created by Coskun Caner, April 8, 2017. Licensed under MIT.v.1.0
  Released into the public domain.
  ver.1.0.0
*/
#ifndef Button_h
#define	Button_h

#include "Arduino.h"

#pragma once
class Button
{
private:
	static unsigned int btn_number;
	bool is_pressed;
public:
	bool ButtonState; // This holds the initial state of your button
	String Name; // You can give a special name to your button
	int Counter; // Initial HitCounter of your button
    
    // Default Constractor with no params
	Button(void);
	
	// This sends only one TRUE value on user's tap time,
	// than immediately return FALSE even button is still pressed.
	bool isPressed(void);

	// Sample: processButton(digitalRead(pinNo));
	void processButton(bool val);
    // Sample: processButton(digitalRead(pinNo), myHitCounter);
	int processButton(bool val, int counter);
};

#endif