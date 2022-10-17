#ifndef CHASINGRAINBOWEFFECT_H
#define CHASINGRAINBOWEFFECT_H

#include "ChasingEffect.h"

/**
 * @brief Effect to create a chasing rainbow.
 */
class ChasingRainbowEffect : ChasingEffect {

    public:

        /**
         * @brief Construct a new Chasing Rainbow Effect object
         * 
         * @param frameDivisor Animation
         * @param animationLength 
         * @param reverseDirection 
         */
        ChasingRainbowEffect(
            int frameDivisor,
            int animationLength,
            bool reverseDirection = false
        ) : ChasingEffect(
            frameDivisor,
            animationLength,
            animationLength,
            animationLength,
            reverseDirection
        ), 
            _thirdLength { animationLength / 3 }
        {}

    private:

        int _thirdLength;

        // implementation of superclass 'getColor' method.
        uint32_t getColor(int index) {
            return getColor(_thirdLength, index);
        }

        /**
         * @brief Interpolate between R, G, and B values.
         * 
         * @param thirdLength Length of interpolation between each of the three colors.
         * @param x Index of the current LED we are calculating a color for.
         * 
         * @return uint32_t Color value calculated for the LED.
         */
        static uint32_t getColor(int thirdLength, int x) {
            if(x < thirdLength) {
                return interpolateColors(0x0000ff, 0xff0000, thirdLength, x);
            } else if (x < thirdLength * 2) {
                return interpolateColors(0xff0000, 0x00ff00, thirdLength, x - thirdLength);
            } else {
                return interpolateColors(0x00ff00, 0x0000ff, thirdLength, x - (thirdLength * 2));
            }
        }
};

#endif
