#include "Motor.h"

Motor::Motor(Pin enable, Pin pin1, Pin pin2) 
    : m_Enable(enable), m_Pin1(pin1), m_Pin2(pin2) {
    pinMode(m_Enable, OUTPUT);
    pinMode(m_Pin1, OUTPUT);
    pinMode(m_Pin2, OUTPUT);

    analogWrite(m_Enable, 0);
}

Motor::~Motor() {
    analogWrite(m_Enable, 0);
    digitalWrite(m_Pin1, LOW);
    digitalWrite(m_Pin2, LOW);
}

void Motor::swap() {
    Pin temp = m_Pin1;
    m_Pin1 = m_Pin2;
    m_Pin2 = temp;
}

void Motor::drive(bool dir, int speed) const {
    analogWrite(m_Enable, speed);
    digitalWrite(m_Pin1, dir);
    digitalWrite(m_Pin2, dir ^ 1);
}

void Motor::stop() const {
    drive(0, 0);
}

void Motor::driveStop(bool dir, int speed, int duration) const {
    drive(dir, speed);
    delay(duration);
    stop();
}
