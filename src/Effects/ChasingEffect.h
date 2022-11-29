#ifndef CHASING_EFFECT_H
#define CHASING_EFFECT_H

#include "AnimationEffect.h"

/**
 * @brief Class to produce a chasing animation effect.
 */
class ChasingEffect : public AnimationEffect {

    public: 

        /**
         * @brief Construct a new Chasing Effect object
         * 
         * @param animationLength 
         */
        ChasingEffect(int animationLength) : 
        AnimationEffect(animationLength) {}

        /**
         * @brief Set the length of the segment that the chase block will
         * chase through.
         * 
         * @param length 
         */
        void setChaseLength(int length) {
            _chaseLength = length;
        }

        /**
         * @brief Set the length of the chase block.
         * 
         * @param length 
         */
        void setBlockLength(int length) {
            _blockLength = length;
        }

        /**
         * @brief Set the chase block color to a single color value.
         * 
         * @param color 
         */
        void setColor(uint32_t color) {
            _getColor = [color](int x) { return color; };
        }

        /**
         * @brief Set a callback to get a color based on the index of an LED
         * within the chase block.
         * 
         * @param getColor 
         */
        void setColorCallback(std::function<uint32_t(int)> getColor) {
            _getColor = getColor;
        }

        /**
         * @brief Reverse the chase direction.
         * 
         * @param reverse 
         */
        void reverseDirection(bool reverse) {
            _reverseDirection = reverse;
        }

    protected:

        /**
         * @brief Method for subclasses to override to get color values.
         * 
         * @param x 
         * @return uint32_t 
         */
        virtual uint32_t getColor(int x) {
            return _getColor(x);
        }

        /**
         * @brief Effect action implementation.
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

            // Get chase offset for forward or reverse.
            int offset = _reverseDirection ? (_chaseLength - ledIndex) : ledIndex;

            // Get getColor callback.
            std::function<uint32_t(int)> f = [this](int x){ return this->getColor(x); };

            return chasingFade(
                offset, 
                frame, 
                _chaseLength,
                _blockLength,
                f,
                currentColor,
                newColor
            );
        }

    private:

        // Flag to reverse chase direction.
        bool _reverseDirection = false;

        // Length of the chase block.
        int _blockLength;

        // Length of the segment the chase block will chase through.
        int _chaseLength;

        // Method to get a color value for an LED in the chase block.
        std::function<uint32_t(int)> _getColor;

        static AnimationState chasingFade(
            int offset, 
            unsigned int frame,
            unsigned int chaseLength,
            int blockLength,
            std::function<uint32_t(int)> getColor, 
            uint32_t currentColor,
            uint32_t& newColor
        ) {
            // Add frame and LED index to create chasing effect.
            int x = (offset + frame + blockLength);
            x = x % chaseLength;

            // If we are past the end of the chase block...
            if (x >= blockLength) {

                // Then don't change color.
                newColor = currentColor;
                return COMPLETE;
            }

            // Otherwise, get a new color.
            newColor = getColor(x);
            return ANIMATING;
        }
};

#endif
