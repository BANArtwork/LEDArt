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
const int numSegments = 10;
const Segment* segments[numSegments] = {
    new Segment(0, 21),
    new Segment(21, 5),
    new Segment(26, 5),
    new Segment(31, 5),
    new Segment(36, 5),
    new Segment(41, 5),
    new Segment(46, 5),
    new Segment(51, 5),
    new Segment(56, 5),
    new Segment(61, 5),
};

const Segment* arc = segments[0];
const int numHearts = 9;
const Segment** hearts = &segments[1];

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
