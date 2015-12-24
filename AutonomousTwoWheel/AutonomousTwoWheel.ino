//AFMotor.h will need to be downloaded. Instructions/Link to download @ https://learn.adafruit.com/adafruit-motor-shield/library-install
#include <AFMotor.h>
#include <Servo.h>

//ping
const int trigPin = 19;
const int echoPin = 18;
long duration, inches;
int checkDistance = 6; //adjusting this int will adjust the distance the ping sensor will check before stopping the car.


//Servo
Servo servo1;
Servo servo2;


//Dc Motors (using the AFMotor library from adafruit)
AF_DCMotor leftMotor(4);
AF_DCMotor rightMotor(3);
int curSpeed = 255;
const int maxSpeed = 255;
const int minSpeed = 0;
int beginDelay = 5; //delay in seconds prior to starting loop.

void setup() 
{
  //DC Motors
  leftMotor.setSpeed(curSpeed);
  rightMotor.setSpeed(curSpeed);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);

  //servo
  servo1.attach(10);
  servo2.attach(9);

  //ping
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  //Serial.begin(9600);
  //Serial.println("Serial begin");

  //pause for 10 seconds before begining loop
  delay(beginDelay*1000);
}


void loop() 
{
  //uncomment to test motors
  //motorTest();
  //uncomment to run without servo usage
  basicCarMovement();
  //uncomment to run with servo usage
  //advancedCarMovement();
}

//Car Movements

void motorTest()
{
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  delay(5000);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  delay(3000);
  leftMotor.run(BACKWARD);
  rightMotor.run(BACKWARD);
  delay(5000);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  delay(3000);
}

void basicCarMovement()
{
    ping();

  if(inches <= 12)
  {
     carStop();
     delay(1000);
     turnLeft();  
  }
  else
  {
    moveForward();
  }
}


void advancedCarMovement()
{
    if(canGoForward())
  {
    moveForward();
  }
  else
  {
    carStop();
    if(canGoLeft())
    {
      turnLeft();
    }
    else if(canGoRight())
    {
      turnRight();
    }
    else
    {
      moveBackward();
      delay(2000);
      carStop();
      if(canGoLeft())
      {
        turnLeft();
      }
      else
      {
        turnRight();
      }
    }
  }
}

//ping functions

void ping()
{
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  inches = microsecondsToInches(duration);
}

long microsecondsToInches(long microseconds) 
{ 
  return microseconds / 74 / 2; 
} 

bool pingCheck()
{
  ping();
  if(inches >= checkDistance) //set in global variables at the top of file
  {
    return true; 
  }
  else
  {
    return false;
  }
}

bool canGoForward()
{
  bool goForward = false;
  //if(servo1.read() != 90)
  //{
  //  servo1.write(90);
  //}
  delay(100);
  goForward = pingCheck();
  return goForward;
  
}

bool canGoLeft()
{
  bool goLeft = false;
  servo1.write(180);
  delay(1000);
  goLeft = pingCheck();
  servo1.write(90);
  return goLeft;
}
bool canGoRight()
{
  bool goRight = false;
  servo1.write(0);
  delay(1000);
  goRight = pingCheck();
  servo1.write(90);
  return goRight;
}


//basic car functions

void moveForward()
{
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
}

void moveBackward()
{
  leftMotor.run(BACKWARD);
  rightMotor.run(BACKWARD);
}

void carStop()
{
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
}

void setCurSpeed(int sp)
{
  if(sp > maxSpeed)
  {
    curSpeed = maxSpeed;
  }
  else if(sp < minSpeed)
  {
    curSpeed = minSpeed;
  }
  else
  {
    curSpeed = sp;
  }
  
  leftMotor.setSpeed(curSpeed);
  rightMotor.setSpeed(curSpeed);
}


//left Turns

void turnLeft()
{
  leftMotor.setSpeed(maxSpeed);
  rightMotor.setSpeed(maxSpeed);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  leftMotor.run(BACKWARD);
  rightMotor.run(FORWARD);
  delay(200);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  leftMotor.setSpeed(curSpeed);
  rightMotor.setSpeed(curSpeed);
}

void turnLeft180()
{
  leftMotor.setSpeed(maxSpeed);
  rightMotor.setSpeed(maxSpeed);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  leftMotor.run(BACKWARD);
  rightMotor.run(FORWARD);
  delay(400);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  leftMotor.setSpeed(curSpeed);
  rightMotor.setSpeed(curSpeed);
}

void turnLeft360()
{
  leftMotor.setSpeed(maxSpeed);
  rightMotor.setSpeed(maxSpeed);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  leftMotor.run(BACKWARD);
  rightMotor.run(FORWARD);
  delay(800);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  leftMotor.setSpeed(curSpeed);
  rightMotor.setSpeed(curSpeed);
}

//right turns

void turnRight()
{
  leftMotor.setSpeed(maxSpeed);
  rightMotor.setSpeed(maxSpeed);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  leftMotor.run(FORWARD);
  rightMotor.run(BACKWARD);
  delay(200);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  leftMotor.setSpeed(curSpeed);
  rightMotor.setSpeed(curSpeed);
}

void turnRight180()
{
  leftMotor.setSpeed(maxSpeed);
  rightMotor.setSpeed(maxSpeed);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  leftMotor.run(FORWARD);
  rightMotor.run(BACKWARD);
  delay(400);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  leftMotor.setSpeed(curSpeed);
  rightMotor.setSpeed(curSpeed);
}

void turnRight360()
{
  leftMotor.setSpeed(maxSpeed);
  rightMotor.setSpeed(maxSpeed);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  leftMotor.run(FORWARD);
  rightMotor.run(BACKWARD);
  delay(800);
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  leftMotor.setSpeed(curSpeed);
  rightMotor.setSpeed(curSpeed);
}
