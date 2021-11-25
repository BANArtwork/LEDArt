#ifndef FIREEFFECT_H
#define FIREEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"
#include "./../Util/Colors.h"

class FireEffect : Effect {

    public:

        FireEffect(int speed, int frequency, int rand) : 
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
            
            auto state = fire(
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

            if (state == LAST_FRAME) {
                _rand = rand();
            }

            return (state == FADING);
        }

    private:

        int _speed;
        int _frequency;
        int _rand;

        enum state {
            FADING,
            LAST_FRAME,
            BLACK    
        };
            
        static const uint32_t orange = 0xffc800;

        static state fire(
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
            } else if (x == 512) {
                return LAST_FRAME;
            } else {
                return BLACK;
            }

            uint32_t f = interpolateColors(0, orange, 255, w);
            uint8_t fR, fG, fB;
            uint32toRgb(f, fR, fG, fB);

            // Get greater of current color or white value.
            uint8_t r, g, b;
            uint32toRgb(currentColor, r, g, b);
            r = (fR > r) ? fR : r;
            g = (fG > g) ? fG : g;
            b = (fB > b) ? fB : b;

            // Set result and return true.
            newColor = rgbToUint32(r, g, b);
            return FADING; 
        }
};

#endif
