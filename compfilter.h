#ifndef COMPFILETER_H
#define COMPFILETER_H

class compfilter{
public:
    compfilter(){
        prevTime = millis();
    }

    double compute(double gRate, double aAngle, double tau){
        double now = millis();
        double dT = (now - prevTime)/1000;
        double a = tau/(tau+dT);
        double angle = a * (angle + gRate * dT) + (1-a) * aAngle;

        prevTime = now;
        return angle;
    }

private:
    double prevTime;

};

#endif
