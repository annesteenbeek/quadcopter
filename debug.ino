void debugProcess(){
	// Serial.print("aRoll "); Serial.print(aRoll); Serial.print("\t");
	// Serial.print("aPitch "); Serial.print(aPitch); Serial.print("\t");

	// Serial.print("gRoll "); Serial.print(gRoll); Serial.print("\t");
	// Serial.print("gPitch "); Serial.print(gPitch); Serial.print("\t");
	// Serial.print("gYaw "); Serial.print(gYaw); Serial.print("\t");

	// Serial.print("dGRoll "); Serial.print(dGRoll); Serial.print("\t");
	// Serial.print("dGPitch "); Serial.print(dGPitch); Serial.print("\t");
	// Serial.print("dGYaw "); Serial.print(dGYaw); Serial.print("\t");

	// Serial.print("dGRoll "); Serial.print(dGRoll); Serial.print("\t");
	// Serial.print("dGPitch "); Serial.print(dGPitch); Serial.print("\n");

	Serial.print("combinedRoll "); Serial.print(aRoll); Serial.print(" ");
	Serial.print(gRoll); Serial.print(" "); Serial.print(roll); Serial.print("\t");

	Serial.print("combinedpitch "); Serial.print(aPitch); Serial.print(" ");
	Serial.print(gPitch); Serial.print(" "); Serial.print(pitch); Serial.print("\t");

	// Serial.print("mx "); Serial.print(mx); Serial.print("\t");
	// Serial.print("my "); Serial.print(my); Serial.print("\t");
	// Serial.print("mz "); Serial.print(mz); Serial.print("\n");

	// Serial.print("RCroll "); Serial.print(RCroll); Serial.print("\t");
	// Serial.print("RCpitch "); Serial.print(RCpitch); Serial.print("\t");
	// Serial.print("RCyaw "); Serial.print(RCyaw); Serial.print("\t");
	// Serial.print("RCthrottle "); Serial.print(RCthrottle); Serial.print("\n");

	Serial.print("RPY "); Serial.print(roll); Serial.print(" ");
	Serial.print(pitch); Serial.print(" ");
	Serial.print(yaw); Serial.print("\t");

	// Serial.print("roll "); Serial.print(roll); Serial.print("\t");
	// Serial.print("pitch "); Serial.print(pitch); Serial.print("\t");
	// Serial.print("yaw "); Serial.print(yaw); Serial.print("\n");


	// Serial.print("chan1 "); Serial.print(chan1); Serial.print("\t");
	// Serial.print("chan2 "); Serial.print(chan2); Serial.print("\t");
	// Serial.print("chan3 "); Serial.print(chan3); Serial.print("\t");
	// Serial.print("chan4 "); Serial.print(chan4); Serial.print("\t");
}