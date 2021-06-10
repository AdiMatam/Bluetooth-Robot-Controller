#include "Robot.h"

Robot::Robot(Motor* lhs, Motor* rhs) {
    m_Lhs = lhs; 
    m_Rhs = rhs;
}

void Robot::drive(bool dir, int speed, int duration, bool seconds) const {
    if (seconds) duration *= 1000;
    m_Lhs->drive(dir, speed);
    m_Rhs->drive(dir, speed);
    delay(duration);
    m_Lhs->stop();
    m_Rhs->stop();   
}

void Robot::forward(int speed, int duration, bool seconds) const {
    drive(true, speed, duration, seconds);
}

void Robot::reverse(int speed, int duration, bool seconds) const {
    drive(false, speed, duration, seconds);
}

void Robot::stop() {
    m_Lhs->stop();
    m_Rhs->stop();
}
