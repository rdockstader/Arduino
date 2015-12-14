// ***********************************************************
// Example Accelerometer code
// Last mod: 12/14/2015
//***********************************************************


//Pin delaration
int xPin = A2; //x lead goes to analog 2
int yPin = A1; //y lead goes to analog 1
int zPin = A0; // z lead goes to analog 0
int xRead, xRest, yRead, yRest, zRead, zRest; //variables for the readout of each pin, as well as the resting position
int gX, gY, gZ; //gyro variables


int ledPin = 13; //declare 13(the built in LED on the uno) as ledpin

void setup()
{
  //Declare pins as inputs, not necessarily needed but explicit is generally getter then implicit
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(zPin, INPUT);
  //output to ledPin
  pinMode(ledPin, OUTPUT);

  //begin serial
  Serial.begin(9600);

  
  digitalWrite(ledPin, HIGH); //turn on LED so we know not to move the accelerometer, as we are setting the resting position.
  delay(2000); //wait two seconds just in case you want to change the resting position
  xRest = analogRead(xPin); //set xrest
  yRest = analogRead(yPin); //set yrest
  zRest = analogRead(zPin); //set zrest

  //pring out resting values to the screen
  Serial.print("X resting value: ");
  Serial.print(xRest);
  Serial.print(" Y resting value: ");
  Serial.print(yRest);
  Serial.print(" Z resting value: ");
  Serial.println(zRest);
  digitalWrite(ledPin, LOW);

}


void loop()
{
  getXYZ(); //runs the loop for the accelerometer
  printXYZ(); //prints the XYZ degress
  printDirection(); //prints the direction the accelerometer is tilting.
}

void getXYZ()
{
   //set current xRead values, for x y and z
  xRead = analogRead(xPin) - xRest;
  yRead = analogRead(yPin) - yRest;
  zRead = analogRead(zPin) - zRest;

  //set the current "degrees" from the resting position for x y and z
  gX = xRead * 1.232876712328767;
  gY = yRead * 1.232876712328767;
  gZ = zRead * 1.232876712328767;
}

void printXYZ()
{
  
  /*
  // use for LCD
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
  */

   // USE FOR SERIAL OURPUT
  Serial.print("Gyroscope X: ");
  Serial.print(gX);
  Serial.print(" Y: ");
  Serial.print(gY);
  Serial.print(" Z: ");
  Serial.println(gZ);
  delay(100);
  
}

void printDirection()
{
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("          ");
  //lcd.setCursor(0,0);
  if(gX > 15)
  {
    
    //lcd.print("Top");
    
    Serial.println("Top");
  }
  else if(gX < -15)
  {
    //lcd.print("Bottom");
    
    Serial.println("Bottom");
  }
  else if(gY > 15)
  {
    //lcd.print("Left");
    
    Serial.println("Left");
  }
  else if(gY < -15)
  {
    //lcd.print("Right");
    
    Serial.println("Right");
  }
  else
  {
    //lcd.print("Flat");
    
    Serial.println("Flat");
  }
}

