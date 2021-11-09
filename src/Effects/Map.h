#ifndef MAP_H
#define MAP_H

#include "LedMap.h"

const int NUM_LEDS = 316;

const int s0xMap[NUM_LEDS] = {
    1, 0, 2, 1, 2, 1, 2, 1
};

LedMap map0 = LedMap(NUM_LEDS, s0xMap, s0xMap, s0xMap);

#endif
