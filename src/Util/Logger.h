/**
 * Log utility.
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

void logSetup() {

    #ifdef USE_LOG
    Serial.begin(9600);
    uint32_t start = millis();
    while (!Serial && (millis() - start) < 4000) {;}
    if (Serial) Serial.println("Start");
    #endif
}

void log(char* msg) {
    #ifdef USE_LOG
    if (Serial) Serial.println(msg);
    #endif
}

void logSprintf(const char* fmt, ...) {
    #ifdef USE_LOG
    char buf[200];
    va_list args;
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
    if (Serial) Serial.print(buf);
    #endif
}

#endif
