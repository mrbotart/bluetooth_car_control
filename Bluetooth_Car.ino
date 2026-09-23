#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// ============================================
// L298N MOTOR DRIVER
// ============================================
#define ENA 22
#define IN1 25
#define IN2 26

#define IN3 32
#define IN4 33
#define ENB 23

// ============================================
// IR SENSORS
// ============================================
#define S1 13
#define S2 14
#define S3 34
#define S4 35
#define S5 27

// ============================================
// LIMIT SWITCH
// ============================================
#define CLP 16

// ============================================
// MOTOR SPEED
// ============================================
int motorSpeed = 180;


// ============================================
// SETUP
// ============================================
void setup() {

  Serial.begin(115200);

  // Bluetooth name
  SerialBT.begin("ESP32_ROBOT");

  Serial.println("Bluetooth Started");
  Serial.println("Connect to: ESP32_ROBOT");

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Sensors
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  pinMode(CLP, INPUT);

  stopMotor();
}


// ============================================
// LOOP
// ============================================
void loop() {

  if (SerialBT.available()) {

    char command = SerialBT.read();

    Serial.print("Command: ");
    Serial.println(command);


    // FORWARD
    if (command == 'F' || command == 'f') {

      forward();
      SerialBT.println("FORWARD");
    }


    // BACKWARD
    else if (command == 'B' || command == 'b') {

      backward();
      SerialBT.println("BACKWARD");
    }


    // LEFT
    else if (command == 'L' || command == 'l') {

      turnLeft();
      SerialBT.println("LEFT");
    }


    // RIGHT
    else if (command == 'R' || command == 'r') {

      turnRight();
      SerialBT.println("RIGHT");
    }


    // STOP
    else if (command == 'S' || command == 's') {

      stopMotor();
      SerialBT.println("STOP");
    }
  }
}


// ============================================
// FORWARD
// ============================================
void forward() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}


// ============================================
// BACKWARD
// ============================================
void backward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}


// ============================================
// LEFT
// ============================================
void turnLeft() {

  // Left motor backward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right motor forward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}


// ============================================
// RIGHT
// ============================================
void turnRight() {

  // Left motor forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Right motor backward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}


// ============================================
// STOP
// ============================================
void stopMotor() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
