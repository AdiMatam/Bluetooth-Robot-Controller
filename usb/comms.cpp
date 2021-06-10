#include <iostream>
#include "Serial.h"

int main() {
    Serial* port = new Serial("COM3");
    if (!port->IsConnected()) {
        std::cout << "Not connected!" << std::endl;
        return -1;
    }
    std::string msg;
    while (true) {
        std::cin >> msg;
        if (msg == "kill") 
            break;
        port->WriteData(msg.c_str(), msg.size());
    }
    return 0;
}

    // char data[4] = "";
    // char command[2] = "";
    // int datalength = 4;  //length of the data,
    // int readResult = 0;
    // int n;

    // for (int i = 0; i < 4; ++i) { data[i] = 0; } //initial the data array

    // //read from user input 
    // //this is where I added while loop 
    // // while(1){
    // std::cout << "Enter your command: ";
    // std::cin.get(command, 2);     //input command 
    // int msglen = strlen(command);
    // if (port->WriteData(command, msglen));   //write to arduino
    // printf("\n(writing success)\n");
