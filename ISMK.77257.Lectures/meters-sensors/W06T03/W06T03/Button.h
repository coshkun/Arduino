#ifndef Button_h
#define	Button_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#pragma once
class Button
{
private:
	/*static unsigned int btn_number;*/
	bool is_pressed;
public:
	bool ButtonState;
	String Name;
	int Counter;


	Button(void)
	{
		/*btn_number=0;*/
		is_pressed = false;
		ButtonState = false;
		Name = "UNNAMED_BUTTON";
		Counter = 0;
	}

	~Button(void)
	{
	}
	
	// This sends only one TRUE value on user's tap time,
	// than immediately return FALSE even button is still pressed.
	bool isPressed(void)
	{
		return is_pressed;
	}

	// Sample: processButton(digitalRead(pinNo));
	void processButton(bool val){ 
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

	int processButton(bool val, int counter){
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
};

#endif