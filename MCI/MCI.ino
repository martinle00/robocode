// =======================================================
// ENGG1000 - R2R Group 21
// Motor Controller
// Written by Martin Le November 2020
// Controls motors via an H Bridge
// ======================================================= 
    
// -------------------------------------------------------
// Global Variables
// -------------------------------------------------------
// Initialising Global Variables
int rightMotor1 = 5;
int rightMotor2 = 6;
int leftMotor1 = 9;
int leftMotor2 = 10;

int pwmDutyCycle = 0;
char currentDirection = 'x';
char command = 0;
// -------------------------------------------------------
// Subroutine: Initialize Motor Pins
// -------------------------------------------------------
void initializeMotorPins(){
  
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
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);

}

// -------------------------------------------------------
// Function: Receive Byte
// -------------------------------------------------------
char receiveCommand(char command){
  // when a user inputs a command, it is read and then returned
  if(Serial.available() > 0) {
    command = Serial.read();
    delay(10);
  }
  return command;
}

// -------------------------------------------------------
// Function: Update Direction
// -------------------------------------------------------
char updateDirection(char command, char currentDirection){
    // if user inputs w, the currentDirection is forwards
    if (command == 'w'){
      currentDirection = 'f';
      Serial.println("Forwards");
    }
    // if user inputs s, the currentDirection is backwards
    else if (command == 's') {
      currentDirection = 'b';
      Serial.println("Backwards");
    }
    // if user inputs a, the currentDirection is left
    else if (command == 'a') {
      currentDirection = 'l';
      Serial.println("Turn Left");
    }
    // if user inputs d, the currentDirection is right
    else if (command == 'd') {
      currentDirection = 'r';
      Serial.println("Turn Right");
    }
    // return the direction
    return currentDirection;
}

// -------------------------------------------------------
// Function: Update Speed
// -------------------------------------------------------
int updateSpeed(char command, int pwmDutyCycle){
  
    // Speed Change Commands
    // If command is 0, the pwmDutyCycle will be 0 (non-moving)
    if (command == '0') {
      pwmDutyCycle = 0;
      Serial.println("Stop");
    }
    // If command is 1, the pwmDutyCycle will be 10% of 255 (26)
    else if (command == '1') {
      pwmDutyCycle = 26;
      Serial.println("Speed = 10%");
    }
    // If command is 2, the pwmDutyCycle will be 20% of 255 (51)
    else if (command == '2') {
      pwmDutyCycle = 51;
      Serial.println("Speed = 20%");
    }
    // If command is 3, the pwmDutyCycle will be 30% of 255 (77)
    else if (command == '3') {
      pwmDutyCycle = 77;
      Serial.println("Speed = 30%");  
    }
    // If command is 4, the pwmDutyCycle will be 40% of 255 (102)
    else if (command == '4') {
      pwmDutyCycle = 102;
      Serial.println("Speed = 40%");  
    }
    // If command is 5, the pwmDutyCycle will be 50% of 255 (128)
    else if (command == '5') {
      pwmDutyCycle = 128;
      Serial.println("Speed = 50%");  
    }
    // return the newly set pwmDutyCycle
    return pwmDutyCycle;
}
  
// -------------------------------------------------------
// Subroutine: Set Motor Pins
// -------------------------------------------------------
void setMotorPins(char currentDirection, int pwmDutyCycle){

    // Resetting Pins
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);

    // case where currentDirection is either forwards or turn right
    // leftMotor2 will be configured with the pwmDutyCycle to go appropriate direction
    if (currentDirection == 'f' || currentDirection == 'r') {
      analogWrite(leftMotor2, pwmDutyCycle);
    }
    // case where currentDirection is either backwards or turn left
    // leftMotor1 will be configured with the pwmDutyCycle to go appropriate direction
    if (currentDirection == 'b' || currentDirection == 'l') {
      analogWrite(leftMotor1, pwmDutyCycle); 
    }
    // case where currentDirection is either forwards or turn left
    // rightMotor2 will be configured with the pwmDutyCycle to go appropriate direction
    if (currentDirection == 'f' || currentDirection == 'l') {
      analogWrite(rightMotor2, pwmDutyCycle);
    }
    // case where currentDirection is either backwards or turn right
    // rightMotor1 will be configured with the pwmDutyCycle to go appropriate direction
    if (currentDirection == 'b' || currentDirection == 'r') {
      analogWrite(rightMotor1, pwmDutyCycle);
    }  
}

// -------------------------------------------------------
// Function: Help Information
// -------------------------------------------------------

void helpPrompt() {
    Serial.println("Welcome to the help desk!");
    Serial.println("-------------------------------------");
    Serial.println("Directional Inputs");
    Serial.println("w - move forward");
    Serial.println("a - move left");
    Serial.println("s - move right");
    Serial.println("d - move backwards");
    Serial.println("---------------------------");
    Serial.println("Speed Inputs");
    Serial.println("0 - set speed to 0");
    Serial.println("1 - set speed to 10%");
    Serial.println("2 - set speed to 20%");
    Serial.println("3 - set speed to 30%");
    Serial.println("4 - set speed to 40%");
    Serial.println("5 - set speed to 50%");
    Serial.println("-------------------------------------");
    Serial.println("Functional Inputs");
    Serial.println("r - return autonomously");
    Serial.println("x - terminate the program");
    Serial.println("-------------------------------------");
}


void setup() {
  Serial.begin(9600);
  
  // Introductory Statements
  Serial.println("-------------------------------------");
  Serial.println("Program: Controlling Motors");
  Serial.println("Initialising ...");
  initializeMotorPins();
  Serial.println("Initialisation complete");
  Serial.println("-------------------------------------");
  helpPrompt();
}

void loop() {
  bool keyboardControl = true;
  
  // Control the motors from the keyboard
  while (keyboardControl) {
    
    // Wait for a command from the keyboard
    command = receiveCommand(command); 
    
    // Update the direction of the robot
    currentDirection = updateDirection(command, currentDirection);
    
    // Update the speed of the robot
    pwmDutyCycle = updateSpeed(command, pwmDutyCycle);
    
    // Set the motor pins according to speed and direction
    setMotorPins(currentDirection, pwmDutyCycle);
    
    // Was this an exit command
    if (command == 'x') keyboardControl = false;
    
    if (command == 'h') {
        helpPrompt();
    }
  }
  
  // Terminate the program
 Serial.println("The robot will not be taking any more requests");
 while(true);

}
