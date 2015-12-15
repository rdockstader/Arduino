// *******************************************************************
// Analog TMP sensor Example
// Last modified: 12/14/2015
// *******************************************************************



//temp variables
int tmpRead = 0;
float tmpVoltage = 0, degreesC = 0;
int degreesF = 0;
int tempPin = A3;

void setup() 
{
    pinMode(tempPin, INPUT);
}

void loop() 
{
  readTemp();
  printTemp();
  delay(1000);
}

void readTemp()
{
  tmpRead = analogRead(tempPin);
  tmpVoltage = ((tmpRead * 5.0)/1024.4);
  degreesC = (tmpVoltage - 0.5) * 100;
  degreesF = (degreesC * (9.0/5.0)) + 32;
}

void printTemp()
{
  //LCD
  //lcd.setCursor(12, 0);
  //lcd.print("F:");
  //lcd.print(degreesF);

  //Serial print
  Serial.print("F:");
  Serial.println(degreesF);
}
