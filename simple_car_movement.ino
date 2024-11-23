// define IO pin
// Needs motor driver module
#define PWMA 5    // Controls power to right motor
#define PWMB 6    // Controls power to left motor
#define AIN 7     // Controls direction of right motor, HIGH = FORWARD, LOW = REVERSE
#define BIN 8     // Controls direction of left motor, HIGH = FORWARD, LOW = REVERSE
#define STBY 3    // Place H-Bridge in standby if LOW, Run if HIGH

// Initialize the car
void setup() {
  pinMode(PWMA, OUTPUT);     // Set IO pin mode OUTPUT for right motor power
  pinMode(PWMB, OUTPUT);     // Set IO pin mode OUTPUT for left motor power
  pinMode(AIN, OUTPUT);      // Set IO pin mode OUTPUT for right motor direction
  pinMode(BIN, OUTPUT);      // Set IO pin mode OUTPUT for left motor direction
  pinMode(STBY, OUTPUT);     // Set IO pin mode OUTPUT for standby control
  digitalWrite(STBY, HIGH);  // Enable Motors to run
  digitalWrite(PWMA, LOW);   // Fully on for right motor
  digitalWrite(PWMB, LOW);   // Fully on for left motor
}

// Main loop
void loop() {
  delay(500);  // Wait 0.5 seconds before moving

  // Move forward for 0.5 seconds
  moveForward(500);

  // Move backward for 0.5 seconds
  moveBackward(500);

  // Turn clockwise for 0.5 seconds
  turnCounterClockwise(500);

  // Turn counterclockwise for 0.5 seconds
  turnClockwise(500);

  // Stop for 0.5 seconds
  stopTime(500);
}

// Move forward for a specified duration in milliseconds
void moveForward(int duration) {
  digitalWrite(AIN, HIGH);  // Set right motor direction to forward
  digitalWrite(BIN, HIGH);  // Set left motor direction to forward
  digitalWrite(PWMA, HIGH); // Power right motor to full speed
  digitalWrite(PWMB, HIGH); // Power left motor to full speed
  delay(duration);          // Move for the specified duration
  stopMotors();             // Stop motors after movement
}

// Move backward for a specified duration in milliseconds
void moveBackward(int duration) {
  digitalWrite(AIN, LOW);   // Set right motor direction to reverse
  digitalWrite(BIN, LOW);   // Set left motor direction to reverse
  digitalWrite(PWMA, HIGH); // Power right motor to full speed
  digitalWrite(PWMB, HIGH); // Power left motor to full speed
  delay(duration);          // Move for the specified duration
  stopMotors();             // Stop motors after movement
}

// Turn clockwise for a specified duration in milliseconds
void turnClockwise(int duration) {
  digitalWrite(AIN, LOW);  // Set right motor direction to reverse
  digitalWrite(BIN, HIGH);   // Set left motor direction to forward
  digitalWrite(PWMA, HIGH); // Power right motor to full speed
  digitalWrite(PWMB, HIGH); // Power left motor to full speed
  delay(duration);          // Turn for the specified duration
  stopMotors();             // Stop motors after movement
}

// Turn counterclockwise for a specified duration in milliseconds
void turnCounterClockwise(int duration) {
  digitalWrite(AIN, HIGH);   // Set right motor direction to forward
  digitalWrite(BIN, LOW);  // Set left motor direction to reverse
  digitalWrite(PWMA, HIGH); // Power right motor to full speed
  digitalWrite(PWMB, HIGH); // Power left motor to full speed
  delay(duration);          // Turn for the specified duration
  stopMotors();             // Stop motors after movement
}

// Stop the motors for a specified duration in milliseconds
void stopTime(int mS) {
  digitalWrite(STBY, LOW);  // Go into standby mode
  delay(mS);                // Wait for the specified time
  digitalWrite(STBY, HIGH); // Come out of standby mode
}

// Stop both motors
void stopMotors() {
  digitalWrite(PWMA, LOW);  // No power to right motor
  digitalWrite(PWMB, LOW);  // No power to left motor
}
