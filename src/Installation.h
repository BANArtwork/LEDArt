/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 140;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

// Individual segments.
const int numSegments = 10;
const Segment* segments[numSegments] = {
    new Segment(0, 14),
    new Segment(14, 14),
    new Segment(28, 14),
    new Segment(42, 14),
    new Segment(56, 14),
    new Segment(70, 14),
    new Segment(84, 14),
    new Segment(98, 14),
    new Segment(112, 14),
    new Segment(126, 14),
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
