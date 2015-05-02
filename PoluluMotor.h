



#ifndef POLULUMOTOR_h
#define POLULUMOTOR_h

#include <PID_v1.h>
#include <PololuWheelEncoders.h>
#include "Arduino.h"


#define MAX_SPEED 300

class PoluluMotor{
  
  static int instances;                                               // Count of instances. At max 2 Instances allowed.
  static int m1_encA, m1_encB, m2_encA, m2_encB;                      // 4 Encoder pins from 2 motors.
  
  
  
  public:  // Functions
    PoluluMotor(uint8_t pinPWM, uint8_t pinIN1, uint8_t pinIN2);      // Constructor
    void attachEncoder(uint8_t pinENCA);                              // If single encoder channel will be used
    void attachEncoder(uint8_t pinENCA, uint8_t pinENCB);             // If both encoder channels will be used
    void detachEncoder();                                             // Disengages the encoder.
    
    void setDuty(double perDuty);                                     // Sets the duty cycle, perDuty in range (0, 1)
    void setRefSpeed(double rpm);                                     // Set the reference speed (if PID engaged, pid shall be used)
    void setGains(double Kp, double Ki, double Kd);                   // PID gains, if engaged
    void setPIDEngage(boolean value);                                 // Set the pid_engage variable value
    
    double getSpeed();                                                // Returns the speed in RPM
    uint8_t getDirection();                                           // Returns the direction of rotation (1: Clockwise, 0: Stopped, -1: Anticlockwise)
    
    void brake(uint8_t duration_ms);                                  // Explicit braking with GND/Vs
    void reverse();                                                   // Safely reverses the direction of motor
    
    void applyUpdate();                                               // Applies the speed corrections (manual pwm or PID correction, whichever applicable)
    
    
  public:  // Variables
    int me_instance;
    boolean pid_engage, motor_enable, feedback_enable;
    boolean isClockwise;
    
    uint8_t pwm, in1, in2;
    double currSpeed, refSpeed, output;
    double Kp, Ki, Kd;
  
    PID* myPID;    
    
};

#endif