#ifndef SPARKLEEFFECT_H
#define SPARKLEEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief Effect to create random sparkles.
 */
class SparkleEffect : Effect {

    public:

        SparkleEffect(int speed, int frequency, int rand) : 
            _speed { speed }, 
            _frequency { frequency },
            _rand { rand } {}
        
        bool effectAction(
            uint32_t ledX, 
            uint32_t ledY, 
            uint32_t ledZ, 
            uint32_t ledIndex, 
            uint32_t frame,
            uint32_t currentColor, 
            uint32_t previousColor,
            uint32_t& newColor
        ) {
            return sparkle(
                _speed,
                _frequency, 
                _rand,
                ledX, 
                ledY, 
                ledZ, 
                ledIndex, 
                frame, 
                currentColor, 
                newColor
            );
        }

    private:

        int _speed;
        int _frequency;
        int _rand;

        static bool sparkle(
            int speed,
            int frequency,
            int rand,
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t& newColor
        ) {
            // Calculate var for sparkle animation.
            unsigned int x = frame + rand;
            x = x % frequency;
            x = x * speed;
            uint8_t w;

            // Fade up.
            if (x < 256) {
                w = x;

            // Fade down.
            } else if (x < 512) {
                w = 511 - x;

            // No sparkle.
            } else {
                return false;
            }

            // Get greater of current color or white value.
            uint8_t r, g, b;
            uint32toRgb(currentColor, r, g, b);
            r = (w > r) ? w : r;
            g = (w > g) ? w : g;
            b = (w > b) ? w : b;

            // Set result and return true.
            newColor = rgbToUint32(r, g, b);
            return true; 
        }
};

#endif
