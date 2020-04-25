/*
" Copyright 2020 SGLee "
*/

#include "Arduino.h"

const byte ledPin = 13;
const byte r_interruptPin = 3;  // Photo-interrupter of the right wheel
const byte l_interruptPin = 2;  // Photo-interrupter of the left wheel
volatile byte state = LOW;
union Data {
    long int num; // NOLINT
    unsigned char ch[4];
} r_enc, l_enc;

void setup() {
  r_enc.num = 0;  // counting the pulse of the right wheel
  l_enc.num = 0;  // counting the pulse of the left wheel
  pinMode(ledPin, OUTPUT);
  pinMode(r_interruptPin, INPUT_PULLUP);
  pinMode(l_interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(r_interruptPin), right_count, FALLING);
  attachInterrupt(digitalPinToInterrupt(l_interruptPin), left_count, FALLING);
  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
}

void loop() {
  char incomingByte;
  digitalWrite(ledPin, state);
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    switch (incomingByte) {
    case 'w'  :
      Serial.print('l');
      Serial.print(l_enc.ch[0], DEC);
      break;  /* optional */
    case 'a'  :
      Serial.print(analogRead(A0)); Serial.print(' ');
      Serial.print(analogRead(A1)); Serial.print(' ');
      Serial.print(analogRead(A2)); Serial.print(' ');
      Serial.print(analogRead(A3)); Serial.print(' ');
      break;  /* optional */
    case 'r'  :
      analogWrite(5, 150); digitalWrite(4, 1); digitalWrite(6, 0);
      break; /* optional */
    case 'l'  :
      analogWrite(9, 250); digitalWrite(7, 1); digitalWrite(8, 0);
      while (1) {
        Serial.println(l_enc.ch[0], DEC);
        delay(10);
      }
      break; /* optional */
    case 'e' :
      analogWrite(5, 0); analogWrite(9, 0); break; /* optional */
    }
  }
}

void right_count() {
  // Chattering check. (if chattering, exit from this ISR.)
  delayMicroseconds(2000);  // Deay time is 2000 us = 2 ms.
  if (digitalRead(r_interruptPin) != LOW) return;
  // If the interrupt pin keeps LOW for the delay time, increase the count number.
  r_enc.num++;
}

void left_count() {
  // Chattering check. (if chattering, exit from this ISR.)
  delayMicroseconds(2000);  // Deay time is 2000 us = 2 ms.
  if (digitalRead(l_interruptPin) != LOW) return;
  // If the interrupt pin keeps LOW for the delay time, increase the count number.
  l_enc.num++;
}
