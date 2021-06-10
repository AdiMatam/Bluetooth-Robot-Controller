#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int trig, int echo)
    : m_Trig(trig), m_Echo(echo) {

    pinMode(m_Trig, OUTPUT);
    pinMode(m_Echo, INPUT);
}

int Ultrasonic::getDistanceCentimeter() {
    digitalWrite(m_Trig, 1);
    delayMicroseconds(10);
    digitalWrite(m_Trig, 0);

    float duration = pulseIn(m_Echo, 1);
    return int(duration * 0.034f / 2.f); // cm distance
}

