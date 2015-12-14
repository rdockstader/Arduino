#include <AFMotor.h>
#include <Servo.h>

//ping
const int trigPin = 19;
const int echoPin = 18;
long duration, inches;


//Servo
Servo servo1;


//Dc Motors
AF_DCMotor leftMotor(4);
AF_DCMotor rightMotor(3);
int curSpeed = 255;
const int maxSpeed = 255;
const int minSpeed = 0;

void setup() 
{
  //DC Motors
  leftMotor.setSpeed(curSpeed);
  rightMotor.setSpeed(curSpeed);
  leftMotor.run(RELEASE);
  leftMotor.run(RELEASE);

  //servo
  servo1.attach(9);

  //ping
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  //pause for 10 seconds before begining loop
  delay(10000);
}


void loop() 
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

bool footCheck()
{
  ping();
  if(inches <= 12)
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
  if(servo1.read() != 90)
  {
    servo1.write(90);
  }
  goForward = footCheck();
  return goForward;
  
}

bool canGoLeft()
{
  bool goLeft = false;
  servo1.write(180);
  goLeft = footCheck();
  servo1.write(90);
  return goLeft;
}
bool canGoRight()
{
  bool goRight = false;
  servo1.write(0);
  goRight = footCheck();
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

//Motor Test

void motortest()
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



