#include <Servo.h>

// Pins
int trigPin = 9;
int echoPin = 10;

int greenLED = 2;
int yellowLED = 3;
int redLED = 4;
int buzzer = 6;

Servo myServo;   // create servo object

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  myServo.attach(5); // servo signal pin

  Serial.begin(9600);
}

void loop() {
  // Send ultrasonic signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance
  distance = duration * 0.034 / 2;

  Serial.println(distance);

  // Reset everything
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  noTone(buzzer);

  // 🟢 SAFE (>50cm)
  if (distance > 50) {
    digitalWrite(greenLED, HIGH);
    myServo.write(0);   // 0°
  }

  // 🟡 CAUTION (20–50cm)
  else if (distance > 20) {
    digitalWrite(yellowLED, HIGH);
    myServo.write(90);  // middle

    tone(buzzer, 1000);
    delay(500);
    noTone(buzzer);
    delay(500);
  }

  // 🔴 DANGER (5–20cm)
  else if (distance > 5) {
    digitalWrite(redLED, HIGH);
    myServo.write(140);

    tone(buzzer, 2000);
    delay(200);
    noTone(buzzer);
    delay(200);
  }

  // 🚨 CRITICAL (<5cm)
  else {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, HIGH);
    myServo.write(180);

    tone(buzzer, 3000); // continuous
  }

  delay(50); // small stability delay
}