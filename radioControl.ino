
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
  double RCyaw=constrain(map(chan2,ch2min,ch2max, -100, 100), -100, 100);
  double RCthrottle=constrain(map(chan4,ch4min,ch4max, MOTOR_ARM_START, MOTOR_MAX_LEVEL), MOTOR_ARM_START, MOTOR_MAX_LEVEL);

  if (!motorsEnable){
    checkArmingProcedure();
  }
}

// check for RC sequence to allow arming of the motors
void checkArmingProcedure(){
    // arming procedure:
    // first throttle must be low (<10)
    // then > 80 for 2 sec
    // then low again for 2 sec
    // ---- first counter
    if(RCthrottle < 10 && !lowDone){
        if(!startCount){
            startTime = micros();
            startCount = true;
        }
        if(startTime-micros()>2000000){
            lowDone = true; // start with high timer
            startCount = false;
        }
    }else{
        startCount = false;
    }

    //---- second counter 
    if(RCthrottle > 80 && lowDone && !highDone){
        if(!startCount){
            startTime = micros();
            startCount = true;
        }
        if(startTime-micros()>2000000){
            highDone = true;
            startCount = false;
        }
    }else{
        if(lowDone && startCount && !highDone){ // if sequence is broken, restart
            lowDone = false;
            startCount = false;
        }
    }
    // third counter
    if(RCthrottle <10 && lowDone && highDone){
        if(!startCount){
            startTime = micros();
            startCount = true;
        }
        if(startTime-micros()>2000000){
            motorsEnable=true;
            digitalWrite(LEDPIN, HIGH);
        }
    }else{
        if(lowDone && highDone && startCount){ // if sequence is broken, restart
            lowDone = false;
            highDone = false;
            startCount = false;
        }
    }
}