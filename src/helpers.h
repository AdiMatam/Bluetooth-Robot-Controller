#ifndef HELPERS_H
#define HELPERS_H

#include <Arduino.h>

// returns # of splits
// int split(String msg, char sep, String* out) {
//     int i = 0;
//     int space;
//     while (true) {
//         space = msg.indexOf(" ");
//         if (space == -1) {
//             out[i] = msg;
//             break;
//         }
//         out[i++] = msg.substring(0, space);
//         msg = msg.substring(space + 1); 
//     }
//     return i;
// }

// bool contains(const String& str, char value) {
//     for (int i = 0; i < str.length(); i++) {
//         if (str[i] == value)
//             return true;
//     }
//     return false;
// }

// void strip(String& msg, const String& chars) {
//     int index = msg.length() - 1;
//     while (contains(chars, msg[index]))
//         index--;
//     msg = msg.substring(0, index + 1);
// }

template <typename T>
void printArray(T args[], int len) {
    for (int i = 0; i < len; i++) {
        Serial.print(i);
        Serial.print(": " + args[i]);
    }
}


template <typename T>
bool between(T value, T low, T high) {
    return (low <= value) && (value <= high);
}

template <typename T>
void clamp(T& value, T low, T high) {
    value = min(high, max(value, low));
}

template <typename T>
T clampReturn(T value, T low, T high) {
    return min(high, max(value, low));
}



#endif

