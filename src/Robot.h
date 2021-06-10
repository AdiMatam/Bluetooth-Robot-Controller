#ifndef ROBOT_H
#define ROBOT_H

#include "Motor.h"

class Robot {
private:
    Motor* m_Lhs;
    Motor* m_Rhs;
public:
    Robot() = default;
    Robot(Motor* lhs, Motor* rhs);
    ~Robot() = default;
    void drive(bool dir, int speed, int duration, bool seconds=false) const;
    void forward(int speed, int duration, bool seconds=false) const;
    void reverse(int speed, int duration, bool seconds=false) const;
    void stop();
};

#endif
