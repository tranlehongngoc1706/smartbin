#include <LiquidCrystal.h>
#include <Servo.h>

// 1: ultrasonic sensor for detecting the nearby object to open the lid 
// 2: ultrasonic sensor for measuring the trash's height inside the bin

Servo myservo;

// ultrasonic sensors' pins
const int trigPin1 = 5;
const int echoPin1 = 6;
const int trigPin2 = 10;
const int echoPin2 = 13;

// LED pin
const int REDPin = 2;

// Lcd screen
// LiquidCrystal lcd(12, 11,8, 7, 4, 3);

// define variables
long duration1, duration2;
int distance1, distance2;
int trashCanHeight = 25;

void setup() {
  Serial.begin(9600); // starts the serial communication

  // trigPin: OUTPUT, echoPin: INPUT
  pinMode(trigPin1, OUTPUT);  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin1, INPUT);  
  pinMode(echoPin2, INPUT); 

  pinMode(REDPin,OUTPUT);


  myservo.attach(9);
}

void loop() {
  
  // Detecting the nearby object to open the lid 
  digitalWrite(trigPin2,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = int(duration1 *0.034/2);

  // Measuring the trash's height inside the bin
  // Clears the trigPin
  digitalWrite(trigPin2,LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2,LOW);

  // read the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2,HIGH);

  // Calculating the distance
  distance2 = int(duration2*0.0344/2);

  if (distance2 <= 5){
    digitalWrite(REDPin,HIGH);
    Serial.print("Distance: ");
    Serial.println("Out of range");
    // lcd.print("The trash can is ");
    // lcd.print(((trashCanHeight-distance2)/trashCanHeight)*100); 
    // lcd.println("% full");
    // lcd.print("Please empty it!"); 
    delay(1000);   
  } else {
    digitalWrite(REDPin,LOW);
    // lcd.print("The trash can is ");
    // lcd.print(((trashCanHeight-distance2)/trashCanHeight)*100); 
    // lcd.println("% full"); 
    // lcd.print("The trash can is available!");
    delay(1000); 
    // // Print the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance2);
    Serial.println("cm");
  }

 if (distance1 <= 50 && distance1 >= 0 && distance2 > 5) 
  {	
  myservo.write(50);    
  delay(3000);
  } else {		
  myservo.write(160);
  }  
  
delay(500);  
// lcd.clear();
}
