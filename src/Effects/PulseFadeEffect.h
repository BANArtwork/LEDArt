#ifndef PULSEFADEEFFECT_H
#define PULSEFADEEFFECT_H

#include "FadeEffect.h"
#include "./../Util/ColorConverters.h"
#include <Arduino.h>

/**
 * @brief An effect that will show a chasing fade between an array of colors.
 */
class PulseFadeEffect : FadeEffect {

    public:

        /**
         * @brief Construct a new Chasing Fade Effect object
         * 
         * @param frameDivisor To calculate animation frame. Higher value ==
         * slower animation.
         * @param fadeLength Total number of frames to lerp from one color to 
         * the next.
         * @param fadeStep Number of 'steps' in the color difference 
         * between neighboring LEDs. Higher value == 'narrower' color bands.
         * @param numColors Total number of colors to fade between.
         * @param colors Array of colors to fade between
         */
        PulseFadeEffect(
            int frameDivisor,
            int fadeLength,
            int fadeStep,
            int numColors,
            const uint32_t* colors,
            int lastLedIndex,
            int firstLedIndex,
            int segmentLength = 0,
            bool reverseDirection = false
        ) :
        FadeEffect(
            frameDivisor,
            fadeLength,
            fadeStep,
            numColors,
            colors
        ),  
            _lastLedIndex { lastLedIndex },
            _firstLedIndex { firstLedIndex },
            _segmentLength { segmentLength },
            _reverseDirection { reverseDirection }
        { 
            _rand = rand();
        }

        
        
    
        AnimationState animationEffectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            unsigned int ledIndex, 
            unsigned int frame,
            unsigned int animationLength,
            uint32_t currentColor, 
            uint32_t previousColor,
            uint32_t& newColor
        ) {
  
            // If we have just started a new frame and the previous frame 
            // was the last animation frame...
            if (_lastFrameFlag && _lastFrame != frame && ledIndex == _firstLedIndex) {

                // Reset flag.
                _lastFrameFlag = false;

                // Update rand.
                _rand = rand();

               //Serial.printf("New rand: %d, last: %d, led: %d\r\n", _rand, _lastLedIndex, ledIndex);
            }

            // Update last frame value.
            _lastFrame = frame;



            unsigned int offset = _reverseDirection ? (_segmentLength - ledIndex) : ledIndex;
            offset += _rand;

            AnimationState s = chasingFade(
                offset, 
                frame, 
                animationLength,
                _fadeStep,
                _numColors,
                _colors,
                currentColor,
                newColor
            );

           // if(frame % animationLength == animationLength - 1) {
               if(s == AnimationState::LAST_FRAME) {
                _lastFrameFlag = true;
               // Serial.println("LAST");
            }
         
            return s;
        }

    private:

        unsigned int _lastFrame;
        bool _lastFrameFlag;

        int _segmentLength;
        bool _reverseDirection;
        unsigned int _rand;
        int _lastLedIndex;
        int _firstLedIndex;
};

#endif
