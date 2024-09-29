#include <AccelStepper.h>
#include <CytronMotorDriver.h>
#include <Servo.h>
#include <Wire.h>

Servo myServo;
int servoPin = 9;
int angle = 0;

CytronMD motorL(PWM_DIR, 5, 4);
CytronMD motorR(PWM_DIR, 6, 7);

volatile bool startCommand = false;  // Flag to control the loop execution

void setup() {
  motorL.setSpeed(0);
  motorR.setSpeed(0);
  myServo.attach(servoPin);
  myServo.write(0);

  pinMode(A1, OUTPUT);

  Serial.begin(9600);

  // Initialize I2C communication as Slave
  Wire.begin(8);  // Set the I2C address to 8
  Wire.onReceive(receiveEvent);  // Define the function that will be triggered when data is received


  
}

void loop() {

  
  if (startCommand) {
    delay(4000);
    // Move forward
    motorL.setSpeed(-80);
    motorR.setSpeed(-80);
    delay(2500);

    // Stop for a short period
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(2000);

    // Rotate the servo continuously clockwise (CW)
    for (angle = 0; angle <= 180; angle += 1) {
      myServo.write(angle);
      delay(15);
    }
    delay(3000);

    // Rotate the servo continuously counter-clockwise (CCW)
    for (angle = 180; angle >= 0; angle -= 1) {
      myServo.write(angle);
      delay(15);
    }
    
    delay(3000);


  digitalWrite(A1, HIGH);
  delay(3000);
  digitalWrite(A1, LOW);

      // Stop for a short period again
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(3000);


    // Move backward
    motorL.setSpeed(80);
    motorR.setSpeed(80);
    delay(2000);

    // Stop for a short period again
    motorL.setSpeed(0);
    motorR.setSpeed(0);
    delay(5000);


    //motorL.setSpeed(-400);
    //motorR.setSpeed(400);
    //delay(3000);

    //motorL.setSpeed(0);
    //motorR.setSpeed(0);
    //delay(5000);
    // Reset the startCommand flag
    startCommand = false;
  }
}

// This function will be called whenever the Uno receives data from the Mega
void receiveEvent(int howMany) {
  while (Wire.available()) {
    int receivedData = Wire.read();
    if (receivedData == 1) {
      startCommand = true;  // Set flag to true to start the loop in the next iteration
    }
  }
}
