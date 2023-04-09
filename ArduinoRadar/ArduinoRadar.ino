#include <Servo.h>
#define SERVO 3
#define SERVODELAY 100
#define TRIGGER 4 
#define ECHO 5
#define RED 7
#define GREEN 6
#define BLUE 8

Servo servo;
unsigned int servoPos = 0;
bool servoDirection = true;
unsigned long previousMillisServo = 0;
 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(SERVO);
  pinMode(TRIGGER,OUTPUT);
  pinMode(ECHO,INPUT);
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  digitalWrite(TRIGGER,LOW);
}

void moveServo() {
  servo.write(servoPos);
  if (servoDirection) {
    if (++servoPos == 180) servoDirection = false;
  }
  else {
    if (--servoPos == 0) servoDirection = true;
  }
}

unsigned long sensorDistance() {
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  unsigned long t = pulseIn(ECHO, HIGH);
  return t/59;
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisServo >= SERVODELAY) {
    previousMillisServo = currentMillis;
    moveServo();
    unsigned long d = sensorDistance();
    if (d < 200) {
      digitalWrite(RED,HIGH);
      digitalWrite(GREEN,LOW);
      digitalWrite(BLUE,LOW);
    }
    else if (d < 500) {
      digitalWrite(RED,HIGH);
      digitalWrite(GREEN,HIGH);
      digitalWrite(BLUE,LOW);
    }
    else if (d < 800) {
      digitalWrite(RED,LOW);
      digitalWrite(BLUE,HIGH);
      digitalWrite(GREEN,HIGH);
    }
    else {
      digitalWrite(GREEN,HIGH);
      digitalWrite(BLUE,LOW);
      digitalWrite(RED,LOW);
    }
    Serial.print("Distance: ");
    Serial.print(d);
    Serial.print("cm\n");
  }
}
