#ifndef MOTOR_h
#define MOTOR_h

#include "PID.h"

// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  13

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     5000

struct Encoder { 
    Encoder(int pin_a, int pin_b) : pinA(pin_a), pinB(pin_b), pos(0), del(0){}

    int pinA; int pinB; int del;
    volatile int pos;
};

class Motor{
    public:
        Motor(int pinA, int pinB, int pinEN, int pinIN1, int pinIN2, int analogChannel, PID* pid);
        ~Motor();

    private:
        Encoder _encoder;
        int _pinEN, _pinIN1, _pinIN2;
        int _analogChannel;

        PID* _pid;

    /* public functions w/o robot kinematics => operate each wheel */
    public:
        /**
         * @brief turn one of the wheels
         * @param velocity wheel speed, m/s(or PWM)
         */
        void run(double velocity);

        /**
         * @brief stop all wheels
         */
        void stop();

    private:
        //to get Encoder
        void isrPinA();
        void isrPinB();


    private:
        /* auxiliary debouncing function                             */
        void debounce(int del) {
            for (int k=0;k<del;k++) {
                /* can't use delay in the ISR so need to waste some time
                perfoming operations, this uses roughly 0.1ms on uno  */
                k = k +0.0 +0.0 -0.0 +3.0 -3.0;
            }
        }
};

#endif