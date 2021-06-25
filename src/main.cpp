#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ArduinoBlue.h>
#include "Robot.h"
#include "buttons.h"
#include "helpers.h"

// #define MOTOR_DEBUG
// #define NO_OP

#if defined(NO_OP)
void setup() {}
void loop() {}
#else
SoftwareSerial bluetooth(5, 6);
ArduinoBlue phone(bluetooth);
Motor left(3, 2, 4);
Motor right(9, 8, 10);
// Robot robot(&left, &right);

#if !defined(MOTOR_DEBUG)

void runBot(int steering, int throttle) {
    // delay(1000);
    steering -= 49;
    throttle -= 49;
    clamp(steering, -48, 48);
    clamp(throttle, -48, 48);
    // Serial.print("Steering: ");
    // Serial.println(steering);
    // Serial.print("Throttle: ");
    // Serial.println(throttle);
    if (between(steering, -2, 2) && between(throttle, -2, 2)) {
        // Serial.println("stopping");
        left.stop();
        right.stop();
    }
    else if (between(throttle, 0, 49)) {
        Serial.println(throttle);
        // fromLow, fromHigh, toLow, toHigh
        const int constantSpeed = 255;
        int variableSpeed = map(abs(steering), 0, 48, 100, constantSpeed);
        if (steering < -2) {
            left.drive(true, variableSpeed);
            right.drive(true, constantSpeed);
        }
        if (steering > +2) {
            left.drive(true, constantSpeed);
            right.drive(true, variableSpeed);
        }
    }
}

#endif

void runMain() {
#if defined(MOTOR_DEBUG)
    Motor* motors[2] = {&left, &right};
    for (int dir = 0; dir < 2; dir++) {
        for (int index = 0; index < 2; index++)
            motors[index]->driveStop(bool(dir), speed, 2000);
    }
#else
    // speed window = 150->255
    // steering domain => 0->99
    // throttle domain => 0, 49, 99
    // slider => 0->200
    bool power = false;
    bool forward = true;
    int steering = 0; 
    
    while (true) {
        int button = phone.getButton();
        if (phone.getSliderId() == 0) {
            steering = phone.getSliderVal() - 100;
            // Serial.println(steering);
        }
        if (button == 1)
            power ^= 1;
        else if (button == 2)
            forward ^= 1;

        int throttle = 49 - phone.getThrottle();
        clamp(throttle, -45, 45);
        if (abs(throttle) >= 25) {
            const int constantSpeed = 255;
            forward = throttle < 0;
            steering = 49 - phone.getSteering();
            clamp(steering, -45, 45);

            if (steering == 0) {
                left.drive(forward, constantSpeed);
                right.drive(forward, constantSpeed);
            }
            else {
                int variableSpeed = map(abs(steering), 45, 0, 0, constantSpeed);
                if (steering > 0) {
                    left.drive(forward, variableSpeed);
                    right.drive(forward, constantSpeed);
                }
                else {
                    left.drive(forward, constantSpeed);
                    right.drive(forward, variableSpeed);
                }
            }
        }
        else {
            left.stop();
            right.stop();
        }
    }
#endif
}
void setup() {
    Serial.begin(9600);
    bluetooth.begin(9600);
    delay(100);
    Serial.println("ready");
    runMain();
}

void loop() {}
#endif

/*
String previousRead = "";
String currentRead = "";

if ((currentRead = phone.getText()) != "") {
    delay(2000);
    Serial.println(phone.getThrottle());
    Serial.println(phone.getSteering());
    Serial.println(currentRead);
}
if (currentRead.startsWith(".") and currentRead.length() >= 1 and
    currentRead != previousRead) {

    strip(currentRead, " \r\n");
    currentRead.toLowerCase();
    parseAction(currentRead);
    previousRead = currentRead;
}
void parseAction(String& msg) {
    int space = msg.indexOf(' ');
    if (space == -1) 
        space = msg.length();
    String command = msg.substring(1, space);
    
    // NO ARGS
    if (command == "stop") {
        left.stop();
        right.stop();
        return;
    }

    else if (command == "f" or command == "forward") {
        left.drive(true, speed);
        right.drive(true, speed);
        return;
    }

    else if (command == "r" or command == "reverse") {
        left.drive(false, speed);
        right.drive(false, speed);
        return;
    }

    // MIGHT HAVE ARGS
    String args[4];
    split(msg.substring(space + 1), ' ', args);

    if (command == "speed") {
        speed = args[0].toInt();
        Serial.print("Set Speed: ");
        Serial.println(speed);
    }
}



*/

