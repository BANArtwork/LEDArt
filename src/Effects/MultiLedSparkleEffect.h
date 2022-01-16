#ifndef MULTILEDSPARKLEEFFECT_H
#define MULTILEDSPARKLEEFFECT_H

#include "AnimationEffect.h"
#include "./../Util/ColorConverters.h"
#include "../Util/LinkedList.h"
#include <math.h>
#include "../Util/Logger.h"

/**
 * @brief Effect to create random sparkles.
 */
class MultiLedSparkleEffect : AnimationEffect {

    public:

        MultiLedSparkleEffect(
            int frameDiv,
            int animationWindow,
            int animationLength,
            int animationWidth,
            const uint32_t* const colors,
            int numColors
        ) : AnimationEffect(frameDiv),
            _animationWindow { animationWindow },
            _animationLength { animationLength },
            _animationWidth { animationWidth },
            _colors { colors },
            _numColors { numColors }
        {
            int r = rand() % _numColors;
            _randomColor = _colors[r];
            _randomFrameOffset = rand();
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
                _animationWindow,
                _animationLength,
                _animationWidth,
                _randomColor,
                _randomFrameOffset,
                ledIndex,
                frame,
                currentColor,
                newColor
            );

            if (state == LAST_FRAME) {
                int r = rand() % _numColors;
                _randomColor = _colors[r];
                _randomFrameOffset = rand();
            }

            return (state == FADING);
        }

    private:

        // Struct to define a sparkle animation.
        struct Sparkle {
            int ledIndex;
            unsigned int animationFrame;
        };

        // List of current sparkle center points.
        static LinkedList<Sparkle*> _sparkles;

        // Array of colors to choose from.
        const int _numColors;
        const uint32_t* const _colors;

        // Number of animation frames within which a sparkle will occur.
        int _animationWindow;

        // Length of the animation in frames. (Actual animation length 
        // is (this value * 2) + 1)
        int _animationLength;

        // Width of the animaion in LEDs. (Actual length
        // is (this value * 2) + 1)
        int _animationWidth;

        // Random color to use for next sparkle.
        uint32_t _randomColor;

        // Value to randomiz the sparkles.
        unsigned int _randomFrameOffset;

        unsigned int _previousAnimaationFrame;

        enum AnimationState {
            FADING,
            LAST_FRAME,
            COMPLETE
        };

        static AnimationState sparkle(
            int animationWindow,
            int animationLength,
            int animationWidth,
            uint32_t sparkleColor,
            int randomFrameOffset,
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t& newColor
        ) {

            // If this LED is part of an existing sparkle animation...
            Sparkle* currentSparkle = getSparkleAnimation(ledIndex, animationWidth);
            if (currentSparkle != NULL && currentSparkle->ledIndex != ledIndex) {

                // Then calculate new color based off of the existing animation.
                int f = calculateSparkleFactor(currentSparkle, ledIndex, animationLength, animationWidth);
                int max = (animationLength * animationWidth);
                newColor = interpolateColors(currentColor, sparkleColor, max, f);
                return FADING;
            }

            // Calculate animation frame.
            unsigned int animationFrame = frame + randomFrameOffset;
            animationFrame %= animationWindow;

            // If we are on the first animation frame and we haven't created a sparkle item yet...
            if (animationFrame == 0 && currentSparkle == NULL) {

                // Create a new sparkle item.
                currentSparkle = new Sparkle {
                    ledIndex, animationFrame
                };
                
                // And add it to the list.
                _sparkles.insert(currentSparkle);
            }
            
            // If we are past animation length, then the animation is complete.
            if (animationFrame > (animationLength * 2 + 1)) return COMPLETE;

            // If we are on the last animation frame...
            if (animationFrame == (animationLength * 2 + 1)) {

                // Get index of the sparkle item in the list of current sparkle animations.
                int i = -1;
                _sparkles.forEach([ledIndex, &i](Sparkle* sparkle){
                    i++;
                    if (sparkle->ledIndex == ledIndex) return true;
                    return false;
                });

                // And remove it from the list.
                if (i >= 0) _sparkles.remove(i);
                
                return LAST_FRAME;
            }

            // Calculate new color.
            int f = calculateSparkleFactor(currentSparkle, ledIndex, animationLength, animationWidth);
            
            logSprintf("Factor: %d index: %d\r\n", f, ledIndex);

            int max = (animationLength * animationWidth);
            newColor = interpolateColors(currentColor, sparkleColor, max, f);

            // Inc animation frame for sparkle.
            if (currentSparkle->ledIndex == ledIndex) currentSparkle->animationFrame++;
            return FADING;
        }

        /**
         * @brief Find the first sparkle item in the list where the current
         * LED index falls within 'animationWidth' of the sparkle item.
         * 
         * @param ledIndex 
         * @param animationWidth 
         * @return Sparkle* 
         */
        static Sparkle* getSparkleAnimation(int ledIndex, int animationWidth) {

            // Look for a sparkle item
            Sparkle* result = _sparkles.findFirst([ledIndex, animationWidth](Sparkle* sparkle){

                // Lower animation bound:
                bool lower = ledIndex >= (sparkle->ledIndex - animationWidth);

                // Upper animation bound.
                bool upper = ledIndex <= (sparkle->ledIndex + animationWidth);

                // If the given led index lies within 'animationWidth' of a
                // sparkle item in the list, then we have found the item we
                // are looking for.
                return lower && upper;
            });

            return result;
        }

        /**
         * @brief Calculate an interpolation value between 0 and 
         * 'animationWidth' * 'animationLength' for the current 
         * LED and current animation frame.
         * 
         * @param currentSparkle 
         * @param ledIndex 
         * @param animationLength 
         * @param animationWidth 
         * @return int 
         */
        static int calculateSparkleFactor(
            Sparkle* currentSparkle, 
            int ledIndex, 
            int animationLength, 
            int animationWidth
        ) {
            // Get distance of this LED from the center of the current sparkle.
            int x = abs(currentSparkle->ledIndex - ledIndex);

            // If we pretend time is just another physical dimension,
            // the we get the 'distance' from the current animation frame
            // to the center frame of the animation (center frame = max
            // color value).
            int y = abs(currentSparkle->animationFrame - animationLength);

            // Calculate color interpolation factor.
            int result = 
                (animationLength * animationWidth) - 
                (x * animationWidth + y * animationLength);

            if (result < 0) result = 0;

            return result;
        }
};

// Initialize the sparkle item list.
LinkedList<MultiLedSparkleEffect::Sparkle*> MultiLedSparkleEffect::_sparkles = 
    LinkedList<MultiLedSparkleEffect::Sparkle*>();

#endif

/*


takala, andy
or ates takala.
or contact foundation specialist.


(w * h) - (abs(x) * w + abs(y) * h)
range = (0..w*h)

*/
