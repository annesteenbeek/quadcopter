
void PIDinit(){
    rollPID.SetMode(AUTOMATIC);
    pitchPID.SetMode(AUTOMATIC);
    yawPID.SetMode(AUTOMATIC);

    rollPID.SetOutputLimits(0, 254);
    pitchPID.SetOutputLimits(0, 254);
    yawPID.SetOutputLimits(0, 254);

    rollPID.SetSampleTime(PIDSampleTime);
    pitchPID.SetSampleTime(PIDSampleTime);
    yawPID.SetSampleTime(PIDSampleTime);
}


void motorInit(){
  // motor pins
  pinMode(FL, OUTPUT);  // Front Left Motor
  pinMode(FR, OUTPUT);  // Front Right Motor
  pinMode(BL, OUTPUT);  // Back Left Motor
  pinMode(BR, OUTPUT);  // Back Right Motor

  // send start value to motors when initializing 
  analogWrite(FL, MOTOR_ZERO_LEVEL);
  analogWrite(FR, MOTOR_ZERO_LEVEL);
  analogWrite(BL, MOTOR_ZERO_LEVEL);
  analogWrite(BR, MOTOR_ZERO_LEVEL);
}

void writeMotors(){
  FLinput = (int) (RCthrottle - pitchPWM + rollPWM + yawPWM);
  FRinput = (int) (RCthrottle - pitchPWM - rollPWM - yawPWM);
  BLinput = (int) (RCthrottle + pitchPWM + rollPWM - yawPWM);
  BRinput = (int) (RCthrottle + pitchPWM - rollPWM + yawPWM);

  FLinput = constrain(FLinput, MOTOR_ZERO_LEVEL, MOTOR_MAX_LEVEL);
  FRinput = constrain(FRinput, MOTOR_ZERO_LEVEL, MOTOR_MAX_LEVEL);
  BLinput = constrain(BLinput, MOTOR_ZERO_LEVEL, MOTOR_MAX_LEVEL);
  BRinput = constrain(BRinput, MOTOR_ZERO_LEVEL, MOTOR_MAX_LEVEL);

  analogWrite(FL, FLinput);
  analogWrite(FR, FRinput);
  analogWrite(BL, BLinput);
  analogWrite(BR, BRinput);
}
