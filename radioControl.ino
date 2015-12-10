
void readRadio(){

    int flag;
  // get the Radio data
  if(flag=getChannelsReceiveInfo()){
    int chan1 = constrain(RC_Channel_Value[0],ch1min, ch1max);
    int chan2 = constrain(RC_Channel_Value[1],ch2min, ch2max);
    int chan3 = constrain(RC_Channel_Value[2],ch3min, ch3max);
    int chan4 = constrain(RC_Channel_Value[3],ch4min, ch4max);
  }

  double RCroll=constrain(map(chan1,ch1min,ch1max,-45,45), -45, 45);
  double RCpitch=constrain(map(chan3,ch3min,ch3max, -45, 45), -45, 45);
  double RCthrottle=constrain(map(chan4,ch4min,ch4max, MOTOR_ARM_START, MOTOR_MAX_LEVEL), MOTOR_ARM_START, MOTOR_MAX_LEVEL);

  // yaw works incremental but for reliable function needs to be called periodically
  if(micros()-prevTimeY > 100){
        double RCyaw =((int) yawAvg + map(chan2,ch2min,ch2max, -10, 10)) % 360;
        prevTimeY = micros(); 
    }

  if (!motorsEnable){
    checkArmingProcedure();
  }
}

// check for RC sequence to allow arming of the motors
void checkArmingProcedure(){
    // throttle needs to be low before motors are enabled
    if(RCthrottle <= MOTOR_ARM_START + 10){
        motorsEnable = true;
    }
}