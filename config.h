// ----- Debug settings ------
#define DEBUG

// ----- Sensors --------
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

double aRoll, aPitch;
double dGx, dGy, dGz;
double gRoll, gPitch, gYaw;

double timer;

//------Motor Config --------

#define FL 10 // Front Left Motor
#define FR 11 // Front Right Motor
#define BR 3 // Back Right Motor
#define BL 9 // Back Left Motor

double toDeg = 180/3.14159;
double toRad = 3.14159/180;

int RCroll, RCpitch, RCyaw, RCthrottle;
int chan1, chan2, chan3, chan4;

#define NUM_RC_CHANNELS 4
#define ch1 6
#define ch2 7
#define ch3 8
#define ch4 4

const uint8_t RC_Channel_Pin[NUM_RC_CHANNELS]={4,6,7,8}; // Specify where to listen
uint16_t RC_Channel_Value[NUM_RC_CHANNELS];

#define ch1min 1084
#define ch2min 1050
#define ch3min 1052
#define ch4min 1116

#define ch1max 1916
#define ch2max 1880
#define ch3max 1868
#define ch4max 1932

#define Kp_roll 0.1
#define Ki_roll 0.1
#define Kd_roll 0.1

#define Kp_pitch 0.1
#define Ki_pitch 0.1
#define Kd_pitch 0.1

#define Kp_yaw 0
#define Ki_yaw 0
#define Kd_yaw 0

int input = 0;