/*
 Name:		W08T02.ino
 Created:	4/21/2017 7:36:55 AM
 Author:	coskun
*/
#include <SPI.h>
#include <RFID.h>

String currentCard;
String cardbase[4][3] = { 
							{"150-253-250-74-219", "m", "000"},
							{"195-35-111-133-10", "t", "009"},
							{"44-196-57-213-4 ", "i", "004"},
							{"133-207-38-59-87", "i", "004"}
						};

RFID rf(10,5);
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	SPI.begin(); 
	rf.init();
	//boot signal
	beepBuzzerOK();
	delay(500);
	beepBuzzerFAIL();
}

// the loop function runs over and over again until power down or reset
void loop() {
	currentCard = getCardNo();
	delay(250);

	if (currentCard != "")
	{
		for (int i = 0; i < 4; i++)
		{
			int bakiye = cardbase[i][2].toInt();
			if (cardbase[i][0] == currentCard)
			{
				if(bakiye > 0)
				{
					// Ok to PASS
					beepBuzzerOK();
					if(cardbase[i][1] == "t")
					{
						bakiye -= 3;
						cardbase[i][1] = String(bakiye);
					}
					else if(cardbase[i][1] == "i")
					{
						bakiye -= 1;
						cardbase[i][1] = String(bakiye);
					}
				
					Serial.println("Kalan Bakiyeniz: " + cardbase[i][1]);
				}
				else
				{
					beepBuzzerFAIL();
					Serial.println("Yetersiz bakiye :( ");
				}
			}
			else
			{
				// FAIL to PASS
				beepBuzzerFAIL();
				Serial.println("Geçersiz Kart !!");
			}
		} 

		currentCard = "";
	}
}

void beepBuzzerOK()
{
	//new ok soun
	tone(8, 880);
	delay(135);
	noTone(8);
}

void beepBuzzerFAIL()
{
	//new fail
	tone(8, 880);
	delay(35);
	noTone(8);
	delay(500);
	//old fail sound
	tone(8, 660);
	delay(5);
	tone(8, 880);
	delay(5);
	tone(8, 660);
	noTone(8);
	delay(25);

	tone(8, 660);
	delay(5);
	tone(8, 880);
	delay(5);
	tone(8, 660);
	noTone(8);
	delay(25);

	tone(8, 660);
	delay(5);
	tone(8, 880);
	delay(5);
	tone(8, 660);
	noTone(8);
	delay(25);
}

String getCardNo()
{
	String rslt ="";
	if (rf.isCard())
	{
		while (rf.readCardSerial())
		{
			rslt ="";
			for (int i = 0; i < 5; i++)
			{
				rslt = rslt + "-" + String(rf.serNum[i]);
			} 
			rslt = rslt.substring(1, rslt.length());

			//while(rf.readCardSerial()){}
		}
	}
	return rslt;
}