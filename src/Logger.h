#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

//#define USE_LOG

void logSetup() {

    #ifdef USE_LOG
    // Init serial.
    Serial.begin(9600);
    while (!Serial) {;}
    Serial.println("Start");
    #endif
}

void log(char* msg) {
    #ifdef USE_LOG
    Serial.println(msg);
    #endif
}

void logSprintf(const char* fmt, ...) {
    #ifdef USE_LOG
    char buf[100];
    va_list args;
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
    Serial.print(buf);
    #endif
}

#endif
