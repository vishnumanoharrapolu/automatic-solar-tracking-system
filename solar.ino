#include <Servo.h>

// ----- Pins -----
const int PIN_SERVO_AZ = 9;   // Azimuth servo
const int PIN_SERVO_EL = 10;  // Elevation servo

const int PIN_LDR_LEFT  = A0;
const int PIN_LDR_RIGHT = A1;
const int PIN_LDR_UP    = A2;
const int PIN_LDR_DOWN  = A3;

const int PIN_RAIN = 7;  // digital
const int PIN_PIR  = 6;  // digital

// ----- Servos -----
Servo servoAz;
Servo servoEl;

// ----- Angles -----
int azimuthAngle   = 90;  // start centered
int elevationAngle = 45;  // start mid
const int AZ_MIN = 0, AZ_MAX = 180;
const int EL_MIN = 10, EL_MAX = 85;

// ----- Motion tuning -----
const int DEAD_BAND = 30;   // minimum diff to move
const int STEP_MIN  = 1;    // smallest servo step
const int STEP_MAX  = 4;    // largest servo step

// ----- Park position -----
const int PARK_AZ = 90;
const int PARK_EL = 0;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_RAIN, INPUT);
  pinMode(PIN_PIR, INPUT);

  servoAz.attach(PIN_SERVO_AZ);
  servoEl.attach(PIN_SERVO_EL);

  servoAz.write(azimuthAngle);
  servoEl.write(elevationAngle);

  Serial.println("Solar Tracker Initialized");
}

int moveStepFromError(int error) {
  int mag = abs(error);
  if (mag < DEAD_BAND) return 0;
  int step = map(mag, DEAD_BAND, DEAD_BAND * 6, STEP_MIN, STEP_MAX);
  if (step > STEP_MAX) step = STEP_MAX;
  return (error > 0 ? step : -step);
}

void loop() {
  // Read LDRs
  int leftVal  = analogRead(PIN_LDR_LEFT);
  int rightVal = analogRead(PIN_LDR_RIGHT);
  int upVal    = analogRead(PIN_LDR_UP);
  int downVal  = analogRead(PIN_LDR_DOWN);

  int diffX = leftVal - rightVal; // +ve => move right
  int diffY = upVal - downVal;    // +ve => tilt down

  int rain = digitalRead(PIN_RAIN);
  int pir  = digitalRead(PIN_PIR);

  // Safety: rain -> park; PIR -> pause
  if (rain == LOW) { // adjust depending on your module
    azimuthAngle   = PARK_AZ;
    elevationAngle = PARK_EL;
    Serial.println("Rain detected: PARKING");
  } else if (pir == HIGH) {
    Serial.println("PIR active: pausing movement");
  } else {
    // Normal tracking
    int stepAz = moveStepFromError(diffX);
    int stepEl = moveStepFromError(diffY);

    azimuthAngle   = constrain(azimuthAngle   + stepAz, AZ_MIN, AZ_MAX);
    elevationAngle = constrain(elevationAngle + (-stepEl), EL_MIN, EL_MAX);

    Serial.print("AZ: "); Serial.print(azimuthAngle);
    Serial.print(" EL: "); Serial.print(elevationAngle);
    Serial.print(" | diffX: "); Serial.print(diffX);
    Serial.print(" diffY: "); Serial.println(diffY);
  }

  // Write servos
  servoAz.write(azimuthAngle);
  servoEl.write(elevationAngle);

  delay(200); // loop delay
}
