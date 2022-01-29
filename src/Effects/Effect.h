#ifndef EFFECT_H
#define EFFECT_H

#include <stdint.h>

/**
 * @brief Base effect class.
 */
class Effect {

    public:

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
