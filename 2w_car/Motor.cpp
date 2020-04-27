#include "Motor.h"
#include <Arduino.h>

Motor::Motor(int pinA, int pinB, int pinEN, int pinIN1, int pinIN2, int analogChannel, PID* pid) :
_encoder(pinA, pinB), _pinEN(pinEN), _pinIN1(pinIN1), _pinIN2(pinIN2),  //motor pin configuration
_analogChannel(analogChannel), _pid(pid)
{
    // set Encoder pins  
    pinMode(_encoder.pinA, INPUT);
    pinMode(_encoder.pinB, INPUT);

    // turn on pullup resistors
    digitalWrite(_encoder.pinA, HIGH);
    digitalWrite(_encoder.pinB, HIGH);

    // encoder pin on interrupts -> callback 함수가 연결이 안됨!!!
    //attachInterrupt(_encoder.pinA, Motor::isrPinA, HIGH);
    //attachInterrupt(_encoder.pinB, Motor::isrPinB, HIGH);

    // configure motor PWM functionalities
    ledcSetup(_analogChannel, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
    
    // attach led pin to analog pin
    ledcAttachPin(_pinEN, _analogChannel);

    // set pin mode for change directions
    pinMode(_pinIN1, OUTPUT);
    pinMode(_pinIN2, OUTPUT);
}

Motor::~Motor(){
    delete _pid;
}

void Motor::run(double velocity){

}

void Motor::stop(){

}


/* Interrupt Service Routine: change on pin A for Encoder 0  */
void Motor::isrPinA(){
  int drB = digitalRead(_encoder.pinB); /* read pin B right away */
  debounce(_encoder.del);   /* possibly wait before reading pin A, then read it */
  int drA = digitalRead(_encoder.pinA);

  /* this updates the counter                                */
  if (drA == HIGH) {   /* low->high on A? */ 
    if (drB == LOW) _encoder.pos++;  /* going clockwise: increment by checking pin B */  
    else _encoder.pos--;  /* going counterclockwise: decrement  */
  } else {                       /* must be high to low on A */
    if (drB == HIGH) _encoder.pos++;  /* going clockwise: increment by checking pin B */
    else _encoder.pos--;  /* going counterclockwise: decrement  */
  } /* end counter update                                    */
} /* end ISR pin A Encoder 0                                 */

/* Interrupt Service Routine: change on pin B for Encoder 0  */
void Motor::isrPinB(){ 
  int drA = digitalRead(_encoder.pinA); /* read pin A right away */
  debounce(_encoder.del);   /* possibly wait before reading pin B, then read it */
  int drB = digitalRead(_encoder.pinB);

  /* this updates the counter                                */
  if (drB == HIGH) {   /* low->high on B? */
    if (drA == HIGH) _encoder.pos++;  /* going clockwise: increment by checking pin A */
    else _encoder.pos--;  /* going counterclockwise: decrement  */
  } else {                       /* must be high to low on B */
    if (drA == LOW) _encoder.pos++;  /* going clockwise: increment check pin A */
    else _encoder.pos--;  /* going counterclockwise: decrement  */
  } /* end counter update */
} /* end ISR pin B Encoder 0  */
