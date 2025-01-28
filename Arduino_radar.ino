/*
  Arduino-based Radar using Ultrasonic Sensor & Servo Motor
  ---------------------------------------------------------
  This project simulates a radar system using an ultrasonic sensor to measure 
  distances and a servo motor to sweep the sensor across a defined range of angles. 
  The measured distances are sent via Serial communication for visualization 
  in a Processing-based interface.

  Project by: Kitkraft
  Visit us at: https://kitkraft.in
*/

// Includes the Servo library for controlling the servo motor
#include <Servo.h>

// Defines the pins connected to the Ultrasonic Sensor
const int trigPin = 10;  // Trigger pin of the ultrasonic sensor
const int echoPin = 11;  // Echo pin of the ultrasonic sensor

// Variables to store the duration of the pulse and the calculated distance
long duration;  
int distance;  

// Creates a Servo object for controlling the servo motor
Servo myServo;

void setup() {
  // Initializes the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an input

  // Initializes serial communication for debugging and data transfer
  Serial.begin(9600);

  // Attaches the servo motor to pin 12
  myServo.attach(12);
}

void loop() {
  // Rotates the servo motor from 15° to 165°
  for (int i = 15; i <= 165; i++) {  
    myServo.write(i);          // Moves the servo to the current angle
    delay(30);                 // Delays to allow stable sensor readings

    distance = calculateDistance(); // Calculates the distance at the current angle

    // Sends the angle and distance to the Serial Monitor in the format: angle,distance.
    Serial.print(i);           // Sends the current angle
    Serial.print(",");         // Adds a comma separator
    Serial.print(distance);    // Sends the measured distance
    Serial.print(".");         // Adds a period to mark the end of the data
  }

  // Rotates the servo motor back from 165° to 15°
  for (int i = 165; i > 15; i--) {  
    myServo.write(i);          // Moves the servo to the current angle
    delay(30);                 // Delays to allow stable sensor readings

    distance = calculateDistance(); // Calculates the distance at the current angle

    // Sends the angle and distance to the Serial Monitor
    Serial.print(i);           
    Serial.print(",");         
    Serial.print(distance);    
    Serial.print(".");         
  }
}

// Function to calculate the distance measured by the ultrasonic sensor
int calculateDistance() { 
  digitalWrite(trigPin, LOW);  // Clears the trigPin to ensure no previous pulse
  delayMicroseconds(2);        // Short delay for stabilization
  digitalWrite(trigPin, HIGH); // Sets the trigPin HIGH for 10 microseconds to send a pulse
  delayMicroseconds(10);       // Waits for the pulse to complete
  digitalWrite(trigPin, LOW);  // Stops the pulse

  // Reads the duration of the echo pulse in microseconds
  duration = pulseIn(echoPin, HIGH); 

  // Converts the duration into distance (in cm)
  distance = duration * 0.034 / 2; 
  return distance;             // Returns the calculated distance
}
