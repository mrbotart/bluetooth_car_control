#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// New "Easy-to-Find" Pins
const int IN1 = 18; 
const int IN2 = 19; 
const int IN3 = 21; 
const int IN4 = 22; 

int motorSpeed = 220; 

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Car_NewPins"); 

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopCar();
  Serial.println("Bluetooth Started! Use Pins 18, 19, 21, 22.");
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    
    if (command == 'F') moveForward();
    else if (command == 'B') moveBackward();
    else if (command == 'L') turnLeft();
    else if (command == 'R') turnRight();
    else if (command == 'S') stopCar();
  }
}

void moveForward() {
  analogWrite(IN1, motorSpeed); analogWrite(IN2, 0);
  analogWrite(IN3, motorSpeed); analogWrite(IN4, 0);
}

void moveBackward() {
  analogWrite(IN1, 0); analogWrite(IN2, motorSpeed);
  analogWrite(IN3, 0); analogWrite(IN4, motorSpeed);
}

void turnLeft() {
  analogWrite(IN1, 0); analogWrite(IN2, motorSpeed);
  analogWrite(IN3, motorSpeed); analogWrite(IN4, 0);
}

void turnRight() {
  analogWrite(IN1, motorSpeed); analogWrite(IN2, 0);
  analogWrite(IN3, 0); analogWrite(IN4, motorSpeed);
}

void stopCar() {
  analogWrite(IN1, 0); analogWrite(IN2, 0);
  analogWrite(IN3, 0); analogWrite(IN4, 0);
}