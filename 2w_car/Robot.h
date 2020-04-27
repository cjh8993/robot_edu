#ifndef ROBOT_h
#define ROBOT_h

#include "Motor.h"

class MobileRobot{
    public:
        MobileRobot();
        ~MobileRobot();

    private:
        Motor* wheel[2];


    /* public functions for robot kinematics */
    public:
        /**
         * @brief move robot w/ linear and angular velocity
         * @param linear linear velocity, m/s
         * @param angular angular velocity, m/s
         */
        void move(double linear, double angular);

        /**
         * @brief stop robot
         */
        void stop();
};

#endif