#include <Servo.h>  // Include the Servo library

// Define pins for the ultrasonic sensor
const int trigPin = 10;
const int echoPin = 11;

// Variables for distance measurement
long duration;
int distance;

// Create Servo object
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);  // trigPin as output
  pinMode(echoPin, INPUT);   // echoPin as input
  Serial.begin(9600);       // Start serial communication at 9600 baud
  myServo.attach(12);       // Attach the servo to pin 12
}

void loop() {
  // Sweep from 15 to 165 degrees
  for (int angle = 15; angle <= 165; angle++) {
    myServo.write(angle);
    delay(30);
    distance = calculateDistance();
    
    // Send data in "angle,distance." format
    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
  
  // Sweep from 165 back to 15 degrees
  for (int angle = 165; angle >= 15; angle--) {
    myServo.write(angle);
    delay(30);
    distance = calculateDistance();
    
    // Send data in "angle,distance." format
    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

// Function to calculate distance from ultrasonic sensor
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;  // Convert to cm
  return distance;
}
