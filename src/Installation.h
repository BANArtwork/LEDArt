/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 175;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

const int numStars = 7;
const Segment* stars[numStars] = {
    new Segment(0, 4),
    new Segment(4, 1),
    new Segment(35, 1),
    new Segment(94, 1),
    new Segment(95, 4),
    new Segment(128, 1),
    new Segment(129, 1)
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
