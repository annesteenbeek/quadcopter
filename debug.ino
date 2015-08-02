void debugProcess(){
	Serial.print("ax:"); Serial.println(ax); 
	Serial.print("ay:"); Serial.println(ay); 
	Serial.print("az:"); Serial.println(az);

	Serial.print("gx:"); Serial.println(gx); 
	Serial.print("gy:"); Serial.println(gy); 
	Serial.print("gz:"); Serial.println(gz);

	Serial.print("mx:"); Serial.println(mx); 
	Serial.print("my:"); Serial.println(my); 
	Serial.print("mz:"); Serial.println(mz);

	Serial.print("RCroll:"); Serial.print(RCroll);
	Serial.print("RCpitch:"); Serial.print(RCpitch);
	Serial.print("RCyaw:"); Serial.print(RCyaw);
	Serial.print("RCthrottle:"); Serial.println(RCthrottle);
}