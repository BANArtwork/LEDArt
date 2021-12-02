#ifndef SPARKLEEFFECT_H
#define SPARKLEEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief Effect to create random sparkles.
 */
class SparkleEffect : Effect {

    public:

        SparkleEffect(
            int animationLength, 
            int animationWindow, 
            int animationFrameDiv,
            uint32_t color = 0xffffff
        ) :
            _animationLength { animationLength }, 
            _animationWindow { animationWindow },
            _animationFrameDiv { animationFrameDiv },
            _color { color } {
            _rand = rand();
        }

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
            AnimationState state = sparkle(
                _animationLength,
                _animationWindow, 
                _animationFrameDiv,
                _rand,
                _color,
                ledX, 
                ledY, 
                ledZ, 
                ledIndex, 
                frame, 
                currentColor, 
                newColor
            );

            if (state == LAST_FRAME) {
                _rand = rand();
            }

            return (state == FADING);
        }

    private:

        int _animationLength;
        int _animationWindow;
        int _animationFrameDiv;
        unsigned int _rand;
        uint32_t _color;

        enum AnimationState {
            FADING,
            LAST_FRAME,
            COMPLETE
        };

        static AnimationState sparkle(
            int animationLength,
            int animationWindow,
            int animationFrameDiv,
            unsigned int random,
            uint32_t color,
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t& newColor
        ) {
            // Add frame and random val.
            unsigned int x = frame + random;

            // Divide by framediv to get animation frame.
            x /= animationFrameDiv;

            // Mod by window to see if we should animate.
            x = x % animationWindow;

            uint8_t w;

            // Fade up.
            if (x < animationLength / 2) {
                w = x;

            // Fade down.
            } else if (x < animationLength) {
                w = animationLength - x;

            // Last frame.
            } else if (x == animationLength) {
                return LAST_FRAME;

            // Animation complete.
            } else {
                return COMPLETE;
            }

            // Interpolate from current color to random color.
            newColor = interpolateColors(currentColor, color, animationLength / 2, w);

            return FADING; 
        }
};

#endif
