#ifndef CHASING_EFFECT_H
#define CHASING_EFFECT_H

#include "AnimationEffect.h"

/**
 * @brief An effect to create a block of LEDs 
 * that will chase through a segment of LEDs.
 */
class ChasingEffect : AnimationEffect {

    public: 

        /**
         * @brief Construct a new Chasing Effect object
         * 
         * @param frameDivisor 
         * @param animationLength 
         * @param chaseLength 
         * @param blockLength 
         * @param getColor 
         * @param reverseDirection 
         */
        ChasingEffect(
            int frameDivisor,
            int animationLength,
            int chaseLength,
            int blockLength,
            uint32_t (*getColor)(int index),
            bool reverseDirection = false
        ) : AnimationEffect(
            frameDivisor,
            animationLength
        ),
            _chaseLength { chaseLength },
            _blockLength { blockLength },
            _getColor { getColor },
            _reverseDirection { reverseDirection }
        {}

protected:


        ChasingEffect(
            int frameDivisor,
            int segmentLength,
            int blockLength,
            
            bool reverseDirection = false
        ) : AnimationEffect(
            frameDivisor,
            segmentLength
        ),
            _blockLength { blockLength },
            _reverseDirection { reverseDirection }
        {}

        virtual uint32_t getColor(int x) {
            return _getColor(x);
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

            // Calculate offset value for chase.
            int offset = _reverseDirection ? (_animationLength - ledIndex) : ledIndex;



            // Calculate chasing effect.
            return chasingFade(
                offset, 
                frame, 
                animationLength,
                this,
                _blockLength,
                currentColor,
                newColor
            );
        }

    private:

        // Method to get a color value for an LED in the chase block.
        uint32_t (*_getColor)(int index);

        // Length of the chase block (in LEDs)
        int _blockLength;

        // Flag to reverse chase direction.
        bool _reverseDirection;
 
    
        int _chaseLength;

        static AnimationState chasingFade(
            int offset, 
            unsigned int frame,
            unsigned int animationLength,
            ChasingEffect* chase,
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
            newColor = chase->getColor(x);
            return ANIMATING;
        }

};

#endif
