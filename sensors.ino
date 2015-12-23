
void initSensors(){
  Wire.begin();
  mpu.initialize();
  mag.initialize();

  prevTimeG = micros();
  prevTimeK = micros();
}

void readSensors(){
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  aRoll = atan2(ay, az)*toDeg;
  aPitch = atan2(-ax, sqrt(pow(ay,2)+pow(az,2)))*toDeg;

  // De gyroscoop maakt 131 metingen per graad/sec, dus delen door 131 geeft de verandering in graad/sec.
  dGRoll = (double) gx/131.0;
  dGPitch = (double) gz/131.0;
  dGYaw = (double) gy/131.0;

  double dT = (micros()-prevTimeG)/1000000;

  gRoll += dGRoll*dT; // rotatie om de X as (roll)
  gPitch += dGPitch*dT; // rotatie om de Y as (pitch)
  gYaw += dGYaw*dT; // rotatie om de Z as (yaw)

  prevTimeG = micros();

   // Magnometer
  mag.getHeading(&mx, &my, &mz);
  double heading = atan(sqrt(pow(mx,2)+pow(mz,2))/my);
  if(heading < 0)
    heading += 2 * M_PI;

}

void filterSensors(){
  double dT = (micros()- prevTimeK)/1000000;
  roll = kalmanRoll.getAngle(aRoll, dGRoll, dT);
  pitch = kalmanPitch.getAngle(aPitch, dGPitch, dT);
  prevTimeK = micros();
  yaw = tiltCompensateYaw(mx, my, mz, roll, pitch);

}

double tiltCompensateYaw(double mx, double my, double mz, double roll, double pitch){
  roll = roll*toRad;
  pitch = pitch*toRad;
  double Xh = mx * cos(pitch) + my * sin(roll) * sin(pitch) + mz * cos(roll) * sin(pitch);
  double Yh = my * cos(roll) - mz * sin(roll);
  return atan2(-Yh, Xh)*toDeg;
}