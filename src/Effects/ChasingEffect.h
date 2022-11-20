#ifndef CHASING_EFFECT_H
#define CHASING_EFFECT_H

#include "AnimationEffect.h"

class ChasingEffect : public AnimationEffect {

    public: 

        ChasingEffect(
            int animationLength,
            int chaseLength,
            uint32_t color,
            int length,
            int segmentLength = 0,
            bool reverseDirection = false

        ) : AnimationEffect(
            animationLength
        ),
            _chaseLength { chaseLength },
            _segmentLength { segmentLength },
            _reverseDirection { reverseDirection },
            _color { color },
            _length { length }
        {}

        void setColor(uint32_t color) {
            _color = color;
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

            int offset = _reverseDirection ? (_segmentLength - ledIndex) : ledIndex;
            return chasingFade(
                offset, 
                frame, 
                _chaseLength,
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
        int _chaseLength;

        static AnimationState chasingFade(
            int offset, 
            unsigned int frame,
            unsigned int chaseLength,
            uint32_t color,
            int length,
            uint32_t currentColor,
            uint32_t& newColor
        ) {
            // Add frame and LED index to create chasing effect.
            int x = (offset + frame + length);
            x = x % chaseLength;

            if (x >= length) {
                newColor = currentColor;
                return COMPLETE;
            }

            newColor = color;
            return ANIMATING;
        }

};

#endif
