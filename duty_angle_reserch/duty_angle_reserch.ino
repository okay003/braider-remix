// see this site (step) :
// see this site (dc) : https://aisumegane.com/l298n/

#include <AccelStepper.h>

#define STEP_IN1 4
#define STEP_IN2 5
#define STEP_IN3 6
#define STEP_IN4 7
#define STEP_INTERFACE 8
#define DC_IN1 9
#define DC_IN2 8
#define DC_PWM 10

AccelStepper stepper(STEP_INTERFACE, STEP_IN1, STEP_IN3, STEP_IN2, STEP_IN4);

bool isOneShot=false;

int driveSpeed = 0;
int pullSpeed = 1000;

void setup() {
  Serial.begin(9600);
  stepper.setMaxSpeed(1000);
  pinMode(DC_IN1, OUTPUT);
  pinMode(DC_IN2, OUTPUT);
  pinMode(DC_PWM, OUTPUT);
}

void runStepper() {
  stepper.setSpeed(pullSpeed);
  stepper.runSpeed();
}

void runDC(long speed) {
  digitalWrite(DC_IN1, HIGH);
  digitalWrite(DC_IN2, LOW);
  analogWrite(DC_PWM, speed);
}

int serialGetDuty() {
  if (Serial.available() > 0) {
    long value = Serial.readString().toInt();
    if (value < 0) {
      value = 0;
    } else if (value > 255) {
      value = 255;
    }
    Serial.println(value);
    return (int)value;
  }
}

void loop() {
  runStepper();
  driveSpeed = serialGetDuty();
  runDC(driveSpeed);
}
