#include <Servo.h>


Servo myservo2;
const int pingPin = 7;   // Trigger Pin of Ultrasonic Sensor
const int echoPin = 8;   // Echo Pin of Ultrasonic Sensor
const int redLedPin = 4;   // pin for red led
const int greenLedPin = 3;   // pin for green led




void setup()
{
  pinMode(redLedPin , OUTPUT);     //set redLedPin as output
  pinMode(greenLedPin , OUTPUT);    //set greenLedPin as output
  Serial.begin(9600); // Starting Serial Terminal



}

void loop()
{
  long duration, inches, safedistance;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  safedistance = microsecondsTosafedistance(duration);

  Serial.print(safedistance);
  Serial.print("cm");
  Serial.println();
  delay(100);

 // if the safedistancen is less than 30 red light will blink faster 
  if (safedistance <= 30)
  {

    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    delay(100);
    digitalWrite(redLedPin, LOW);


  }

  //else if safedistance is less tha 50 cm and more than 30 cm it will make red light blink at steady rate  
  //so that anyone on this area get some worning to coming in rstricted area
  else if (safedistance < 50 && safedistance > 30)
  {

    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    delay(200);
    digitalWrite(redLedPin, LOW);

  }

  //safedistance more than 50 cm give green light means no one is in restricted area.
  else
  {

    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    delay(500);
    digitalWrite(greenLedPin, LOW);
  }


}

long microsecondsTosafedistance(long microseconds) {
  return microseconds / 29 / 2;
}
