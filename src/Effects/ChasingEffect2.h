#ifndef CHASING_EFFECT2_H
#define CHASING_EFFECT2_H

#include "AnimationEffect.h"

/**
 * @brief An effect to create a block of LEDs 
 * that will chase through a segment of LEDs.
 */
class ChasingEffect2 : AnimationEffect {

    public: 

        typedef uint32_t (*getColor_t)(int index);

        /**
         * @brief Construct a new Chasing Effect object
         * 
         * @param frameDivisor Base effect parameter
         * @param animationLength Base effect parameter
         * @param getColor Method that will take the index of the current LED in the chase block and return a color for it.
         * @param length The length of the chasing block
         * @param segmentLength Length of the segment the chasing block will chase through
         * @param reverseDirection If true, reverse the chase direction.
         */
        ChasingEffect2(
            int frameDivisor,
            int animationLength,
            uint32_t (*getColor)(int index),
            int length,
            int segmentLength = 0,
            bool reverseDirection = false

        ) : AnimationEffect(
            frameDivisor,
            animationLength
        ),
            _getColor { getColor },
            _length { length },
            _segmentLength { segmentLength },
            _reverseDirection { reverseDirection }
        {}

        virtual uint32_t getColor(int x) {
            return _getColor(x);
        }

        ChasingEffect2(
            int frameDivisor,
            int animationLength,
            int length,
            int segmentLength = 0,
            bool reverseDirection = false

        ) : AnimationEffect(
            frameDivisor,
            animationLength
        ),
            _length { length },
            _segmentLength { segmentLength },
            _reverseDirection { reverseDirection }
        {}

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

            // Calculate offset value for chase.
            int offset = _reverseDirection ? (_segmentLength - ledIndex) : ledIndex;

            // Calculate chasing effect.
            return chasingFade(
                offset, 
                frame, 
                animationLength,
                this,
                _length,
                currentColor,
                newColor
            );
        }

    private:

        uint32_t (*_getColor)(int index);
        int _length;
        int _segmentLength;
        bool _reverseDirection;

        static AnimationState chasingFade(
            int offset, 
            unsigned int frame,
            unsigned int animationLength,
            ChasingEffect2* effectPtr,
            int length,
            uint32_t currentColor,
            uint32_t& newColor
        ) {
            // Add frame and LED index to create chasing effect.
            int x = (offset + frame);

            // Mod by animation length.
            x = x % animationLength;

            // If we're past animation length, then we're done animating.
            if (x >= length) {
                newColor = currentColor;
                return AnimationState::COMPLETE;
            }

            // Otherwise set new color value.
            newColor = effectPtr->getColor(x);
            return ANIMATING;
        }

};

#endif
