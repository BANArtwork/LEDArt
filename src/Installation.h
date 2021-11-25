/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 66;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

// Individual segments.
const int numSegments = 14;
const Segment* segments[numSegments] = {
    new Segment(0, 3),
    new Segment(3, 3),
    new Segment(6, 3),
    new Segment(9, 3),
    new Segment(12, 3),
    new Segment(15, 3),
    new Segment(18, 2),
    new Segment(20, 2),
    new Segment(22, 2),
    new Segment(24, 3),
    new Segment(27, 3),
    new Segment(30, 3),
    new Segment(33, 3),
    new Segment(36, 3)
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
