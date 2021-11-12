#ifndef EFFECT_H
#define EFFECT_H

#include <stdint.h>

/**
 * @brief Base effect class.
 */
class Effect {

    public:

        virtual bool effectAction(
            uint32_t ledX, 
            uint32_t ledY, 
            uint32_t ledZ, 
            uint32_t ledIndex, 
            uint32_t frame,
            uint32_t currentColor, 
            uint32_t previousColor,
            uint32_t& newColor
        );
};

#endif
