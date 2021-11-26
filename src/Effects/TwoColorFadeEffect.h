#ifndef TWOCOLORFADEEFFECT_H
#define TWOCOLORFADEEFFECT_H

#include "Effect.h"
#include "../Hardware/Segment.h"
#include "./../Util/ColorConverters.h"

class TwoColorFadeEffect : Effect {

    public:

        TwoColorFadeEffect(
            Segment* segment,
            int fadeLength, 
            int frameSpeed, 
            int animationWindow, 
            uint32_t color1, 
            uint32_t color2,
            bool reverse = false
        ) : 
            _segment { segment },
            _fadeLength { fadeLength }, 
            _frameSpeed { frameSpeed },
            _animationWindow { animationWindow },
            _color1 { color1 },
            _color2 { color2 },
            _reverse { reverse } {}

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
                _segment,
                _fadeLength,
                _frameSpeed,
                _animationWindow,
                _color1,
                _color2,
                _reverse,
                ledIndex, 
                frame, 
                currentColor, 
                newColor
            );
        }

    private:

        Segment* _segment;
        int _fadeLength;
        int _frameSpeed;
        int _animationWindow;
        uint32_t _color1;
        uint32_t _color2;
        bool _reverse;

        static bool effect(
            Segment* segment,
            int fadeLength, 
            int frameSpeed, 
            int animationWindow,
            uint32_t color1,
            uint32_t color2,
            bool reverse,
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t& newColor
        ) {

            // Divide frame for animation speed.
            int x = frame / frameSpeed;

            // Get offset of LED index and fade direction.
            int offset = (ledIndex - segment->getStart());
            if (reverse) offset = segment->getCount() - offset;

            // Add offset to create fade.
            x += offset;

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
