#include "I2Cdev.h"
#include "MPU6050.h" // docs: http://www.i2cdevlib.com/docs/html/class_m_p_u6050.html
#include "Wire.h"
#include "HMC5883L.h" // Source: https://github.com/jrowberg/i2cdevlib
#include "PinChangeInt.h"
// #include "RCLib.h"  // Source: https://github.com/jantje/libraries/tree/master/RCLib
#include "config.h"

MPU6050 mpu;    // define mpu
HMC5883L mag; // define compass

void setup() {
  #ifdef DEBUG  
  Serial.begin(9600);
  while(!Serial);
  #endif
  Wire.begin();
  mpu.initialize();
  mag.initialize();

  timer = micros();
  // initSensors();

  // radio pins
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
  pinMode(ch3, INPUT);
  pinMode(ch4, INPUT);

  // motor pins
  pinMode(FL, OUTPUT);  // Front Left Motor
  pinMode(FR, OUTPUT);  // Front Right Motor
  pinMode(BL, OUTPUT);  // Back Left Motor
  pinMode(BR, OUTPUT);  // Back Right Motor

  // SetRCInterrupts(); //This method will do all the config for you.
}

void loop() {
  readSensors();

  // readRadio();

  #ifdef DEBUG
    debugProcess();
  #endif

} 

