
#define SERIAL_BUFFER_SIZE 256

String s="";
bool isReading =false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Booting..");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0 || isReading)
  {
    if(s.length() < 94)
      isReading = true;
    else
      isReading = false;

    Serial.println("Flag: " + String(isReading));
    Serial.println("Length: " + String(s.length()));
    
    if(isReading)
    {
      s = Serial.readString();
      //Serial.println(s);
    }
    
  }
  
  if(isReading == false){
    Serial.println(s);
    delay(1000);
  }
}
