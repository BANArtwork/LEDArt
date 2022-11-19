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
         * @brief Construct a new Animation Effect object
         * 
         * @param frameDivisor To calculate animation frame. Higher value ==
         * slower animation.
         * @param animationLength Total number of frames in the animation.
         */
        AnimationEffect(
            int animationLength
        ) : 
            _animationLength { animationLength },
            _frameDivisor { 1 },
            _frameMultiplier { 1 } {}

        void setFrameDivisor(int divisor) {
            _frameDivisor = divisor;
        }
        
        void setFrameMultiplier(int multiplier) {
            _frameMultiplier = multiplier;
        }

        void setOnAnimationCompleteCallback(std::function<void()> onComplete) {
            _onAnimationComplete = onComplete;
        }

        void setSpeed(double speed) {
                _speed = speed;
        }
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


unsigned int f2;


           
            // First run in new frame.
            if (frame != _lastFrame) {
                _animationFrame += _speed;
            }


                 f2 = _animationFrame;
               //  f2--;
                f2 %= _animationLength;

             

                        if (frame != _lastFrame) {
                            if (f2 < _speed){ //_animationLength - _speed + 1) {
                    logSprintf("first animation frame ");
                    if (_onAnimationComplete != NULL) {
                        _onAnimationComplete();
                    }
                        }
                _lastFrame = frame;
                logSprintf("First run in new frame. Frame: %d, AnimationFrame %0.2f, Mod frame: %d\r\n", frame, _animationFrame, f2);
                
                        }
            

                
                     

            



            uint32_t newColor;

           // int modLength = (_animationLength * _frameMultiplier) / _frameDivisor;

           // logSprintf("WTF f2: %d\r\n", f2);
            // Get color for new frame.
            AnimationState result = animationEffectAction(
                ledX,
                ledY,
                ledZ,
                ledIndex,
                f2,
                _animationLength,
                currentColor,
                previousColor,
                newColor
            );

            return newColor;
        }

    private:

        double _animationFrame = 0;

        bool _lastFrameFlag;

        double _speed;
        unsigned int _lastFrame = 0;
        int _frameDivisor;
        int _frameMultiplier;
        int _animationLength;
        std::function<void()> _onAnimationComplete;
};

#endif
