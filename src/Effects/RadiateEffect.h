#ifndef RADIATEEFFECT_H
#define RADIATEEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief Effect to create random sparkles.
 */
class RadiateEffect : Effect {

    public:

        RadiateEffect(
            int order,
            int animationLength, 
            int animationWindow, 
            int animationFrameDiv,
            int overlap
        ) : 
            _order { order },
            _animationLength { animationLength }, 
            _animationWindow { animationWindow },
            _animationFrameDiv { animationFrameDiv },
            _overlap { overlap } {}
        
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
            return effect(
                _animationLength,
                _animationWindow, 
                _animationFrameDiv,
                _order,
                _overlap,
                ledX, 
                ledY, 
                ledZ, 
                ledIndex, 
                frame, 
                currentColor, 
                newColor
            );
        }

    private:

        int _order;        
        int _animationLength;
        int _animationWindow;
        int _animationFrameDiv;
        int _overlap;


        static bool effect(
            int animationLength,
            int animationWindow,
            int animationFrameDiv,
            int order,
            int overlap,
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t& newColor
        ) {
            unsigned int x = frame / animationFrameDiv;
            x = x % animationWindow;

            unsigned int y = (animationLength - overlap) * order;

            int z;

            // Not animating yet.
            if (x < y) return false;

            // Done animating.
            if (x >= (y + animationLength)) return false;

            // fading up:
            if (x < (y + (animationLength / 2))) {
                z = x - y;
            }

            // fading down.
            else if (x < (y + animationLength)) {
                z = (y + animationLength) - x;
            }

            newColor = interpolateColors(0, 0xffffff, (animationLength / 2), z);

            return true;

        }
};

#endif


// Animation length: [____^____][____^____][____^____][____^____][____^____]
// Animation window: [_____________________________________________________]