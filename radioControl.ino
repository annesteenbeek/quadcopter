// void readRadio(){
//   // get the Radio data
//   int flag;
//     if(flag=getChannelsReceiveInfo()){
//   chan1 = constrain(RC_Channel_Value[0],ch1min, ch1max);
//   chan2 = constrain(RC_Channel_Value[1],ch2min, ch2max);
//   chan3 = constrain(RC_Channel_Value[2],ch3min, ch3max);
//   chan4 = constrain(RC_Channel_Value[3],ch4min, ch4max);
//   }

//   RCroll=constrain(map(chan4,ch4min,ch4max,-45,45), -45, 45);
//   RCpitch=constrain(map(chan2,ch2min,ch2max, -45, 45), -45, 45);
//   RCyaw=constrain(map(chan1,ch1min,ch1max, -100, 100), -100, 100);
//   RCthrottle=constrain(map(chan3,ch3min,ch3max, 100, 220), 95, 220);

//   PIDroll = ((RCroll - Kalroll)*Kp_roll - gyroXrate)*Kd_roll; 
//   PIDpitch = ((RCpitch - Kalpitch)*Kp_pitch - gyroYrate)*Kd_pitch; 
//   PIDyaw = ((RCyaw - Kalyaw)*Kp_yaw - gyroZrate)*Kd_yaw; 
// }