#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "HMC5883L.h" // Source: https://github.com/jrowberg/i2cdevlib
#include "Kalman.h" // Source: https://github.com/TKJElectronics/KalmanFilter
#include "PinChangeInt.h"
#include "RCLib.h"  // Source: https://github.com/jantje/libraries/tree/master/RCLib
#include "config.h"


MPU6050 mpu;    // define mpu
HMC5883L mag; // define compass

Kalman kalRoll; // Create the Kalman instances
Kalman kalPitch;

void setup() {
  #ifdef DEBUG  
  Serial.begin(9600);
  while(!Serial);
  #endif

  Wire.begin();
  mpu.initialize();
  mag.initialize();

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);w
  kalRoll.setAngle((double) atan(ay/sqrt(pow(ax,2)+pow(az,2)))*todeg); // Set starting angle
  kalPitch.setAngle((double) atan(ax/sqrt(pow(ay,2)+pow(az,2)))*todeg);

  timer=micros();

  Startroll = atan(ay/sqrt(pow(ax,2)+pow(az,2)))*todeg; // rotatie om de X as (roll)
  Startpitch = atan(ax/sqrt(pow(ay,2)+pow(az,2)))*todeg; // rotatie om de Y as (pitch)

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

  SetRCInterrupts(); //This method will do all the config foe you.
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  rollAcc = (double) atan(ay/sqrt(pow(ax,2)+pow(az,2)))*todeg; // rotatie om de X as (roll)
  pitchAcc = (double) atan(ax/sqrt(pow(ay,2)+pow(az,2)))*todeg; // rotatie om de Y as (pitch)

  // De gyroscoop maakt 131 metingen per graad/sec, dus delen door 131 geeft de verandering in graad/sec.
  gyroXrate = (double) gx/131.0;
  gyroYrate = (double) gy/131.0;
  gyroZrate = (double) gz/131.0;

  rollGyro += (gx/131.0)*((double)(micros()-timer)/1000000); // rotatie om de X as (roll)
  pitchGyro += (gy/131.0)*((double)(micros()-timer)/1000000); // rotatie om de Y as (pitch)
  yawGyro += (gz/131.0)*((double)(micros()-timer)/1000000); // rotatie om de Z as (yaw)

  Kalroll = kalRoll.getAngle(rollAcc, gyroXrate, (double)(micros()-timer)/1000000) - Startroll;
  Kalpitch = kalPitch.getAngle(pitchAcc, gyroYrate, (double)(micros()-timer)/1000000) - Startpitch;
  timer = micros();
  Kalyaw = yawGyro;

  // Magnometer
  mag.getHeading(&mx, &my, &mz);

      double heading = atan(sqrt(pow(mx,2)+pow(mz,2))/my);
      if(heading < 0)
        heading += 2 * M_PI;

  // get the Radio data
  int flag;
    if(flag=getChannelsReceiveInfo()){
  chan1 = constrain(RC_Channel_Value[0],ch1min, ch1max);
  chan2 = constrain(RC_Channel_Value[1],ch2min, ch2max);
  chan3 = constrain(RC_Channel_Value[2],ch3min, ch3max);
  chan4 = constrain(RC_Channel_Value[3],ch4min, ch4max);
  }

  RCroll=constrain(map(chan4,ch4min,ch4max,-45,45), -45, 45);
  RCpitch=constrain(map(chan2,ch2min,ch2max, -45, 45), -45, 45);
  RCyaw=constrain(map(chan1,ch1min,ch1max, -100, 100), -100, 100);
  RCthrottle=constrain(map(chan3,ch3min,ch3max, 100, 220), 95, 220);

  PIDroll = ((RCroll - Kalroll)*Kp_roll - gyroXrate)*Kd_roll; 
  PIDpitch = ((RCpitch - Kalpitch)*Kp_pitch - gyroYrate)*Kd_pitch; 
  PIDyaw = ((RCyaw - Kalyaw)*Kp_yaw - gyroZrate)*Kd_yaw; 

  if (RCthrottle > 110) {
  analogWrite(FL, RCthrottle - PIDpitch + PIDroll + PIDyaw);
  analogWrite(FR, RCthrottle - PIDpitch - PIDroll - PIDyaw);
  analogWrite(BL, RCthrottle + PIDpitch + PIDroll - PIDyaw);
  analogWrite(BR, RCthrottle + PIDpitch - PIDroll + PIDyaw);
  }
  else {
  analogWrite(FL, 100);
  analogWrite(FR, 100);
  analogWrite(BL, 100);
  analogWrite(BR, 100);
  }


  if (Serial.available() > 0) {
    input = Serial.parseInt();
    Serial.print("Input was: "); Serial.println(input);
    //kalPitch.setAngle((double) input);
    }

  Serial.print("Kalroll: "); Serial.print(Kalroll);
  Serial.print("  Kalpitch: "); Serial.print(Kalpitch);
  Serial.print("  Kalyaw: "); Serial.print(Kalyaw);

  Serial.print(" FL: "); Serial.print(RCthrottle - PIDpitch + PIDroll + PIDyaw);
  Serial.print("  FR: "); Serial.print(RCthrottle - PIDpitch - PIDroll - PIDyaw);
  Serial.print("  BL: "); Serial.print(RCthrottle + PIDpitch + PIDroll - PIDyaw);
  Serial.print("  BR: "); Serial.println(RCthrottle + PIDpitch - PIDroll + PIDyaw);

  #ifdef DEBUG
    debugProcess();
  #endif

} 

