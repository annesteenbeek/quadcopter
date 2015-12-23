 
void getFilterValues(){ // get old Filter values from EEPROM

    // store values as floats, after read, convert back to double
    for (int i =0; i<15; i++){
        float f = 0.00f; // store float read from EEPROM
        EEPROM.get(i*sizeof(float), f);
        if(f != f){ // filter out possible NaN values
            f = 0;
        }
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
                // get Kalman Filter Values
                case 9:
                    rollQAngle = (double) f;
                    break;
                case 10: 
                    rollQBias = (double) f;
                    break;
                case 11: 
                    rollRMeasure = (double) f;
                    break;
                case 12:
                    pitchQAngle = (double) f;
                    break;
                case 13:
                    pitchQBias = (double) f;
                    break;
                case 14: 
                    pitchRMeasure = (double) f;
                    break;
            }
        f = 0.00;
    }
    rollPID.SetTunings(KpRoll, KiRoll, KdRoll);
    pitchPID.SetTunings(KpPitch, KiPitch, KdPitch);
    yawPID.SetTunings(KpYaw, KiYaw, KdYaw);
    // set Kalman values
    kalmanRoll.setQangle(rollQAngle);
    kalmanRoll.setQbias(rollQBias);
    kalmanRoll.setRmeasure(rollRMeasure);
    kalmanPitch.setQangle(pitchQAngle);
    kalmanPitch.setQbias(pitchQBias);
    kalmanPitch.setRmeasure(pitchRMeasure);
}

void setFilterValues(){
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
            if (command=="rqa"){
                rollQAngle = newValue;
                EEPROM.put(9*sizeof(float), (float) newValue);
            }
            if (command=="rqb"){
                rollQBias = newValue;
                EEPROM.put(10*sizeof(float), (float) newValue);
            }
            if (command=="rrm"){
                rollRMeasure = newValue;
                EEPROM.put(11*sizeof(float), (float) newValue);
            }
            if (command=="pqa"){
                pitchQAngle = newValue;
                EEPROM.put(12*sizeof(float), (float) newValue);
            }
            if (command=="pqb"){
                pitchQBias = newValue;
                EEPROM.put(13*sizeof(float), (float) newValue);
            }
            if (command=="prm"){
                pitchRMeasure = newValue;
                EEPROM.put(14*sizeof(float), (float) newValue);
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
                Serial.print(" ");  Serial.print(yawPID.GetKd()); 
                // kalman values
                Serial.print(" ");  Serial.print(kalmanRoll.getQangle());
                Serial.print(" ");  Serial.print(kalmanRoll.getQbias());
                Serial.print(" ");  Serial.print(kalmanRoll.getRmeasure());
                Serial.print(" ");  Serial.print(kalmanPitch.getQangle());
                Serial.print(" ");  Serial.print(kalmanPitch.getQbias());
                Serial.print(" ");  Serial.print(kalmanPitch.getRmeasure());
                Serial.print("\n");
            }

            rollPID.SetTunings(KpRoll, KiRoll, KdRoll);
            pitchPID.SetTunings(KpPitch, KiPitch, KdPitch);
            yawPID.SetTunings(KpYaw, KiYaw, KdYaw);
            // kalman values
            kalmanRoll.setQangle(rollQAngle);
            kalmanRoll.setQbias(rollQBias);
            kalmanRoll.setRmeasure(rollRMeasure);
            kalmanPitch.setQangle(pitchQAngle);
            kalmanPitch.setQbias(pitchQBias);
            kalmanPitch.setRmeasure(pitchRMeasure);

            inData = ""; // Clear recieved buffer
        }
    }
}



