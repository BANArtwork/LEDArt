/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 335;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

const int numStars = 7;
const Segment* stars[numStars] = {
    new Segment(0, 4),
    new Segment(7, 1),
    new Segment(236, 4),
    new Segment(240, 1),
    new Segment(302, 1),
    new Segment(303, 4),
    new Segment(320, 1)
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
