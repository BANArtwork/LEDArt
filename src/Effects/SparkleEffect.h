#ifndef SPARKLEEFFECT_H
#define SPARKLEEFFECT_H

#include "AnimationEffect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief Effect to create random sparkles.
 */
class SparkleEffect : AnimationEffect {

    public:

        SparkleEffect(
            int frameDivisor,
            int animationLength,
            unsigned int animationWindow,
            uint32_t sparkleColor
        ) :
        AnimationEffect(
            frameDivisor,
            animationLength
        ),  
            _animationWindow { animationWindow },
            _sparkleColor { sparkleColor }
        {
            _rand = rand();
            _randomColors = false;
        }

        SparkleEffect(
            int frameDivisor,
            int animationLength,
            unsigned int animationWindow
        ) :
        AnimationEffect(
            frameDivisor,
            animationLength
        ),  
            _animationWindow { animationWindow }
        {
            _rand = rand();
            _sparkleColor = rand();
            _randomColors = true;
        }

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
            uint32_t newColor;
            AnimationState s = sparkle(
                _animationWindow,
                animationLength,
                _sparkleColor, 
                _rand,
                ledX, 
                ledY, 
                ledZ, 
                ledIndex, 
                frame, 
                currentColor, 
                newColor
            );
            if (s == FADING) {
                return newColor;
            }
            if (s == LAST_FRAME) {
                _rand = rand();
                if (_randomColors) {
                    _sparkleColor = rand();
                }
            }
            return currentColor;
        }

    private:

        unsigned int _animationWindow;
        int _rand;
        uint32_t _sparkleColor;
        bool _randomColors;

        enum AnimationState {
            FADING,
            LAST_FRAME,
            COMPLETE
        };

        static AnimationState sparkle(
            unsigned int animationWindow,
            unsigned int animationLength,
            uint32_t sparkleColor,
            int rand,
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor,
            uint32_t& newColor
        ) {
            unsigned int x = frame + rand;
            x %= animationWindow;
            if (x == animationLength) return LAST_FRAME;
            if (x > animationLength) return COMPLETE;

            int half = animationLength / 2;
            uint32_t c;
            if (x < half) {
                c = interpolateColors(currentColor, sparkleColor, half, x);
            } else {
                c = interpolateColors(currentColor, sparkleColor, half, animationLength - x);
            }

            newColor = c;
            return FADING;
        }
};

#endif
