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

#endif
