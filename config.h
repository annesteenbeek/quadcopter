//----- Sensors --------
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

double aRoll, aPitch;
double dGRoll, dGPitch, dGYaw;
double gRoll, gPitch, gYaw;
double roll, pitch, yaw;

double tau = 0.075;

double prevTimeG;
double prevTimeK;
double prevTimeY = 0; // prev time yawRate was calculated

//------Motor Config --------
#define FL 11 //3 //10 // Front Left Motor
#define FR 3 //9 // Front Right Motor
#define BR 9 //10 //3 // Back Right Motor
#define BL 10 //11  //9 // Back Left Motor

bool motorsEnable = false;
#define LEDPIN 13

double toDeg = 180/3.14159;
double toRad = 3.14159/180;

double rollPWM;
double pitchPWM;
double yawPWM;

//------- Remote control setup ------
double RCroll, RCpitch, RCyaw, RCthrottle;
int chan1, chan2, chan3, chan4;
int ch2prev, ch3prev, ch4prev;
bool remoteState = false;
unsigned long lastReceived = 0;

#define NUM_RC_CHANNELS 4
#define ch1 6
#define ch2 7
#define ch3 8
#define ch4 4

const uint8_t RC_Channel_Pin[NUM_RC_CHANNELS]={4,6,7,8}; // Specify where to listen
uint16_t RC_Channel_Value[NUM_RC_CHANNELS];

const int ch1min = 1048; // avg: 1464
const int ch2min = 1044; // avg: 1452
const int ch3min = 1032; // avg: 1454
const int ch4min = 1040; 

const int ch1max = 1860;
const int ch2max = 1872;
const int ch3max = 1860;
const int ch4max = 1840;

const int MOTOR_ZERO_LEVEL = 100;
const int MOTOR_ARM_START = 100;
const int MOTOR_MAX_LEVEL = 254;

int FLinput, FRinput, BLinput, BRinput;

//------- PID values ------
double KpRoll = 1;
double KiRoll = 0;
double KdRoll = 0;

double KpPitch = 1;
double KiPitch = 0;
double KdPitch = 0;

double KpYaw = 1;
double KiYaw = 0;
double KdYaw = 0;

double PIDSampleTime = 0.01;

String inData;