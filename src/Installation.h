/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 297;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

// Individual segments.
const int numSegments = 13;
const Segment* segments[numSegments] = {
    new Segment(0, 2),
    new Segment(2, 3),
    new Segment(5, 25),
    new Segment(30, 38),
    new Segment(68, 48),
    new Segment(116, 20),
    new Segment(136, 10),
    new Segment(146, 29),
    new Segment(175, 96),
    new Segment(271, 12),
    new Segment(283, 3),
    new Segment(286, 9),
    new Segment(295, 2),
};

const Segment* shortArc = segments[4];
const Segment* longArc = segments[8];

const int numBalls = 4;
const Segment* balls[numBalls] = {
    segments[0],
    segments[1],
    segments[10],
    segments[12],
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
