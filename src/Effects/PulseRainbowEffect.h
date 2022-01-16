#ifndef PULSERAINBOWEFFECT_H
#define PULSERAINBOWEFFECT_H

#include "AnimationEffect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief Pulsing rainbow effect.
 */
class PulseRainbowEffect : AnimationEffect {

    public:

        /**
         * @brief Construct a new Fade Rainbow Effect object
         * 
         * @param frameDivisor To calculate animation frame. Higher value ==
         * slower animation.
         * @param animationLength Total number of frames in the animation.
         * @param colorStep Number of 'steps' in the color difference 
         * between neighboring LEDs. Higher value == 'narrower' rainbow.
         */
        PulseRainbowEffect(
            int frameDivisor,
            int animationLength,
            unsigned int colorStep,
            unsigned int offset
        ) :
        AnimationEffect(
            frameDivisor,
            animationLength
        ),  
            _colorStep { colorStep },
            _offset { offset }
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
            return pulseRainbow(
                ledIndex, 
                frame, 
                animationLength,
                _colorStep,
                _offset,
                currentColor
            );
        }

    private:

        unsigned int _colorStep;
        unsigned int _offset;

        static uint32_t pulseRainbow(
            int ledIndex, 
            unsigned int frame,
            unsigned int animationLength,
            unsigned int colorStep,
            unsigned int offset,
            uint32_t currentColor
        ) {
            // Add frame and LED index to create rainbow effect.
            int x = frame + offset;
            x *= colorStep;
            x = x % animationLength;

            int firstThird = animationLength / 3;
            int secondThird = firstThird * 2;

            // Calculate RGB values for this step.
            uint8_t r, g, b;
            if (x < firstThird) {
                r = (firstThird - 1) - x;
                g = x;
                b = 0;
            } else if (x < secondThird) {
                r = 0;
                g = (secondThird - 1) - x;
                b = x - firstThird;
            } else {
                r = x - secondThird;
                g = 0;
                b = (animationLength - 1) - x;
            }

            // Set result and return true.
            return rgbToUint32(r, g, b);
        }
};

#endif
