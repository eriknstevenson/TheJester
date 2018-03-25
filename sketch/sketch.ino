#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Left Wheel (M1)
Adafruit_DCMotor *left_wheel = AFMS.getMotor(1);
int left_wheel_speed = 0x00;
int left_wheel_target_speed = 0x00;

// Right Wheel (M2)
Adafruit_DCMotor *right_wheel = AFMS.getMotor(2);
int right_wheel_speed = 0x00;
int right_wheel_target_speed = 0x00;

const int HIGH_SPEED = 0xFF;
const int MED_SPEED = 0x80;
const int LOW_SPEED = 0x40;
const int STOPPED = 0x00;
const int ACCEL = 0x04;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  Serial.println("all set");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  left_wheel->setSpeed(left_wheel_speed);
  right_wheel->setSpeed(right_wheel_speed);

  left_wheel->run(RELEASE);
  right_wheel->run(RELEASE);
}

void process_command(byte command) {
  switch (command) {
    case 0x00:
      Serial.println("doing 0");
      left_wheel_target_speed = MED_SPEED;
      right_wheel_target_speed = MED_SPEED;
      break;
    case 0x01:
      Serial.println("doing 1");
      left_wheel_target_speed = HIGH_SPEED;
      right_wheel_target_speed = HIGH_SPEED;
      break;
    case 0x02:
      Serial.println("doing 2");
      left_wheel_target_speed = HIGH_SPEED;
      right_wheel_target_speed = MED_SPEED;
      break;
    case 0x03:
      Serial.println("doing 3");
      left_wheel_target_speed = HIGH_SPEED;
      right_wheel_target_speed = MED_SPEED;
      break;
    case 0x04:
      Serial.println("doing 4");
      left_wheel_target_speed = MED_SPEED;
      right_wheel_target_speed = LOW_SPEED;
      break;
    case 0x05:
      Serial.println("doing 5");
      left_wheel_target_speed = LOW_SPEED;
      right_wheel_target_speed = LOW_SPEED;
      break;
    case 0x06:
      Serial.println("doing 6");
      left_wheel_target_speed = LOW_SPEED;
      right_wheel_target_speed = MED_SPEED;
      break;
    case 0x07:
      Serial.println("doing 7");
      left_wheel_target_speed = MED_SPEED;
      right_wheel_target_speed = HIGH_SPEED;
      break;
    case 0x08:
      Serial.println("doing 8");
      left_wheel_target_speed = MED_SPEED;
      right_wheel_target_speed = HIGH_SPEED;
      break;
    case 0x11:
      Serial.println("turning left");
      left_wheel_target_speed = -MED_SPEED;
      right_wheel_target_speed = MED_SPEED;
      break;
    case 0x12:
      Serial.println("turning right");
      left_wheel_target_speed = MED_SPEED;
      right_wheel_target_speed = -MED_SPEED;
      break;
    case 0xff:
      Serial.println("stopping");
      left_wheel_target_speed = STOPPED;
      right_wheel_target_speed = STOPPED;
      break;
    default:
      break;
  }


}

void update_speeds() {
  if (left_wheel_speed < left_wheel_target_speed) {
    left_wheel_speed += ACCEL;
  }

  if (left_wheel_speed > left_wheel_target_speed) {
    left_wheel_speed -= ACCEL;
  }

  if (left_wheel_speed > 255) {
    left_wheel_speed = 255;
  }
  if (left_wheel_speed < -255) {
    left_wheel_speed = -255;
  }

  if (right_wheel_speed < right_wheel_target_speed) {
    right_wheel_speed += ACCEL;
  }

  if (right_wheel_speed > right_wheel_target_speed) {
    right_wheel_speed -= ACCEL;
  }

  if (right_wheel_speed > 255) {
    right_wheel_speed = 255;
  }
  if (right_wheel_speed < -255) {
    right_wheel_speed = -255;
  }

  if (left_wheel_target_speed > 0 && left_wheel_speed > 0) {
    left_wheel->run(FORWARD);
  } else if (left_wheel_target_speed < 0 && left_wheel_speed < 0) {
    left_wheel->run(BACKWARD);
  } else {
    left_wheel->run(RELEASE);
  }


  if (right_wheel_target_speed > 0 && right_wheel_speed > 0) {
    right_wheel->run(FORWARD);
  } else if (right_wheel_target_speed < 0 && right_wheel_speed < 0) {
    right_wheel->run(BACKWARD);
  } else {
    right_wheel->run(RELEASE);
  }

  left_wheel->setSpeed(abs(left_wheel_speed));
  right_wheel->setSpeed(abs(right_wheel_speed));

}

void loop() {
  // Read input from Myo
  while (Serial.available() > 0) {
    char c = Serial.read();
    process_command(c);
  }

  update_speeds();

}


