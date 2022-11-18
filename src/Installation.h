/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 366;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

// const int numSegments = 14;
// const Segment* segments[numSegments] = {
//     new Segment(0, 32),
//     new Segment(32, 37),
//     new Segment(69, 43),
//     new Segment(112, 24),
//     new Segment(136, 20),
//     new Segment(156, 18),
//     new Segment(174, 18),
//     new Segment(192, 19),
//     new Segment(211, 23),
//     new Segment(234, 20),
//     new Segment(254, 8),
//     new Segment(262, 4),
//     new Segment(266, 3),
//     new Segment(269, 150)
// };

// const Segment* arcSegment = segments[13];

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
