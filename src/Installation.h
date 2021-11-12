/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 220;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

// Main arc segment.
const Segment mainArcSegment = Segment(0, 134);

// Spoke segments.
const int numberOfSpokes = 11;
const Segment* spokeSegments[numberOfSpokes] = {
    new Segment(134, 9),
    new Segment(143, 4),
    new Segment(147, 3),
    new Segment(150, 4),
    new Segment(154, 12),
    new Segment(166, 14),
    new Segment(180, 12),
    new Segment(192, 5),
    new Segment(197, 5),
    new Segment(202, 6),
    new Segment(208, 12),
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
