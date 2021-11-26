#ifndef TWOCOLORFADEEFFECT_H
#define TWOCOLORFADEEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"

class TwoColorFadeEffect : Effect {

    public:

        TwoColorFadeEffect(
            int fadeLength, 
            int frameSpeed, 
            int animationWindow, 
            uint32_t color1, 
            uint32_t color2
        ) : 
            _fadeLength { fadeLength }, 
            _frameSpeed { frameSpeed },
            _animationWindow { animationWindow },
            _color1 { color1 },
            _color2 { color2 } {}

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
            return effect(
                _fadeLength,
                _frameSpeed,
                _animationWindow,
                _color1,
                _color2,
                ledIndex, 
                frame, 
                currentColor, 
                newColor
            );
        }

    private:

        int _fadeLength;
        int _frameSpeed;
        int _animationWindow;
        uint32_t _color1;
        uint32_t _color2;

        static bool effect(
            int fadeLength, 
            int frameSpeed, 
            int animationWindow,
            uint32_t color1,
            uint32_t color2,
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t& newColor
        ) {

            // Divide frame for animation speed.
            int x = frame / frameSpeed;

            // Add LED index to create fade.
            x += ledIndex;

            // Mod by animation window to set repeat frequency.
            x %= animationWindow;

            // If we are past the fade length then do nothing.
            if (x > fadeLength) return false;

            // Get max fade value.
            int fadeMax = fadeLength / 2;

            uint32_t c;

            // Fading up:
            if (x < fadeLength / 2) {
                c = interpolateColors(color1, color2, fadeMax, x);

            // Fading down:
            } else {
                c = interpolateColors(color1, color2, fadeMax, fadeLength - x);
            }

            // Set result and return true.
            newColor = c;
            return true;
        }
};

#endif
