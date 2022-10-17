#ifndef EFFECT_H
#define EFFECT_H

#include <stdint.h>

/**
 * @brief Base effect class.
 */
class Effect {

    public:

        /**
         * @brief Effect action method signature.
         * 
         * @param ledX X coordinate of the LED
         * @param ledY Y coordinate of the LED
         * @param ledZ Z coordinate of the LED
         * @param ledIndex Index of the LED in the string
         * @param frame Current frame
         * @param currentColor Current LED color (from effects that were calculated before this one)
         * @param previousColor Previous LED coloe (final color from previous frame)
         * 
         * @return uint32_t New color calculated from this effect
         */
        virtual uint32_t effectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            unsigned int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t previousColor
        );

        void activate() { _isActive = true; }
        void deactivate() { _isActive = false; }
        bool isActive() { return _isActive; }

    private:

        bool _isActive = true;
};

#endif
