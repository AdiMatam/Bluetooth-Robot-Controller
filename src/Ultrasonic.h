#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Arduino.h"

class Ultrasonic {
private:
    int m_Trig, m_Echo;
public:
    Ultrasonic(int trig, int echo);
    int getDistanceCentimeter();
};

#endif