// void initSensors(){

// }

void readSensors(){
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  aRoll = atan2(ay, az)*toDeg;
  aPitch = atan2(-ax, sqrt(pow(ay,2)+pow(az,2)))*toDeg;

  // De gyroscoop maakt 131 metingen per graad/sec, dus delen door 131 geeft de verandering in graad/sec.
  dGx = (double) gx/131.0;
  dGy = (double) gy/131.0;
  dGz = (double) gz/131.0;

  gRoll += dGx*((micros()-timer)/1000000); // rotatie om de X as (roll)
  gPitch += dGy*((micros()-timer)/1000000); // rotatie om de Y as (pitch)
  gYaw += dGz*((micros()-timer)/1000000); // rotatie om de Z as (yaw)

  timer = micros();

   // Magnometer
  mag.getHeading(&mx, &my, &mz);
  double heading = atan(sqrt(pow(mx,2)+pow(mz,2))/my);
  if(heading < 0)
    heading += 2 * M_PI;

}

// void filterSensors(){


// }