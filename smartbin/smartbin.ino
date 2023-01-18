#include <Servo.h>
Servo myServo; // define servo.

// 1: ultrasonic sensor that is used to measure the amount of trash inside.
// 2: ultrasonic sensor that is used to detect the trash in front of the trash can.
#define ECHOPIN1 13
#define TRIGPIN1 12
#define ECHOPIN2 11
#define TRIGPIN2 10

// The LEDs that represent the trash level. More lights will be on when the trash is higher.
#define LED1 7
#define LED2 6
#define LED3 5
#define LED4 4
#define LED5 3

// duration is what the ultrasonic sensor receive, by using that we can measure the distance.
long duration1, distance1;
long duration2, distance2;

void setup() {
  // ultrasonic sensor 1 setup
  Serial.begin(9600);
  pinMode(ECHOPIN1, INPUT);
  pinMode(TRIGPIN1, OUTPUT);
  // LED setup
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  // ultrasonic sensor 2 setup
  myServo.attach(9); // servo on digital pin 9
  pinMode(ECHOPIN2, INPUT);
  pinMode(TRIGPIN2, OUTPUT);
}

void loop() { 
  // LED control
  digitalWrite(TRIGPIN1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN1, HIGH);
  delayMicroseconds(10);

  digitalWrite(ECHOPIN1, LOW);
  duration1 = pulseIn(ECHOPIN1, HIGH);
  distance1 = int(duration1*0.0344/2);  // equation to measure the distance by using duration
  // the trash can's height is 18cm

  if (distance1 < 20) {
    digitalWrite(LED1, 150);
  } else {
    digitalWrite(LED1, 0);
  }   

  if (distance1 < 16) {
    digitalWrite(LED2, 150);
  } else {
    digitalWrite(LED2, 0);
  }
    
  if (distance1 < 12) {
    digitalWrite(LED3, 150);
  } else {
    digitalWrite(LED3, 0);
  }
  if (distance1 < 8) {
    digitalWrite(LED4, 150);
  } else {
    digitalWrite(LED4, 0);
  }
    
  if (distance1 < 4) {
    digitalWrite(LED5, 150);
  } else {
    digitalWrite(LED5, 0);
  }

  // Servo control
  digitalWrite(TRIGPIN2, LOW);
  delay(2);  
  digitalWrite(TRIGPIN2, HIGH);
  delayMicroseconds(10);  
  digitalWrite(TRIGPIN2, LOW);  
  duration2 = pulseIn(ECHOPIN2, HIGH);  
  distance2 = int(duration2*0.0344/2);  // equation to measure the distance by using duration

  // The lid will only be open when there is trash in front of the trash can and there is space for more trash.
  if (distance2 < 30) {
    if (distance1 > 4) {
      myServo.write(180);  // Turn Servo to open the lid
      delay(3000); // Wait for the user to put trash in 
    }
  } else {
     myServo.write(0); // Close the lid
     delay(50);
  }
}
