#ifndef SPARKLEEFFECT_H
#define SPARKLEEFFECT_H

#include "AnimationEffect.h"
#include "./../Util/ColorConverters.h"
#include <Arduino.h>

/**
 * @brief Effect to create random sparkles.
 */
class SparkleEffect : AnimationEffect {

    public:

        SparkleEffect(
            int frameDivisor,
            int animationLength,
            unsigned int animationWindow,
            int numSparkleColors,
            uint32_t* sparkleColors
        ) :
        AnimationEffect(
            frameDivisor,
            animationLength
        ),  
            _animationWindow { animationWindow },
            _sparkleColors { sparkleColors },
            _numSparkleColors { numSparkleColors }
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
            // If we have just started a new frame and the previous frame 
            // was the last animation frame...
            if (_lastFrameFlag && _lastFrame != frame) {

                // Reset flag.
                _lastFrameFlag = false;

                // Update rand and color values.
                _rand = rand();
                if (_randomColors) {
                    _sparkleColor = (rand() & 0x00ffffff);
                } else {
                    int i = rand() % _numSparkleColors;
                    _sparkleColor = _sparkleColors[i];                
                }
            }

            // Update last frame value.
            _lastFrame = frame;

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
                _lastFrameFlag = true;
            }

            return currentColor;
        }

    private:

        unsigned int _animationWindow;
        unsigned int _rand;
        uint32_t _sparkleColor;
        uint32_t* _sparkleColors;
        int _numSparkleColors;
        bool _randomColors;

        unsigned int _lastFrame;
        bool _lastFrameFlag;

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
            if (x <= half) {
                c = interpolateColors(currentColor, sparkleColor, half, x);
            } else {
                c = interpolateColors(currentColor, sparkleColor, half, animationLength - x);
            }

            newColor = c;
            return FADING;
        }
};

#endif
