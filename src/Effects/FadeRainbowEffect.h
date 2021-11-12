#ifndef FADERAINBOWEFFECT_H
#define FADERAINBOWEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief Fading rainbow effect.
 */
class FadeRainbowEffect : Effect {

    public:

        FadeRainbowEffect(int fadeStep, int speed) : 
            _fadeStep { fadeStep }, 
            _speed { speed } {}

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
            return fadeRainbow(
                _fadeStep, 
                _speed, 
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

        int _fadeStep;
        int _speed;

        static bool fadeRainbow(
            int fadeStep,
            int speed,
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t& newColor
        ) {
            // Get frame for this effect (frame / speed factor).
            unsigned int x = frame / speed;

            // Add LED index to create rainbow pattern.
            x = (ledIndex + x);

            // Multiply by fade step to set physical length of rainbow.
            x = x * fadeStep;
            
            // Mod by 768 to loop rainbow effect.
            x = x % 768;

            // Calculate RGB values for this step.
            uint8_t r, g, b;
            if (x < 256) {
                r = 255 - x;
                g = x;
                b = 0;
            } else if (x < 512) {
                r = 0;
                g = 511 - x;
                b = x - 256;
            } else {
                r = x - 512;
                g = 0;
                b = 767 - x;
            }

            // Set result and return true.
            newColor = rgbToUint32(r, g, b);
            return true;
        }
};

#endif
