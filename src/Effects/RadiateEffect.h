#ifndef RADIATEEFFECT_H
#define RADIATEEFFECT_H

#include "AnimationEffect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief Effect to create random sparkles.
 */
class RadiateEffect : AnimationEffect {

    public:

        RadiateEffect(
            int frameDivisor,
            int animationLength,
            int animationWindow, 
            int order,
            int overlap
        ) : 
        AnimationEffect(
            frameDivisor,
            animationLength
        ), 
            _animationWindow { animationWindow },
            _order { order },
            _overlap { overlap } {}
        
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
            bool useNewColor = effect(
                animationLength,
                _animationWindow, 
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

            if (useNewColor) return newColor;
            return currentColor;
        }

    private:

        int _animationWindow;
        int _order;        
        int _overlap;


        static bool effect(
            int animationLength,
            int animationWindow,
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
            unsigned int x = frame % animationWindow;
            unsigned int y = (animationLength - overlap) * order;

            int z;

            // Not animating yet.
           // if (x < y) return false;

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