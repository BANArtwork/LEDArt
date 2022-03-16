/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 289;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

// Individual segments.
const int numSegments = 10;
const Segment* segments[numSegments] = {
    new Segment(3, 47),
    new Segment(50, 12),
    new Segment(68, 75),
    new Segment(143, 12),
    new Segment(155, 10),
    new Segment(165, 9),
    new Segment(174, 21),
    new Segment(195, 33),
    new Segment(228, 31),
    new Segment(272, 16),
};

const int numStars = 21;
const Segment* stars[numStars] = {
    new Segment(0, 1),
    new Segment(1, 1),
    new Segment(2, 1),
    new Segment(62, 2),
    new Segment(64, 1),
    new Segment(65, 1),
    new Segment(66, 1),
    new Segment(67, 1),
    new Segment(259, 1),
    new Segment(260, 1),
    new Segment(261, 1),
    new Segment(262, 1),
    new Segment(263, 1),
    new Segment(264, 1),
    new Segment(265, 1),
    new Segment(266, 1),
    new Segment(267, 2),
    new Segment(269, 1),
    new Segment(270, 1),
    new Segment(271, 1),
    new Segment(288, 1),
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
