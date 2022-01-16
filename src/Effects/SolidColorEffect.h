#ifndef SOLIDCOLOREFFECT_H
#define SOLIDCOLOREFFECT_H

#include "Effect.h"

/**
 * @brief Just set LED to the given color.
 */
class SolidColorEffect : Effect {

    public:

        SolidColorEffect(uint32_t color) : _color { color } {}

        uint32_t effectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            unsigned int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t previousColor
        ) {
            return _color;
        }

    private:

        uint32_t _color;
};

#endif
