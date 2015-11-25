 
void getPIDValues(){ // get old PID values from EEPROM

    // store values as floats, after read, convert back to double
    for (int i =0; i<9; i++){
        float f = 0.00f; // store float read from EEPROM
        EEPROM.get(i*sizeof(float), f);
            switch (i){
                case 0:
                KpRoll = (double) f;
                break;
                case 1:
                KiRoll = (double) f;
                break;
                case 2:
                KdRoll = (double) f;
                break;
                case 3:
                KpPitch = (double) f;
                break;
                case 4:
                KiPitch = (double) f;
                break;
                case 5:
                KdPitch = (double) f;
                break;
                case 6:
                KpYaw = (double) f;
                break;
                case 7:
                KiYaw = (double) f;
                break;
                case 8:
                KdYaw = (double) f;
                break;
            }
        rollPID.SetTunings(KpRoll, KiRoll, KdRoll);
        pitchPID.SetTunings(KpPitch, KiPitch, KdPitch);
        yawPID.SetTunings(KpYaw, KiYaw, KdYaw);

        f = 0.00;
    }
}

void tunePIDSerial(){
   while (Serial.available() > 0){
        char recieved = Serial.read();
        inData += recieved; 

        // Process message when new line character is recieved
        if (recieved == '\n')
        {
            inData = inData.substring(0, inData.length()-1); // remove '\n' from string
            String command = inData.substring(0,3);
            String value = inData.substring(3);
            char buffer[10];
            value.toCharArray(buffer, 10);
            double newValue = atof(buffer);
            if (command=="rkp"){
                KpRoll = newValue;
                EEPROM.put(0, (float) newValue);
            }
            if (command=="rki"){
                KiRoll = newValue;
                EEPROM.put(1*sizeof(float), (float) newValue);
            }
            if (command=="rkd"){
                KdRoll = newValue;
                EEPROM.put(2*sizeof(float), (float) newValue);
            }
            if (command=="pkp"){
                KpPitch = newValue;
                EEPROM.put(3*sizeof(float), (float) newValue);
            }
            if (command=="pki"){
                KiPitch = newValue;
                EEPROM.put(4*sizeof(float), (float) newValue);
            }
            if (command=="pkd"){
                KdPitch = newValue;
                EEPROM.put(5*sizeof(float), (float) newValue);
            }
            if (command=="ykp"){
                KpYaw = newValue;
                EEPROM.put(6*sizeof(float), (float) newValue);
            }
            if (command=="yki"){
                KiYaw = newValue;
                EEPROM.put(7*sizeof(float), (float) newValue);
            }
            if (command=="ykd"){
                KdYaw = newValue;
                EEPROM.put(8*sizeof(float), (float) newValue);
            }
            if (inData=="getPIDValues"){
                Serial.print("PIDvalues ");  Serial.print(rollPID.GetKp());
                Serial.print(" ");  Serial.print(rollPID.GetKi());
                Serial.print(" ");  Serial.print(rollPID.GetKd());
                Serial.print(" ");  Serial.print(pitchPID.GetKp());
                Serial.print(" ");  Serial.print(pitchPID.GetKi());
                Serial.print(" ");  Serial.print(pitchPID.GetKd());
                Serial.print(" ");  Serial.print(yawPID.GetKp());
                Serial.print(" ");  Serial.print(yawPID.GetKi());
                Serial.print(" ");  Serial.print(yawPID.GetKd()); Serial.print("\n");
            }

            rollPID.SetTunings(KpRoll, KiRoll, KdRoll);
            pitchPID.SetTunings(KpPitch, KiPitch, KdPitch);
            yawPID.SetTunings(KpYaw, KiYaw, KdYaw);

            inData = ""; // Clear recieved buffer
        }
    }
}



