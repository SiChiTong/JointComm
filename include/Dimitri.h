#ifndef DIMITRI_H
#define DIMITRI_H

#include "dynamixel.h"
#include "JointChain.h"
#include <ctime>

enum DimitriJoints {
  LROLL,
  LPITCH,
  LYAW,
  LELBOW,
  RROLL,
  RPITCH,
  RYAW,
  RELBOW,
  WROLL,
  WPITCH,
  WYAW,
  HPAN,
  HTILT
};

class Dimitri
{

  private:

    JointChain *leftArm;
    JointChain *rightArm;
    JointChain *head;
    JointChain *waist;
    
    time_t initial_time;

  public:

    /*
     * This constructor will initialize the Dimitri object
     * opening /dev/ttyUSBx, where x is the deviceIndex.
     * The baudrate is defined by baudNum. Use baudNum 16
     * for 115200bps.
     */
    Dimitri(int deviceIndex, int baudNum);

    ~Dimitri();

    JointChain *getLeftArm() { return leftArm; }
    JointChain *getRightArm() { return rightArm; }
    JointChain *getHead() { return head; }
    JointChain *getWaist() { return waist; }

    /* 
     * This method will subsequently call the update methods
     * of the JointChains (arms, head and waist), and these
     * in turn will update the joints themselves.
     *
     * Remember to call this method in the main loop.
     */
    void update();

    /*
     * This method enables or disables torque to the motors
     */
    void setControlMode(int mode);

    /*
     * This method sets the maximum torque to all motors
     */
    void setMaxTorque(int torque);

    /*
     * This method sets a pose to the robot
     */
    void setPose(float lroll, float lpitch, float lyaw, float lelbow,
                 float rroll, float rpitch, float ryaw, float relbow,
                 float wroll, float wpitch, float wyaw,
                 float hpan, float htilt);

    void setPose(float pose[]);

    void setNormalizedPose(float lroll, float lpitch, float lyaw, float lelbow,
                           float rroll, float rpitch, float ryaw, float relbow,
                           float wroll, float wpitch, float wyaw,
                           float hpan, float htilt);

    void setNormalizedPose(float pose[]);

    /*
     * This method gets a pose from the robot
     */
    void getPose(float pose[]); //(&pose)[]);

    void getPose(float &lroll, float &lpitch, float &lyaw, float &lelbow,
                 float &rroll, float &rpitch, float &ryaw, float &relbow,
                 float &wroll, float &wpitch, float &wyaw,
                 float &hpan, float &htilt);

    void getNormalizedPose(float pose[]); //(&pose)[]);

    void getNormalizedPose(float &lroll, float &lpitch, float &lyaw, float &lelbow,
                           float &rroll, float &rpitch, float &ryaw, float &relbow,
                           float &wroll, float &wpitch, float &wyaw,
                           float &hpan, float &htilt);

    /*
     * This method performs a busy delay, calling the update
     * method while waiting the time to pass
     */
    void delay(double seconds);

    /*
     * This method ensures a uniform sampling time. It will
     * count the time elapsed since last call and wait only
     * the amount remaining to complete the required period
     */
    void tick(double seconds);

    /*
     * Same as above, but also performs update to the joints
     */
    void tickUpdate(double seconds);

};

#endif 
