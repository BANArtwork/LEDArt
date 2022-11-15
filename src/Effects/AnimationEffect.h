#ifndef ANIMATION_EFFECT_H
#define ANIMATION_EFFECT_H

#include "Effect.h"

/**
 * @brief Base class for animation effect. This class
 * handles calculating the current animation frame.
 * By increasing the frame divisor, the animation can
 * be slowed down.
 */
class AnimationEffect : public Effect {

    public:

        /**
         * @brief 
         *  Construct a new Animation Effect object
         * 
         * @param frameDivisor 
         *  To calculate animation frame. Higher value ==
         *  slower animation.
         * @param animationLength 
         *  Total number of frames in the animation.
         */
        AnimationEffect(
            int frameDivisor,
            int animationLength
        ) : 
            _frameDivisor { frameDivisor },
            _animationLength { animationLength } {}

    protected: 

        enum AnimationState {
            ANIMATING,
            LAST_FRAME,
            COMPLETE
        };

        virtual AnimationState animationEffectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            unsigned int ledIndex, 
            unsigned int frame,
            unsigned int animationLength,
            uint32_t currentColor, 
            uint32_t previousColor,
            uint32_t& newColor
        ) {};

        uint32_t effectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            unsigned int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t previousColor
        ) {
            // Calculate frame for animation. 
            unsigned int f = frame / _frameDivisor;

            uint32_t newColor;

            // Get color for new frame.
            AnimationState result = animationEffectAction(
                ledX,
                ledY,
                ledZ,
                ledIndex,
                f,
                _animationLength,
                currentColor,
                previousColor,
                newColor
            );

            return newColor;
        }

    protected:

        int _frameDivisor;
        int _animationLength;
};

#endif
