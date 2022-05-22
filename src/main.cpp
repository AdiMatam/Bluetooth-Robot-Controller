#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ArduinoBlue.h>
#include "Robot.h"
#include "Ultrasonic.h"
#include "helpers.h"

// #define MOTOR_DEBUG
// #define NO_OP
// #define WALL_FOLLOW

#if defined(NO_OP)
void setup() {}
void loop() {}
#else
SoftwareSerial bluetooth(5, 6);
ArduinoBlue phone(bluetooth);
Motor left(3, 2, 4);
Motor right(9, 8, 10);
Ultrasonic sonic(11, 12);

#if !defined(MOTOR_DEBUG) and !defined(WALL_FOLLOW)

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
    while (true) {
        int distance = side.getDistanceCentimeter();
        Serial.println(distance);
        delay(1000);
    }
#elif defined(WALL_FOLLOW)
    const int goalDistance = 25;
    int currDistance;
    const int normalSpeed = 200;
    int speedDelta;
    bool connected = false;

    while (true) {
        // delay(200);
        int but = phone.getButton();
        if (but == 1) {
            phone.sendText("Toggle connection");
            connected = !connected;
        }
        currDistance = sonic.getDistanceCentimeter();
        if (but == 2)
            phone.sendText(String(currDistance));
        if (currDistance > 500) 
            continue;
        if (connected) {
            speedDelta = abs(goalDistance - currDistance) * 2; // generate positive #
            if (currDistance >= goalDistance + 2)
                speedDelta *= -1;
            left.drive(true,  
                clampReturn(normalSpeed + speedDelta, normalSpeed - 30, normalSpeed + 30)
            );
            right.drive(true, 
                clampReturn(normalSpeed - speedDelta, normalSpeed - 30, normalSpeed + 30)
            );
        }
        else {
            left.stop(); right.stop();
        }
    }   
#else
    runBot(phone.getSteering(), phone.getThrottle());
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

