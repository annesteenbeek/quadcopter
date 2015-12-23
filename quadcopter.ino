#include "I2Cdev.h"
#include "MPU6050.h" // docs: http://www.i2cdevlib.com/docs/html/class_m_p_u6050.html
#include "Wire.h"
#include "HMC5883L.h" // Source: https://github.com/jrowberg/i2cdevlib
#include "PinChangeInt.h"
#include "Kalman.h"
#include "config.h"
#include "RCLib.h" // Source: https://github.com/jantje/libraries/tree/master/RCLib
#include "PID_v1.h"
#include <EEPROM.h>


MPU6050 mpu;    // define mpu
HMC5883L mag; // define compass

Kalman kalmanRoll;
Kalman kalmanPitch;

// create PID filter isntances
PID rollPID(&roll, &rollPWM, &RCroll, KpRoll, KiRoll, KdRoll, DIRECT);
PID pitchPID(&pitch, &pitchPWM, &RCpitch, KpPitch, KiPitch, KdPitch, DIRECT);
PID yawPID(&yaw, &yawPWM, &RCyaw, KpYaw, KiYaw, KdYaw, DIRECT);


void setup() {
  Serial.begin(9600);

  initSensors();
  SetRCInterrupts(); // init RC
  motorInit();
  getPIDValues();
  PIDinit();

  // radio pins
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
  pinMode(ch3, INPUT);
  pinMode(ch4, INPUT);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN,LOW);
}

void loop() {
  readSensors();
  filterSensors();

  readRadio();

  rollPID.Compute();
  pitchPID.Compute();
  yawPID.Compute();

  writeMotors();

  debugProcess();
  tunePIDSerial();


} 

