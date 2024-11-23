// Define IO pins for motor control
#define PWMA 5    // Controls power to right motor
#define PWMB 6    // Controls power to left motor
#define AIN 7     // Controls direction of right motor, HIGH = FORWARD, LOW = REVERSE
#define BIN 8     // Controls direction of left motor, HIGH = FORWARD, LOW = REVERSE
#define STBY 3    // Place H-Bridge in standby if LOW, Run if HIGH

// Define IO pins for ultrasonic sensor
#define TRIG 13   // Trigger pin for ultrasonic sensor
#define ECHO 12   // Echo pin for ultrasonic sensor

// Define constants
#define DISTANCE_THRESHOLD 20  // Distance threshold in cm to detect obstacles
#define TURN_DURATION 300      // Duration for turning in milliseconds
#define REVERSE_DURATION 300   // Duration for reversing in milliseconds
#define FORWARD_SPEED 64      // Speed for forward movement (0 to 255)

// Initialize the car
void setup() {
  // Motor setup
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN, OUTPUT);
  pinMode(BIN, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  // Ultrasonic sensor setup
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Debugging setup
  Serial.begin(9600);
}

// Main loop
void loop() {
  int distance = measureDistance();

  if (distance > 0 && distance < DISTANCE_THRESHOLD) {
    Serial.print("Obstacle detected at: ");
    Serial.print(distance);
    Serial.println(" cm");

    reverseAndTurn(); // Avoid obstacle
  } else {
    Serial.print("Clear path. Distance: ");
    Serial.println(distance);
    moveForwardSlow(); // Continue moving forward
  }
}

// Measure distance using the ultrasonic sensor
int measureDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 20000L);  // 20ms timeout
  if (duration == 0) return 999;               // No echo received, assume large distance
  return (duration * 0.034) / 2;
}

// Move forward slowly
void moveForwardSlow() {
  analogWrite(PWMA, FORWARD_SPEED);
  analogWrite(PWMB, FORWARD_SPEED);
  digitalWrite(AIN, HIGH);
  digitalWrite(BIN, HIGH);
}

// Reverse and turn to avoid obstacles
void reverseAndTurn() {
  // Reverse for a short duration
  analogWrite(PWMA, FORWARD_SPEED);
  analogWrite(PWMB, FORWARD_SPEED);
  digitalWrite(AIN, LOW);  // Reverse right motor
  digitalWrite(BIN, LOW);  // Reverse left motor
  delay(REVERSE_DURATION);

  // Turn clockwise
  analogWrite(PWMA, FORWARD_SPEED);
  analogWrite(PWMB, FORWARD_SPEED);
  digitalWrite(AIN, HIGH);
  digitalWrite(BIN, LOW);
  delay(TURN_DURATION);

  stopMotors();
}

// Stop the motors
void stopMotors() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}
