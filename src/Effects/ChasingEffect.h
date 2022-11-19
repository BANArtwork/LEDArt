#ifndef CHASING_EFFECT_H
#define CHASING_EFFECT_H

#include "AnimationEffect.h"

class ChasingEffect : public AnimationEffect {

    public: 

        ChasingEffect(
            int animationLength,
            uint32_t color,
            int length,
            int segmentLength = 0,
            bool reverseDirection = false

        ) : AnimationEffect(
            animationLength
        ),
            _segmentLength { segmentLength },
            _reverseDirection { reverseDirection },
            _color { color },
            _length { length }
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

            int offset = _reverseDirection ? (_segmentLength - ledIndex) : ledIndex;
            return chasingFade(
                offset, 
                frame, 
                animationLength,
                _color,
                _length,
                currentColor,
                newColor
            );
        }

    private:

        int _segmentLength;
        bool _reverseDirection;
        uint32_t _color;
        int _length;

        static AnimationState chasingFade(
            int offset, 
            unsigned int frame,
            unsigned int animationLength,
            uint32_t color,
            int length,
            uint32_t currentColor,
            uint32_t& newColor
        ) {
            // Add frame and LED index to create chasing effect.
            int x = (offset + frame + length);
            x = x % animationLength;

            if (x >= length) {
                newColor = currentColor;
                return COMPLETE;
            }

            newColor = color;
            return ANIMATING;
        }

};

#endif
