/**
 * LED driver and GRAM instantiation.
 */
#ifndef DRIVER_H
#define DRIVER_H

#include "WS2812Serial.h"
#include "./../Installation.h"

// LED signal pin.
const int ledPin = 1;

// GRAM.
byte drawingMemory[numLeds * 3];
DMAMEM byte displayMemory[numLeds * 12];

// LED Driver.
WS2812Serial ledDriver(
    numLeds, 
    displayMemory, 
    drawingMemory, 
    ledPin, 
    WS2812_GRB
);

#endif
