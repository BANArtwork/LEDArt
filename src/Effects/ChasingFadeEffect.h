#ifndef CHASINGFADEEFFECT_H
#define CHASINGFADEEFFECT_H

#include "FadeEffect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief An effect that will show a chasing fade between an array of colors.
 */
class ChasingFadeEffect : FadeEffect {

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
        ChasingFadeEffect(
            int frameDivisor,
            int fadeLength,
            int fadeStep,
            int numColors,
            const uint32_t* colors,
            int segmentLength = 0,
            bool reverseDirection = false
        ) :
        FadeEffect(
            frameDivisor,
            fadeLength,
            fadeStep,
            numColors,
            colors
        ),  
            _segmentLength { segmentLength },
            _reverseDirection { reverseDirection }
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
            int offset = _reverseDirection ? (_segmentLength - ledIndex) : ledIndex;
            return chasingFade(
                offset, 
                frame, 
                animationLength,
                _fadeStep,
                _numColors,
                ledIndex,
                _colors,
                currentColor,
                newColor
            );
        }

    private:

        int _segmentLength;
        bool _reverseDirection;
};

#endif
