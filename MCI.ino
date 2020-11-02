// =======================================================
// ENGG1000 - Computing Technical Stream
// Motor Controller
// Written by Martin Le October 2020
// Controls motors via an H Bridge 
// ======================================================= 
    
    
// Initialising Motor and Speed Global Variables
int rightMotor1 = 3;
int rightMotor2 = 9;
int leftMotor1 = 10;
int leftMotor2 = 11;
  
int speedPin = 13;
int directionPin = 6;
int pwmDutyCycle;
int motorSpeed = 0;
char currentDirection;


void setup() {
  Serial.begin(9600);
  // Introductory Statements
  Serial.println("Program: Controlling Motors");
  Serial.println("Initialising ...");
  
  // Printing out information on pins
  Serial.print("Right Motor Pin 1  = ");
  Serial.println(rightMotor1);
  Serial.print("Right Motor Pin 2 = ");
  Serial.println(rightMotor2);
  Serial.print("Left Motor Pin 1 = ");
  Serial.println(leftMotor1);
  Serial.print("Left Motor Pin 2 = ");
  Serial.println(leftMotor2);

  // Configure Pins
    
  pinMode(speedPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  Serial.println("Initialisation complete");
}

void loop() {

  char instruction = 0;
  pwmDutyCycle = abs(motorSpeed) * 255 / 100;
  analogWrite(speedPin, pwmDutyCycle);

  // Direction Commands
  if(Serial.available() > 0) {
    instruction = Serial.read();
    if (instruction == 'w'){
      currentDirection = 'f';
      Serial.println("Forwards");
    }
    else if (instruction == 's') {
      currentDirection = 'b';
      Serial.println("Backwards");
    }
    else if (instruction == 'a') {
      currentDirection = 'l';
      Serial.println("Turn Left");
    }
    else if (instruction == 'd') {
      currentDirection = 'r';
      Serial.println("Turn Right");
    }

    // Speed Change Commands
    else if (instruction == '0') {
      pwmDutyCycle = 0;
      Serial.println("Stop");
    }
    else if (instruction == '1') {
      pwmDutyCycle = 0.1 * 255;
      Serial.println("Speed = 10%");
    }
    else if (instruction == '2') {
      pwmDutyCycle = 0.2 * 255;
      Serial.println("Speed = 20%");
    }
    else if (instruction == '3') {
      pwmDutyCycle = 0.3 * 255;
      Serial.println("Speed = 30%");  
    }
    else if (instruction == '4') {
      pwmDutyCycle = 0.4 * 255;
      Serial.println("Speed = 40%");  
    }
    else if (instruction == '5') {
      pwmDutyCycle = 0.5 * 255;
      Serial.println("Speed = 50%");  
    }

    // Resetting Pins
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);

    // Setting Voltage to correct motor to ensure correct direction

    if (currentDirection == 'f' || currentDirection == 'r') {
      analogWrite(leftMotor2, pwmDutyCycle);
    }
    if (currentDirection == 'b' || currentDirection == 'l') {
      analogWrite(leftMotor1, pwmDutyCycle); 
    }
    if (currentDirection == 'f' || currentDirection == 'l') {
      analogWrite(rightMotor2, pwmDutyCycle);
    }
    if (currentDirection == 'b' || currentDirection == 'r') {
      analogWrite(rightMotor1, pwmDutyCycle);
    }
  }
  delay(10);
}
