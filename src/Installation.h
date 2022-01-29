/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 442;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

// Individual segments.
const int numSegments = 14;
const Segment* segments[numSegments] = {
    new Segment(0, 24), // First two Ls.
    new Segment(24, 10), // First circle.
    new Segment(34, 10), // Circle 2.
    new Segment(44, 21), // Straight segments left of eye.
    new Segment(65, 20), // L segment left of eye.
    new Segment(85, 33), // Left eye.
    new Segment(118, 111), // Straight segments top left.
    new Segment(229, 14), // Circle 3.
    new Segment(243, 21), // Straight segment top middle
    new Segment(264, 10), // Circle 4.
    new Segment(274, 61), // Straight segments top right.
    new Segment(335, 77), // Right eye spiral.
    new Segment(412, 20), // Circle 5.
    new Segment(432, 10), // Circle 6.
};

const int numCircles = 6;
const Segment* circles[numCircles] = {
    segments[1],
    segments[2],
    segments[7],
    segments[9],
    segments[12],
    segments[13],
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
