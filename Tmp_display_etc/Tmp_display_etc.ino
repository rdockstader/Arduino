//declare LCD pins
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 8, 5, 4, 3, 2);

//Declare pins/variables for buttons, LEDs, etc
int switchPin = 7;
int ledPin = 13;
int ledPin2 = 6;
int pinState = LOW;
int clickCount = 0;
int tempPin = A3;

//Declarations for accelerometer
int xPin = A2;
int yPin = A1;
int zPin = A0;
int xRead, xRest, yRead, yRest, zRead, zRest;
int gX, gY, gZ;


//timer variables
int timerSeconds = 0, timerMinute = 0, timerHour = 0, timerDay = 0, timeCount = 0, timerLast = 0;


//temp variables
int tmpRead = 0;
float tmpVoltage = 0, degreesC = 0;
int degreesF = 0;


void setup() 
{
  //begin serial
    Serial.begin(9600);
  
  //setup LCD display
  lcd.begin(16, 2);

  //Setup LEDs, switch, and temp
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(tempPin, INPUT);

  //setup Accelerometer
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(zPin, INPUT);

  digitalWrite(ledPin2, HIGH);
  delay(2000);
  xRest = analogRead(xPin);
  yRest = analogRead(yPin);
  zRest = analogRead(zPin);
  Serial.print("X resting value: ");
  Serial.print(xRest);
  Serial.print(" Y resting value: ");
  Serial.print(yRest);
  Serial.print(" Z resting value: ");
  Serial.println(zRest);
  digitalWrite(ledPin2, LOW);
}


void loop() 
{
  timer();
  switchBacklight();
  getXYZ();
  readTemp();
  
  //Uncomment to print coordinates
  //printXYZ();
  //Uncomment to print direction
  printDirection(); 
  printTime();
  printTemp();
}












void switchBacklight()
{
    int value = digitalRead(switchPin);
  if(value == 1)
  {
    pinState = !pinState;
    digitalWrite(ledPin, pinState);
    delay(100);
  }
}

void timer()
{
    int timeCount = (millis() / 1000);

  if(timerLast != timeCount)
  {
    ++timerSeconds;
    timerLast = timeCount;
  }
  if(timerSeconds >= 60)
  {
    timerSeconds = 0;
  }


  if(timeCount%60 == 0 && timeCount > 0)
  {
    timerMinute = (millis() / 60000) ;
  }
  if(timerMinute%60 == 0 && timerMinute > 0)
  {
    ++timerHour;
  }
  if(timerHour%24 == 0 && timerHour > 0)
  {
    ++timerDay;
  }
}

void getXYZ()
{
    //loop for Accelerometer
  xRead = analogRead(xPin) - xRest;
  yRead = analogRead(yPin) - yRest;
  zRead = analogRead(zPin) - zRest;

  gX = xRead * 1.232876712328767;
  gY = yRead * 1.232876712328767;
  gZ = zRead * 1.232876712328767;
}

void printXYZ()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X:");
  lcd.print(gX);
  lcd.setCursor(6, 0);
  lcd.print("Y:");
  lcd.print(gY);
  lcd.setCursor(15,0);
  lcd.print(" ");
  lcd.setCursor(11, 0);
  lcd.print(" Z:");
  lcd.println(gZ);

    /* USER FOR SERIAL OURPUT
  Serial.print("Gyroscope X: ");
  Serial.print(gX);
  Serial.print(" Y: ");
  Serial.print(gY);
  Serial.print(" Z: ");
  Serial.println(gZ);
  delay(100);
  */
}

void printDirection()
{
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("          ");
  lcd.setCursor(0,0);
  if(gX > 15)
  {
    
    lcd.print("Top");
    
    //Serial.println("Top");
  }
  else if(gX < -15)
  {
    lcd.print("Bottom");
    
    //Serial.println("Bottom");
  }
  else if(gY > 15)
  {
    lcd.print("Left");
    
    //Serial.println("Left");
  }
  else if(gY < -15)
  {
    lcd.print("Right");
    
    //Serial.println("Right");
  }
  else
  {
    lcd.print("Flat");
    
    //Serial.println("Flat");
  }
}


void printTime()
{
  lcd.setCursor(0, 1);
  lcd.print("UpTm:");
  lcd.print(timerHour);
  lcd.print(":");
  lcd.print(timerMinute);
  lcd.print(":");
  lcd.print(timerSeconds);  
  delay(100);

    /* USE FOR SERIAL OUTPUT
    Serial.print("Seconds: ");
  Serial.print(timerSeconds);
  Serial.print(" Minutes: ");
  Serial.print(timerMinute);
  Serial.print(" Hours: ");
  Serial.println(timerHour);
  */
}


//int tmpRead = 0, tmpVoltage = 0, degreesC = 0, degreesF = 0;

void readTemp()
{
  tmpRead = analogRead(tempPin);
  tmpVoltage = ((tmpRead * 5.0)/1024.4);
  degreesC = (tmpVoltage - 0.5) * 100;
  degreesF = (degreesC * (9.0/5.0)) + 32;
}

void printTemp()
{
  //NO WORK!!!!!
  lcd.setCursor(12, 0);
  lcd.print("F:");
  lcd.print(degreesF);
  
  Serial.print("F:");
  Serial.println(degreesF);
}











