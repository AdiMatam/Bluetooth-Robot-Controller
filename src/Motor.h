#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

// #define RBPI
#if defined(RBPI)
    enum Pin {
        P11, P12, P13, P15, P16, P18, P22, P7, P3, P5, P24, P26, P19, P21, P23, P8, P10
    };
#else
    typedef int Pin;
#endif

class Motor {
private:
    Pin m_Enable, m_Pin1, m_Pin2;
public:
    Motor() = default;
    Motor(Pin enable, Pin pin1, Pin pin2);
    ~Motor();
    void swap();
    void drive(bool dir, int speed) const;
    void stop() const;
};

#endif
