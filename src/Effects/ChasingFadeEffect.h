#ifndef CHASINGFADEEFFECT_H
#define CHASINGFADEEFFECT_H

#include "AnimationEffect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief An effect that will show a chasing fade between an array of colors.
 */
class ChasingFadeEffect : AnimationEffect {

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
            const uint32_t* colors
        ) :
        AnimationEffect(
            frameDivisor,
            numColors * fadeLength
        ),  
            _fadeStep { fadeStep },
            _numColors { numColors },
            _colors { colors }
        {}

        uint32_t animationEffectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            unsigned int ledIndex, 
            unsigned int frame,
            unsigned int animationLength,
            uint32_t currentColor, 
            uint32_t previousColor
        ) {
            return chasingFade(
                ledIndex, 
                frame, 
                animationLength,
                _fadeStep,
                _numColors,
                _colors,
                currentColor
            );
        }

    private:

        unsigned int _fadeStep;
        int _numColors;
        const uint32_t* _colors;

        static uint32_t chasingFade(
            int ledIndex, 
            unsigned int frame,
            unsigned int animationLength,
            unsigned int fadeStep,
            unsigned int numColors,
            const uint32_t* colors,
            uint32_t currentColor
        ) {
            // Add frame and LED index to create chasing effect.
            int x = (ledIndex + frame);
            x *= fadeStep;
            x = x % animationLength;

            // Get length of fade from one color to the next.
            int fadeLength = animationLength / numColors;

            // Get index of start and end colors for this animation part.
            unsigned int colorIndex1 = x / fadeLength;
            unsigned int colorIndex2 = colorIndex1 + 1;

            // Loop back to first color in the list if neccesary.
            if (colorIndex2 >= numColors) colorIndex2 = 0; 

            // Calculate value to lerp to for current colors.
            int lerpVal = x - (fadeLength * colorIndex1);
            if (lerpVal < 0) lerpVal = 0;

            // Max lerp value.
            unsigned int maxVal = fadeLength;

            // Get colors.
            uint32_t color1 = colors[colorIndex1];
            uint32_t color2 = colors[colorIndex2];

            // Interpolate between the two colors.
            uint32_t result = interpolateColors(color1, color2, maxVal, lerpVal);
            return result;
        }
};

#endif
