/* ArduMoto Control 20/06/2021

   Arduino Uno
   Sparkfun Ardumoto shield Dev-14129
   
*/
#include "ArduMotoControl.h"

// define constants
#define DT_CONTROL_MILLIS 10  // Control DT suggested range 5-50 mSec --> 200-20 Hz
#define GEAR_RATIO 29.86      // Motor gear ratio
#define TIMEOUT 5             // Experiment length in seconds

// timeout flag
boolean timeOutFlag = 0;

// Control Variables
float encoderRADSdt = 0;
float encoderRADSPulses = 0;
float motorRPMdt = 0;
float motorRPMPulses = 0;

// control loop function
void MotorControlLoop(void);
// Control function
float MotorControl(float desiredCMD);

// Init setup
void setup() {
  // intinitalize encoder
  InitArduMotorControl();
  pinMode(LED_BUILTIN, OUTPUT);
  
  // init serial
  Serial.begin (115200);
  //////////////////////////////
  //////// Student Code ////////
  //////////////////////////////
  
  // serial plotter legend
  Serial.println("MotorCMD, RPMdt, RPMPulses");
  
  //////////////////////////////
  //// End of student Code /////
  //////////////////////////////
}

void loop() {
  if (!timeOutFlag){
    static unsigned long millisTick = millis();
    if (millisTick >= TIMEOUT*1000) timeOutFlag = 1;
    
    // control loop software implementation
    if ((millis() - millisTick) >= DT_CONTROL_MILLIS){
      millisTick = millis();
      unsigned long microsTick = micros(); // simple loop cpu consumption measurement
      digitalWrite(LED_BUILTIN,HIGH);

      // update Motor RPM variables
      encoderRADSdt = ReadRadS(); // rad/s measured from dt between pulses with averaging
      encoderRADSPulses = readRadSEncoder(); // rad/s measured from number of pulses over control period 
      motorRPMdt = encoderRADSdt / GEAR_RATIO * RADS_RPM;
      motorRPMPulses = encoderRADSPulses / GEAR_RATIO * RADS_RPM;
      
      //////////////////////////////
      //////// Student Code ////////
      //////////////////////////////

      // motor control loop function call
      MotorControlLoop();

      //////////////////////////////
      //// End of student Code /////
      //////////////////////////////
    }
  }else{
      // turn off motor
      motorComand(0);
  }
}

//////////////////////////////
////// Student functions /////
//////////////////////////////

// control loop function
void MotorControlLoop(void){
  // openloop
  float motorCMD =  0.5 * StepCMD(2); // step command, input period seconds
  //float motorCMD =  0.5 * RampCMD(5); // Ramp command, input period seconds
   
  // update motor, values range of [-1..1]
  motorComand(motorCMD);

  // send values to serial plotter
  Serial.print(motorCMD*100); // scaled to 100% to be visible on plot
  Serial.print(" , ");
  Serial.print(motorRPMdt); // motorRPMdt
  Serial.print(" , ");
  Serial.println(motorRPMPulses); // motorRPMPulses
} 

// control loop function
float MotorControl(float desiredCMD){
  float motorCMD = desiredCMD;
  return motorCMD;
}

//////////////////////////////
// End of Student functions //
//////////////////////////////
 
