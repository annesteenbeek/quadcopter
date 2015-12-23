
void readRadio(){

    int flag;
  // get the Radio data
  if(flag=getChannelsReceiveInfo()){
    ch2prev = chan2;
    ch3prev = chan3;
    ch4prev = chan4;
    chan1 = constrain(RC_Channel_Value[0],ch1min, ch1max);
    chan2 = constrain(RC_Channel_Value[1],ch2min, ch2max);
    chan3 = constrain(RC_Channel_Value[2],ch3min, ch3max);
    chan4 = constrain(RC_Channel_Value[3],ch4min, ch4max);
  }

  RCroll=map(chan1,ch1min,ch1max,-45,45);
  RCpitch=map(chan3,ch3min,ch3max, -45, 45);
  RCthrottle=map(chan4,ch4min,ch4max, MOTOR_ARM_START, MOTOR_MAX_LEVEL);
  RCyaw = yaw + map(chan2,ch2min,ch2max, -10, 10);

  remoteCheck();

  if (!motorsEnable){
    checkArmingProcedure();
  }
}

// check for RC sequence to allow arming of the motors
void checkArmingProcedure(){
    // throttle needs to be low before motors are enabled
    if(RCthrottle <= (MOTOR_ARM_START + 5) && remoteState){
        motorsEnable = true;
    }
}

void remoteCheck(){
  if(ch2prev==chan2 && ch3prev==chan3 && ch4prev==chan4){
    if((millis() - lastReceived) > 1000){
      remoteState = false;
      motorsEnable = false;
    }
  }else {
      lastReceived = millis();
      remoteState = true;
    }
}