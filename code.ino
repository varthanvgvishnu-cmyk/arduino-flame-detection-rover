
/*
  Project: Arduino Flame Detection Rover
  Board: Arduino Uno

  Flame sensors:
    Left  -> D11
    Front -> D12
    Right -> D13

  L298N motor driver:
    IN1 -> D5
    IN2 -> D6
    IN3 -> D9
    IN4 -> D10

  Water pump relay:
    IN -> D7

  Sensor logic:
    LOW  = Flame detected
    HIGH = No flame detected
*/

const int LEFT_FLAME   = 11;
const int FRONT_FLAME  = 12;
const int RIGHT_FLAME  = 13;

const int IN1 = 5;
const int IN2 = 6;
const int IN3 = 9;
const int IN4 = 10;

const int PUMP_RELAY = 7;

// Change to false if your relay activates with HIGH.
const bool RELAY_ACTIVE_LOW = true;

void setup() {
  pinMode(LEFT_FLAME, INPUT);
  pinMode(FRONT_FLAME, INPUT);
  pinMode(RIGHT_FLAME, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set the relay to OFF before enabling its output.
  digitalWrite(PUMP_RELAY, RELAY_ACTIVE_LOW ? HIGH : LOW);
  pinMode(PUMP_RELAY, OUTPUT);

  Serial.begin(9600);

  stopRover();
  pumpOff();

  Serial.println("Flame Detection Rover Ready");
}

void loop() {
  bool leftFire  = (digitalRead(LEFT_FLAME) == LOW);
  bool frontFire = (digitalRead(FRONT_FLAME) == LOW);
  bool rightFire = (digitalRead(RIGHT_FLAME) == LOW);

  Serial.print("Left: ");
  Serial.print(leftFire);
  Serial.print(" | Front: ");
  Serial.print(frontFire);
  Serial.print(" | Right: ");
  Serial.println(rightFire);

  // Front flame: stop and activate the pump.
  if (frontFire) {
    stopRover();
    pumpOn();
    Serial.println("Front flame: Pump ON");
  }
  // Flame detected only on the left.
  else if (leftFire && !rightFire) {
    pumpOff();
    turnLeft();
    Serial.println("Left flame: Turning LEFT");
  }
  // Flame detected only on the right.
  else if (rightFire && !leftFire) {
    pumpOff();
    turnRight();
    Serial.println("Right flame: Turning RIGHT");
  }
  // Ambiguous detection: stop for safety.
  else {
    stopRover();
    pumpOff();

    if (leftFire && rightFire) {
      Serial.println("Flame detected on both sides");
    } else {
      Serial.println("No flame: Rover STOPPED");
    }
  }

  delay(100);
}

// Both motors move forward.
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Pivot left.
void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Pivot right.
void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Stop both motors.
void stopRover() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void pumpOn() {
  digitalWrite(PUMP_RELAY, RELAY_ACTIVE_LOW ? LOW : HIGH);
}

void pumpOff() {
  digitalWrite(PUMP_RELAY, RELAY_ACTIVE_LOW ? HIGH : LOW);
}
