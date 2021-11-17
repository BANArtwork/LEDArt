/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 212;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

// Individual segments.
const int numSegments = 14;
const Segment* segments[numSegments] = {
    new Segment(0, 4),
    new Segment(4, 7),
    new Segment(11, 6),
    new Segment(17, 4),
    new Segment(21, 64),
    new Segment(85, 4),
    new Segment(89, 7),
    new Segment(96, 5),
    new Segment(101, 6),
    new Segment(107, 4),
    new Segment(111, 7),
    new Segment(118, 6),
    new Segment(124, 81),
    new Segment(205, 7),
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
