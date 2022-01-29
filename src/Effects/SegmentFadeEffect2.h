#ifndef SEGMENTFADEEFFECT_H
#define SEGMENTFADEEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"

class SegmentFadeEffect : Effect {

    public:

        SegmentFadeEffect(
            int order,
            int fadeLength,
            int animationFrameDiv
        ) : 
            _order { order },
            _fadeLength { fadeLength }, 
            _animationFrameDiv { animationFrameDiv } {}
        
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
                _animationFrameDiv,
                _order,
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

        int _order;        
        int _fadeLength;
        int _animationFrameDiv;

        static const int _numColors = 4;
        static const uint32_t _colors[_numColors];

        static bool effect(
            int fadeLength,
            int animationFrameDiv,
            int order,
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t& newColor
        ) {
            unsigned int x = frame / animationFrameDiv;
            int c = x / fadeLength;
            c += order;

            uint32_t color1 = _colors[c % _numColors];
            uint32_t color2 = _colors[(c + 1) % _numColors];

            unsigned int y = x % fadeLength;

            newColor = interpolateColors(color1, color2, fadeLength, y);

            return true;
        }
};

const uint32_t SegmentFadeEffect::_colors[] = {
    0xff2600,
    0x00ff0d,
    0xc800ff,
    0x0000ff,
};

#endif


// Animation length: [____^____][____^____][____^____][____^____][____^____]
// Animation window: [_____________________________________________________]