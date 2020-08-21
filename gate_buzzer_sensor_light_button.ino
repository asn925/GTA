#include <Servo.h>

Servo myservo;

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 8; // Echo Pin of Ultrasonic Sensor
const int redLedPin = 4; // pin for red led
const int greenLedPin = 3; // pin for green led
const int buzzer = 11;  // pin for buzzer
const int buttonPin = 12;  //pin for button


int gateopen = 90;    // angle of servo for open gate
int buttonState = 0;     //buttonstate

void setup()
{
  pinMode(redLedPin , OUTPUT);        //set redLedPin as output
  pinMode(greenLedPin , OUTPUT);       //set greenLedPin as output
  pinMode(buzzer, OUTPUT);             //set buzzer Pin as output
  pinMode(buttonPin, INPUT);            //set button Pin as output
  myservo.attach(10);                  // attach servo at pin 10

  Serial.begin(9600); // Starting Serial Terminal
}

void loop() {
  long duration, inches, safedistance;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  buttonState = digitalRead(buttonPin);

  safedistance = microsecondsTosafedistance(duration);

  Serial.print(safedistance);
  Serial.print("cm");
  Serial.println();
  delay(100);



  myservo.write(gateopen);   //make gate open at 90 degree angle

  // if the safedistancen is less than 30 and button is not pressed red light will blink faster and buzzer will on at high hertz
  if (safedistance <= 20 && buttonState == HIGH)
  {
    tone(buzzer, 4000, 500);
    digitalWrite(buzzer, HIGH);
    gateopen = 0;
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    delay(100);
    digitalWrite(redLedPin, LOW);

  }
  //else if safedistance is less tha 50 cm and more than 30 cm it will make red light blink at steady rate an buzzer will on at normal hertz
  //so that anyone on this area get some worning to coming in rstricted area

  else if (safedistance < 35 && safedistance> 20 && buttonState == HIGH)
  {
    tone(buzzer, 500, 500);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    delay(200);
    digitalWrite(redLedPin, LOW);

  }
  //safedistance more than 50 cm give green light means no one is in restricted area.
  else if (safedistance > 35   && buttonState == HIGH)
  {
    digitalWrite(buzzer, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    delay(500);
    digitalWrite(greenLedPin, LOW);
  }
  
  //if button is pressed means it will open gate again if an autorized  thing come in area
  else if (buttonState == LOW)
  {
    gateopen = 90;
  }
}

long microsecondsTosafedistance(long microseconds) {
  return microseconds / 29 / 2;
}
