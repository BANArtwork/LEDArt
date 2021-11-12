/**
 * Methods for color conversion.
 */
#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

/**
 * @brief Utility method to comvert RGB values to a 32 bit color value.
 * 
 * @param r 
 * @param g 
 * @param b 
 * @return uint32_t 
 */
inline uint32_t rgbToUint32(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 16) | (g << 8) | b;
}

/**
 * @brief Utility method to convert a 32 bit color to RGB values.
 * 
 * @param c 
 * @param r 
 * @param g 
 * @param b 
 */
inline void uint32toRgb(uint32_t c, uint8_t& r, uint8_t& g, uint8_t& b) {
    r = (c & 0x00FF0000) >> 16;
    g = (c & 0x0000FF00) >> 8;
    b = (c & 0x000000FF);
}

uint32_t interpolateColors(uint32_t c1, uint32_t c2, uint32_t max, uint32_t val) {
    
    uint8_t r1, g1, b1;
    uint8_t r2, g2, b2;
    uint32toRgb(c1, r1, g1, b1);
    uint32toRgb(c2, r2, g2, b2);

    int rDif, gDif, bDif;

    rDif = (int)r2 - (int)r1;
    gDif = (int)g2 - (int)g1;
    bDif = (int)b2 - (int)b1;

    int v = val;
    int m = max;

    int r, g, b;
    r = ((rDif * v) / m) + r1;
    g = ((gDif * v) / m) + g1;
    b = ((bDif * v) / m) + b1;

    return rgbToUint32(r, g, b);
}

#endif
