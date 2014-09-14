// source: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it/

 double Q_angle = 0.001; // Process noise variance
 double Q_gyroBias = 0.03; // Gyro bias variance
 double R_angle = 0.03; // measurment covariance varriance

 double Rate[3] = {0};
 double Angle[3] = {0};
 double bias[3] = {0};
 double y[3] = {0};
 double S[3] = {0};
 double k[2][3] = {0};
 double P[2][6]={0};


double Kalman(double newAngle[], double newRate[], double dt) {
	Rate[0]=newRate[0]-bias[0];
	Rate[1]=newRate[1]-bias[1];
	Rate[2]=newRate[2]-bias[2];

	Angle[0]+=dt*Rate[0];
	Angle[1]+=dt*Rate[1];
	Angle[2]+=dt*Rate[2];
	
	// Covariantie matrix P(k|k-1)
	// [P]=(k|k-1)=[F]*[P(k-1|k-1)]*[F]^T+Q_k
	
	P[0][0]+=dt*(dt*P[1][1]-P[0][1]-P[1][0]+Q_angle);
	P[0][1]-=dt*P[1][1];
	P[1][0]-=dt*P[1][1];
	P[1][1]+=dt*Q_gyroBias;
	
	P[0][2]+=dt*(dt*P[1][3]-P[0][3]-P[1][2]+Q_angle);
	P[0][3]-=dt*P[1][3];
	P[1][2]-=dt*P[1][3];
	P[1][3]+=dt*Q_gyroBias;
	
	P[0][4]+=dt*(dt*P[1][5]-P[0][5]-P[1][4]+Q_angle);
	P[0][5]-=dt*P[1][5];
	P[1][4]-=dt*P[1][5];
	P[1][5]+=dt*Q_gyroBias;
	
	// Innovation is het verschil tussen de meting en de vorige staat
	y[0]=newAngle[0]-Angle[0];
	y[1]=newAngle[1]-Angle[1];
	y[2]=newAngle[2]-Angle[2];
	
	// S is innovation covarience S_k = H * P(k|k-1)*H^T+newRate-bias
	// R is measurment noise varriance
	S[0]=P[0][0]+R_angle;
	S[1]=P[0][2]+R_angle;
	S[2]=P[0][4]+R_angle;
	// K is Kalman gain K=P(k|k-1)*H^T*S_k^-1
	// Kalman gain expresses how much you gan trust the calculated innovation
	k[0][0]=P[0][0]/S[0];
	k[1][0]=P[1][0]/S[0];
	
	k[0][1]=P[0][0]/S[1];
	k[1][1]=P[1][0]/S[1];
	
	k[0][2]=P[0][0]/S[2];
	k[1][2]=P[1][0]/S[2];
	
	// New estimation
 	Angle[0]+=k[0][0]*y[0];
 	bias[0]+=k[1][0]*y[0];
 	
 	Angle[1]+=k[0][1]*y[1];
 	bias[1]+=k[1][1]*y[1];
 	
 	Angle[2]+=k[0][2]*y[2];
 	bias[2]+=k[1][2]*y[2];

	// De error covarience matrix aanpassen
	P[0][0] -= k[0][0] * P[0][0];
	P[0][1] -= k[0][0] * P[0][1];
	P[1][0] -= k[1][0] * P[0][0];
	P[1][1] -= k[1][0] * P[0][1];
	
	P[0][2] -= k[0][1] * P[0][2];
	P[0][3] -= k[0][1] * P[0][3];
	P[1][2] -= k[1][1] * P[0][2];
	P[1][3] -= k[1][1] * P[0][3];
	
	P[0][4] -= k[0][2] * P[0][4];
	P[0][5] -= k[0][2] * P[0][5];
	P[1][4] -= k[1][2] * P[0][4];
	P[1][5] -= k[1][2] * P[0][5];

return Angle[3];
}

