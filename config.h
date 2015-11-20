//----- Sensors --------
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

double aRoll, aPitch;
double dGRoll, dGPitch, dGYaw;
double gRoll, gPitch, gYaw;
double roll, pitch, yaw;

double prevTimeG;
double prevTimeK;
double prevTimeP;

//------Motor Config --------
#define FL 10 // Front Left Motor
#define FR 11 // Front Right Motor
#define BR 3 // Back Right Motor
#define BL 9 // Back Left Motor

bool motorsEnable = false;

double toDeg = 180/3.14159;
double toRad = 3.14159/180;

double rollPWM;
double pitchPWM;
double yawPWM;


//------- Remote control setup ------
double RCroll, RCpitch, RCyaw, RCthrottle;
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
//-------- arming -------
bool lowDone = false;
bool highDone = false;
bool startCount = false;
double startTime = 0;


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

int input = 0;