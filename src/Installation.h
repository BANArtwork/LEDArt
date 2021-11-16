/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 307;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

// Individual segments.
const int numSegments = 10;
const Segment* segments[numSegments] = {
    new Segment(0, 30),
    new Segment(30, 19),
    new Segment(49, 38),
    new Segment(87, 31),
    new Segment(118, 30),
    new Segment(148, 29),
    new Segment(177, 31),
    new Segment(208, 59),
    new Segment(267, 19),
    new Segment(286, 21),
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
