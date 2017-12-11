#include <Servo.h>

Servo servoLeft;          // Define left servo
Servo servoRight;         // Define right servo
int readLeft, readRight, error, mtrCtrl;
const float Kp = 1;
const float Ki = 1;
const float Kd = 1;

void setup() { 
  servoLeft.attach(10);  // Set left servo to digital pin 10
  servoRight.attach(9);  // Set right servo to digital pin 9
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
} 

void loop() {            // Loop through motion tests
//  turnRight();
  //look for fire
  delay(500);
  readLeft = analogRead(A4);
  readRight = analogRead(A5);
  Serial.println(readLeft);
  Serial.println(readRight);
  if(readLeft < 1010 | readRight < 1010)
    {
      //calculate error
      error = readLeft - readRight;
      //Serial.println(error);
      //calculate motor control number
      mtrCtrl = error*Kp;
      //Serial.println(mtrCtrl);
      if(mtrCtrl > 90)
      {
        mtrCtrl = 90;
      }
      else if(mtrCtrl < -90)
      {
        mtrCtrl = -90;
      }
      if(error < 0)
      {
        servoLeft.write(0);
        servoRight.write(180+mtrCtrl);
      }
      else
      {
        servoLeft.write(0+mtrCtrl);
        servoRight.write(180);
      }
      if(readLeft < 970 | readRight < 970)
      {
        //turn on fan
        digitalWrite(12, HIGH);
        Serial.print("HIGH");
        digitalWrite(13, HIGH);
      }
      else
      {
        digitalWrite(12,LOW);
        Serial.print("LOW");
        digitalWrite(13, LOW);
      }
    }
  else
  {
    stopRobot();
  }
}

// Motion routines for forward, reverse, turns, and stop
void forward() {
  servoLeft.write(0);
  servoRight.write(180);
}

void reverse() {
  servoLeft.write(180);
  servoRight.write(0);
}

void turnRight() {
  servoLeft.write(180);
  servoRight.write(180);
}
void turnLeft() {
  servoLeft.write(0);
  servoRight.write(0);
}

void stopRobot() {
  servoLeft.write(90);
  servoRight.write(90);
}
