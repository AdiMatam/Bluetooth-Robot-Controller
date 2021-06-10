#include <Arduino.h>

// #define BLUETOOTH_TEST
// #define MOTOR_DEBUG

#if defined(BLUETOOTH_TEST)
#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(0, 1);

char c=' ';
void setup() 
{
  Serial.begin(9600);
  Serial.println("ready");
  Bluetooth.begin(38400);
}

void loop() 
{
  if(Bluetooth.available())
  {
    c=Bluetooth.read();
    Serial.write(c);
  }
  if(Serial.available())
  {
    c=Serial.read();
    Bluetooth.write(c);
  }
}
#else
#include "Robot.h"
#include "buttons.h"
#include "helpers.h"

Motor left(2, 3, 4);
Motor right(9, 8, 10);
// Robot robot(&left, &right);
int speed = 255;

#if defined(MOTOR_DEBUG)

void ho() {

}

#else
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

    else if (command == "forward") {
        left.drive(true, speed);
        right.drive(true, speed);
        return;
    }

    else if (command == "reverse") {
        left.drive(false, speed);
        right.drive(false, speed);
        return;
    }

    // MIGHT HAVE ARGS
    String args[4];
    split(msg.substring(space + 1), ' ', args);
    printArray(args, 4);
    Serial.println("Finished parse");

    if (command == "speed")
        speed = args[0].toInt();
}

#endif


void runMain() {
#if defined(MOTOR_DEBUG)
    right.drive(true, speed);
    delay(1000 * 50);
    right.stop();
#else
    String previousRead = "";
    String currentRead = "";
    while (true) {
        if (Serial.available() > 0) {
            currentRead = Serial.readString();
            Serial.println(currentRead);
        }
        if (currentRead.startsWith(".") and currentRead.length() >= 1 and
            currentRead != previousRead) {
            
            strip(currentRead, " \r\n");
            currentRead.toLowerCase();
            parseAction(currentRead);
            previousRead = currentRead;
        }
    }
#endif
}

void setup() {
    Serial.begin(9600);
    runMain();
}

#endif

void loop() {}