/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 543;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

// Individual segments.
const int numSegments = 12;
const Segment* segments[numSegments] = {
    new Segment(0, 39),
    new Segment(39, 54),
    new Segment(93, 46),
    new Segment(139, 42),
    new Segment(181, 49),
    new Segment(230, 45),
    new Segment(275, 42),
    new Segment(317, 50),
    new Segment(367, 43),
    new Segment(410, 48),
    new Segment(449, 50),

    new Segment(499, 44),
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
