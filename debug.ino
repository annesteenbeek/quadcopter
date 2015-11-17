void debugProcess(){
	Serial.print("aRoll "); Serial.print(aRoll); Serial.print("\t");
	Serial.print("aPitch "); Serial.print(aPitch); Serial.print("\n");

	Serial.print("gRoll "); Serial.print(gRoll); Serial.print("\t");
	Serial.print("gPitch "); Serial.print(gPitch); Serial.print("\t");
	Serial.print("gYaw "); Serial.print(gYaw); Serial.print("\n");

	Serial.print("mx "); Serial.print(mx); Serial.print("\t");
	Serial.print("my "); Serial.print(my); Serial.print("\t");
	Serial.print("mz "); Serial.print(mz); Serial.print("\n");

	// Serial.print("RCroll "); Serial.print(RCroll); Serial.print("\t");
	// Serial.print("RCpitch "); Serial.print(RCpitch); Serial.print("\t");
	// Serial.print("RCyaw "); Serial.print(RCyaw); Serial.print("\t");
	// Serial.print("RCthrottle "); Serial.print(RCthrottle); Serial.print("\n");
}