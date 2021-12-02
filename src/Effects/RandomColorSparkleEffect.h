#ifndef RANDOMCOLORSPARKLEEFFECT_H
#define RANDOMCOLORSPARKLEEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"
#include "./../Util/Colors.h"

/**
 * @brief Effect to create random sparkles.
 */
class RandomColorSparkleEffect : Effect {

    public:

        RandomColorSparkleEffect(
            int animationLength, 
            int animationWindow, 
            int animationFrameDiv
        ) : 
            _animationLength { animationLength }, 
            _animationWindow { animationWindow },
            _animationFrameDiv { animationFrameDiv } {
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
                _randomColor,
                _animationLength,
                _animationWindow, 
                _animationFrameDiv,
                _rand,
                ledX, 
                ledY, 
                ledZ, 
                ledIndex, 
                frame, 
                currentColor, 
                newColor
            );

            if (state == LAST_FRAME) {
                int r = rand() % _numColors;
                auto c = _colors[r];
                _randomColor = c;
                _rand = rand();
            }

            return (state == FADING);
        }

    private:

        int _animationLength;
        int _animationWindow;
        int _animationFrameDiv;
        unsigned int _rand;
        uint32_t _randomColor;

        static const int _numColors = 2;
        
         static const uint32_t _colors[_numColors];

        enum AnimationState {
            FADING,
            LAST_FRAME,
            COMPLETE
        };

        static AnimationState sparkle(
            uint32_t randomColor,
            int animationLength,
            int animationWindow,
            int animationFrameDiv,
            unsigned int random,
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
            if (x < (animationLength / 2)) {
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
            newColor = interpolateColors(currentColor, randomColor, animationLength / 2, w);

            return FADING; 
        }
};

 const uint32_t RandomColorSparkleEffect::_colors[] = {
    
    0xff0000,
    // 0x00ff00,
    0x0000ff
};

#endif
