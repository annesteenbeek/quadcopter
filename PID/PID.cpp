// sources used: http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/

#include "PID.h"

PID::PID(double* Input, double* Output, double* Setpoint, double Kp, double Ki, double Kd){
	myOutput = Output;
	myInput = Input;
	mySetpoint = Setpoint;
	inAuto = false;

	PID::setOutputLimits(-255,255); // default output limits for FRDM board

	SampleTime = 0.1; 

	PID::setTunings(Kp, Ki, Kd);
}

bool PID::compute(double dt){
	if(!inAuto) return false;

	// calculate using sample time frequency (regular intervals)
	// no more need to modify derivative/int sicne sample time is constant
	if(dt <=SampleTime){ 
		double input = *myInput;
		error = *mySetpoint - input;  // get error for proportional
		ITerm += (ki*error);  // Error for integral (with ki included)
		// check for integrator windup
		if(ITerm> outMax) ITerm=outMax;
		else if(ITerm<outMin) ITerm=outMin;
		dErr = (error - lastErr); // get error for derivative
		// (could still be tuned for derivative kick)

		// compute PID output
		double output  = kp * error + ITerm + kd * dErr;
		// make sure output is allso within min/max
		if(output> outMax) output=outMax;
		else if(output<outMin) output=outMin;
		*myOutput = output;
		lastErr = error;
		return true;
	}
	else return false;
}

void PID::setTunings(double Kp, double Ki, double Kd)
{
	if (Kp<0 || Ki<0|| Kd<0) return;
	kp = Kp;
	ki = Ki * SampleTime; // change PID parameters according to sample time (in seconds)
	kd = Kd / SampleTime;
}

void PID::setSampleTime(double NewSampleTime){
	if (NewSampleTime > 0 ){
		// change ratios for parameters for better computation in compute()
		double ratio = NewSampleTime/SampleTime;
		ki *= ratio;
		kd /= ratio;
		SampleTime = NewSampleTime;
	}
}

void PID::setOutputLimits(double min, double max){
	if (min > max) return;
	outMin = min;
	outMax = max;

	if(inAuto){
		if(*myOutput > outMax) *myOutput = outMax;
		else if(*myOutput < outMin) *myOutput = outMin;
	
		if(ITerm > outMax) ITerm= outMax;
		else if(ITerm < outMin) ITerm= outMin;
	}
}

void PID::setMode(int Mode){
	// Turn PID on(AUTOMATIC) or off(MANUAL)
	bool newAuto = (Mode == AUTOMATIC);
	if(newAuto && !inAuto){
		PID::initialize(); // avoid bump because of stored values
	}
	inAuto = newAuto;
}

void PID::initialize(){
	lastInput = *myInput;
	ITerm = *myOutput;
	lastErr = 0;
	if(ITerm> outMax) ITerm=outMax;
	else if(ITerm<outMin) ITerm=outMin;
}

double PID::getKp(){
	return kp;
}
	
double PID::getKi(){
	return ki/SampleTime;
}

double PID::getKd(){
	return kd*SampleTime;
}