/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 421;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

// Individual segments.
const int numSegments = 11;
const Segment* segments[numSegments] = {
    new Segment(0, 24),
    new Segment(24, 10),
    new Segment(34, 10),
    new Segment(243, 10),
    new Segment(208, 14),
    new Segment(391, 20),
    new Segment(411, 10),
    new Segment(44, 21),
    new Segment(118, 90),
    new Segment(222, 21),
    new Segment(253, 61),
    
};

const int numCircles = 6;
const Segment* circles[numCircles] = {
    segments[1],
    segments[2],
    segments[3],
    segments[4],
    segments[5],
    segments[6],
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
