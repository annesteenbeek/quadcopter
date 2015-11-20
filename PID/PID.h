#ifndef PID_H
#define PID_H

class PID{
	public:
	PID(double*, double*, double*, double, double, double);

	void compute(double);

	void setOutputLimits(double, double);

	void setSampleTime(double);

	void setTunings(double, double, double);
	
	double getKp();
	double getKi();
	double getKd();

	private:
	void Initialize();
	double SampleTime;
	double *myInput;              // * Pointers to the Input, Output, and Setpoint variables
    double *myOutput;             //   This creates a hard link between the variables and the 
    double *mySetpoint;           //   PID, freeing the user from having to constantly tell us
                                  //   what these values are.  with pointers we'll just know.
	double error, ITerm, dErr; 
	double lastErr, lastInput;
	double kp, ki, kd;
	double outMin, outMax;
	bool inAuto;

};

#endif