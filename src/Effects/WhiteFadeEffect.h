#ifndef WHITEFADEEFFECT_H
#define WHITEFADEEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"
#include "./../Hardware/Segment.h"
#include "../Util/Logger.h"

class WhiteFadeEffect : Effect {

    public:

        WhiteFadeEffect(
            int stripeLength,
            int fadeSpeed,
            int animationWindow
        ) : 
            _stripeLength { stripeLength },
            _fadeSpeed { fadeSpeed },
            _animationWindow { animationWindow } {}
            
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
            return effect(_stripeLength, _fadeSpeed, _animationWindow, ledIndex, frame, 0, newColor);
        }

    private:

    int _stripeLength;
    int _fadeSpeed;
    int _animationWindow;

    static bool effect(
        int stripeLength,
        int fadeSpeed,
        int animationWindow,
        int ledIndex, 
        unsigned int frame,
        uint32_t currentColor, 
        uint32_t& newColor
    ) {
        int window = animationWindow + ledIndex;
        int x = frame / fadeSpeed;
        if (x > window) {
            logSprintf("No fade");
            return false;
        }
int c;

int half = window / 2;
        // Fading up:
        if (x < half) {

             c = (0xff * x) / half;

            logSprintf("Fade up: %08x", c);
        // Fading down:
        } else {
            c = (0xff * (window - x)) / half;
            logSprintf("Fade down: %08x", c);
        }

        newColor = rgbToUint32(c, c, c);
    }
};

#endif
