#include <Stepper.h>
#define led1 12 //RED
#define led2 11 //YELLOW
#define led3 10 //GREEN
#define buzzer 9

#define level1 25 //RED 25
#define level2 35 //YELLOW & GREEN 35

const int trigPin = 2;
const int echoPin = 3;
long duration;
int distanceCm, distanceInch;

const float STEPS_PER_REV = 4;
int Speed = 3500;         //Enter Speed
int stepsRequired = 1000; //Enter Step
int temp;
boolean rotateF = true;  //Open
boolean rotateR = false; //Close

Stepper stepperMotor(STEPS_PER_REV, 4, 6, 5, 7);

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(echoPin, INPUT);
  stepperMotor.setSpeed(Speed);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  //distanceInch = duration*0.0133/2;
  Serial.print(distanceCm);
  Serial.print("\n");

  if (distanceCm >= level2)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(buzzer, LOW);
  }
  else if (distanceCm < level2 && distanceCm > level1)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(buzzer, HIGH);
  }
  else if (distanceCm <= level1)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(buzzer, LOW);
  }

  if (rotateF && distanceCm <= level1)
  {
    digitalWrite(13, HIGH);
    temp = stepsRequired;
    stepperMotor.step(temp);
    rotateF = false;
    rotateR = true;
  }
  else if (rotateR && distanceCm > level1)
  {
    digitalWrite(13, HIGH);
    temp = -stepsRequired;
    stepperMotor.step(temp);
    rotateF = true;
    rotateR = false;
  }
  digitalWrite(13, LOW);
  delay(1000);
}
