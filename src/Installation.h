/**
 * This file contains information about the physical installation.
 */
#ifndef INSTALLATION_H
#define INSTALLATION_H

#include "Hardware/Segment.h"
#include "./Hardware/LedMap.h"

// Total number of LEDs in the piece.
const int numLeds = 364;

// A segment of all the LEDs.
const Segment allLedsSegment = Segment(0, numLeds);

// Individual segments.
const int numSegments = 50;
const Segment* segments[numSegments] = {
    new Segment(0, 29), // 0
    new Segment(29, 25),
    new Segment(54, 4),
    new Segment(58, 4),
    new Segment(62, 4),
    new Segment(66, 4),
    new Segment(70, 4),
    new Segment(74, 4),
    new Segment(78, 4),
    new Segment(82, 2),
    new Segment(84, 2), // 10
    new Segment(86, 2),
    new Segment(88, 2),
    new Segment(90, 2),
    new Segment(92, 2),
    new Segment(94, 2),
    new Segment(96, 2),
    new Segment(98, 2),
    new Segment(100, 8),
    new Segment(108, 11),
    new Segment(119, 8), // 20
    new Segment(127, 2),
    new Segment(129, 2),
    new Segment(131, 2),
    new Segment(133, 2),
    new Segment(135, 2),
    new Segment(137, 2),
    new Segment(139, 2),
    new Segment(141, 2),
    new Segment(143, 2),
    new Segment(145, 2), // 30
    new Segment(147, 2),
    new Segment(149, 2),
    new Segment(151, 2),
    new Segment(153, 21),
    new Segment(174, 10),
    new Segment(184, 8),
    new Segment(192, 10),
    new Segment(202, 14),
    new Segment(216, 19),
    new Segment(235, 26), // 40
    new Segment(261, 19),
    new Segment(280, 8),
    new Segment(288, 11),
    new Segment(299, 8),
    new Segment(307, 4),
    new Segment(311, 6),
    new Segment(317, 4),
    new Segment(321, 17),
    new Segment(338, 26),
};

const int outerEyeRingSegmentCount = 7;
const Segment* outerEyeRing[outerEyeRingSegmentCount] = {
    segments[2],
    segments[3],
    segments[4],
    segments[5],
    segments[6],
    segments[7],
    segments[8],
};

const int innerEyeRingSegmentCount = 22;
const Segment* innerEyRing[innerEyeRingSegmentCount] = {
    segments[9],
    segments[10],
    segments[11],
    segments[12],
    segments[13],
    segments[14],
    segments[15],
    segments[16],
    segments[17],
    segments[21],
    segments[22],
    segments[23],
    segments[24],
    segments[25],
    segments[26],
    segments[27],
    segments[28],
    segments[29],
    segments[30],
    segments[31],
    segments[32],
    segments[33],
};

const int eyeSegmentCount = 3;
const Segment* ringedEye[eyeSegmentCount] = {
    segments[18],
    segments[19],
    segments[20],
};

const Segment* otherEye[eyeSegmentCount] = {
    segments[42],
    segments[43],
    segments[44],
};

const int mouthSegmentCount = 3;
const Segment* mouth[mouthSegmentCount] = {
    segments[45],
    segments[46],
    segments[47],
};

const int stripeSegmentCount = 12;
const Segment* stripes[stripeSegmentCount] = {
    segments[0],
    segments[1],
    segments[34],
    segments[35],
    segments[36],
    segments[37],
    segments[38],
    segments[39],
    segments[40],
    segments[41],
    segments[48],
    segments[49],
};

// Maps of the physical coordinates of each LED.
// TODO 
const int s0xMap[numLeds] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(numLeds, s0xMap, s0xMap, s0xMap);

#endif
