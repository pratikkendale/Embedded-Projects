#define MOTOR1_IN1 2
#define MOTOR1_IN2 5
#define MOTOR2_IN1 16
#define MOTOR2_IN2 17

#define LEFT_IR_SENSOR_PIN 13
#define RIGHT_IR_SENSOR_PIN 19

void setup() {
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);
  pinMode(MOTOR2_IN1, OUTPUT);
  pinMode(MOTOR2_IN2, OUTPUT);

  pinMode(LEFT_IR_SENSOR_PIN, INPUT);
  pinMode(RIGHT_IR_SENSOR_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  int leftIrState = digitalRead(LEFT_IR_SENSOR_PIN);
  int rightIrState = digitalRead(RIGHT_IR_SENSOR_PIN);

  Serial.print("Left IR Sensor: ");
  Serial.print(leftIrState);
  Serial.print(" | Right IR Sensor: ");
  Serial.println(rightIrState);

  if (leftIrState == LOW && rightIrState == LOW) {
    moveForward();
  } else if (rightIrState == HIGH && leftIrState == LOW) {
    turnLeft();
  } else if (leftIrState == HIGH && rightIrState == LOW) {
    turnRight();
  } else if (leftIrState == HIGH && rightIrState == HIGH) {
    moveBackward();
  }

  delay(100);
}

void moveForward() {
  digitalWrite(MOTOR1_IN1, HIGH);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR2_IN1, HIGH);
  digitalWrite(MOTOR2_IN2, LOW);
}

void moveBackward() {
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, HIGH);
  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, HIGH);
}

void turnRight() {
  digitalWrite(MOTOR1_IN1, HIGH);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, HIGH);
}

void turnLeft() {
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, HIGH);
  digitalWrite(MOTOR2_IN1, HIGH);
  digitalWrite(MOTOR2_IN2, LOW);
}

void stopCar() {
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, LOW);
  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, LOW);
}
