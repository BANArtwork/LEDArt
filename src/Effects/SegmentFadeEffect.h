#ifndef SEGMENTFADEEFFECT_H
#define SEGMENTFADEEFFECT_H

#include "FadeEffect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief An effect that will show a chasing fade between an array of colors.
 */
class SegmentFadeEffect : FadeEffect {

    public:

        /**
         * @brief Construct a new Chasing Fade Effect object
         * 
         * @param frameDivisor To calculate animation frame. Higher value ==
         * slower animation.
         * @param fadeLength Total number of frames to lerp from one color to 
         * the next.
         * @param fadeStep Number of 'steps' in the color difference 
         * between neighboring LEDs. Higher value == 'narrower' color bands.
         * @param numColors Total number of colors to fade between.
         * @param colors Array of colors to fade between
         */
        SegmentFadeEffect(
            int frameDivisor,
            int fadeLength,
            int fadeStep,
            int offset,
            int numColors,
            const uint32_t* colors
        ) :
        FadeEffect(
            frameDivisor,
            fadeLength,
            fadeStep,
            numColors,
            colors
        ),
            _offset { offset }
        {}

        AnimationState animationEffectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            unsigned int ledIndex, 
            unsigned int frame,
            unsigned int animationLength,
            uint32_t currentColor, 
            uint32_t previousColor,
            uint32_t& newColor
        ) {
            return chasingFade(
                _offset, 
                frame, 
                animationLength,
                _fadeStep,
                _numColors,
                _colors,
                currentColor,
                newColor
            );
        }

    private:

        int _offset;
};

#endif
