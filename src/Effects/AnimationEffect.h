#ifndef ANIMATION_EFFECT_H
#define ANIMATION_EFFECT_H

#include "Effect.h"

/**
 * @brief Base class for animation effect. This class
 * handles calculating the current animation frame based
 * on the speed value that has been set. It also handles
 * executing the optional callback on the start of each 
 * animation cycle.
 */
class AnimationEffect : public Effect {

    public:

        /**
         * @brief Construct a new Animation Effect object
         * 
         * @param animationLength Total number of frames in the animation.
         */
        AnimationEffect(int animationLength) : 
            _animationLength { animationLength } {}

        /**
         * @brief Set a callback to execute on the start of each animation 
         * cycle.
         * 
         * @param onStart Callback to execute.
         */
        void setOnAnimationStartCallback(std::function<void()> onStart) {
            _onAnimationStart = onStart;
        }

        /**
         * @brief Set the animation speed.
         * 
         * @param speed 
         */
        void setSpeed(double speed) {
            _frameIncrement = speed;
        }

    protected: 

        /**
         * @brief Animation states.
         */
        enum AnimationState {
            ANIMATING,
            LAST_FRAME,
            COMPLETE
        };

        /**
         * @brief Method for subclasses to implement animations.
         * 
         * @param ledX 
         * @param ledY 
         * @param ledZ 
         * @param ledIndex 
         * @param frame 
         * @param animationLength 
         * @param currentColor 
         * @param previousColor 
         * @param newColor 
         * @return AnimationState 
         */
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

        /**
         * @brief Effect action implementation. This is where the animation
         * frame is calculated and the onStart callback is executed.
         * 
         * @param ledX 
         * @param ledY 
         * @param ledZ 
         * @param ledIndex 
         * @param frame 
         * @param currentColor 
         * @param previousColor 
         * @return uint32_t 
         */
        uint32_t effectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            unsigned int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t previousColor
        ) {

            // Is this the first call to this method in a new frame?
            bool newFrame = frame != _lastFrame;
           
            // If so, increment the animation frame counter.
            if (newFrame) {
                _animationFrame += _frameIncrement;
            }

            // Get animation frame as an int and mod by animation length.
            unsigned int f;
            f = _animationFrame;
            f %= _animationLength;

            // If starting a new frame...
            if (newFrame) {

                // If this is the first frame of a new animation cycle... 
                if (f < _frameIncrement) { 
                    
                    // Hit the animation start callback.
                    if (_onAnimationStart != NULL) {
                        _onAnimationStart();
                    }
                }

                // Update last frame value.
                _lastFrame = frame;    
            }
            
            // Get color for new frame.
            uint32_t newColor;
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

            // Return new color value.
            return newColor;
        }

    private:

        // Var to count animati9on frames.
        double _animationFrame = 0;

        // The amount to increment the frame counter by on each call.
        double _frameIncrement = 1;

        // Var to check if a new frame has begun.
        unsigned int _lastFrame = 0;

        // Length of the animation in frames.
        int _animationLength;

        // Optional callback to execute on the start of each animation cycle.
        std::function<void()> _onAnimationStart;
};

#endif
