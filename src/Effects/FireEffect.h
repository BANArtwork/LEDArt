#ifndef FIREEFFECT_H
#define FIREEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"
#include "./../Util/Colors.h"

class FireEffect : Effect {

    public:

        FireEffect(int fadeStep, int speed, int loopLength) : 
            _fadeStep { fadeStep }, 
            _speed { speed },
            _loopLength { loopLength } {}

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
            return fire(
                _loopLength,
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
        int _loopLength;


        static const uint32_t c1 = 0xff0000;
        static const uint32_t c2 = 0xfc8c03;
        static const uint32_t c3 = 0xffffff;

        static bool fire(
            int loopLength,
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
            x = x % loopLength;

            // Calculate RGB values for this step.
            uint8_t r, g, b;
            uint8_t r1, g1, b1;
            uint8_t r2, g2, b2;
            if (x < loopLength / 2) {
                uint32toRgb(c1, r1, g1, b1);
                uint32toRgb(c2, r2, g2, b2);

            } else {
                uint32toRgb(c2, r1, g1, b1);
                uint32toRgb(c1, r2, g2, b2);
            }

                r = (r2 - r1) * x + r1;
                g = (g2 - g1) * x + g1;
                b = (b2 - b1) * x + b1;

            // Set result and return true.
            newColor = rgbToUint32(r, g, b);
            return true;
        }
};

#endif
