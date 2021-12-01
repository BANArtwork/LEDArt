#ifndef RANDOMCOLORSPARKLEEFFECT_H
#define RANDOMCOLORSPARKLEEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief Effect to create random sparkles.
 */
class RandomColorSparkleEffect : Effect {

    public:

        RandomColorSparkleEffect(int speed, int frequency) : 
            _speed { speed }, 
            _frequency { frequency } {
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
                _speed,
                _frequency, 
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
                _randomColor = rand() % _numColors;
                _rand = rand();
            }

            return (state == FADING);
        }

    private:

        int _speed;
        int _frequency;
        int _rand;
        uint32_t _randomColor;

        static const int _numColors = 4;
        static const uint32_t _colors[_numColors] = {
            0xffffff,
            0xff0000,
            0x00ff00,
            0x0000ff
        };

        enum AnimationState {
            FADING,
            LAST_FRAME,
            COMPLETE
        };

        static AnimationState sparkle(
            uint32_t randomColor,
            int speed,
            int frequency,
            int rand,
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t& newColor
        ) {
            // Calculate var for sparkle animation.
            unsigned int x = frame + rand;
            x = x % frequency;
            x = x * speed;
            uint8_t w;

            // Fade up.
            if (x < 256) {
                w = x;

            // Fade down.
            } else if (x < 512) {
                w = 511 - x;

            // Last frame.
            } else if (x == 512) {
                return LAST_FRAME;
            
            // Animation complete.
            } else {
                return COMPLETE;
            }

            // Interpolate from current color to random color.
            newColor = interpolateColors(currentColor, randomColor, 512, w);

            return FADING; 
        }
};

#endif
