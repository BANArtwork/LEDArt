#ifndef SOLIDCOLOREFFECT_H
#define SOLIDCOLOREFFECT_H

#include "Effect.h"

/**
 * @brief Just set LED to the given color.
 */
class SolidColorEffect : Effect {

    public:

        SolidColorEffect(uint32_t color) : _color { color } {}

        bool effectAction(
            uint32_t ledX, 
            uint32_t ledY, 
            uint32_t ledZ, 
            uint32_t ledIndex, 
            uint32_t frame,
            uint32_t currentColor, 
            uint32_t previousColor,
            uint32_t& newColor
        ) {
            newColor = _color;
            return true;
        }

    private:

        uint32_t _color;
};

#endif
