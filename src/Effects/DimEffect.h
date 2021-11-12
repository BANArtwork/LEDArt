#ifndef DIMEFFECT_H
#define DIMEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief Effect to dim LEDs.
 */
class DimEffect : Effect {

    public:

        DimEffect(int dimFactor) : _dimFactor { dimFactor } {}
        
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
            return dim(
                _dimFactor, 
                ledX, 
                ledY, 
                ledZ, 
                ledIndex, 
                frame, 
                currentColor, 
                newColor
            );
        }

    private:

        int _dimFactor;

        static bool dim(
            int d,
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t& newColor
        ) {
            uint8_t r, g, b;
            uint32toRgb(currentColor, r, g, b);
            r /= d;
            g /= d;
            b /= d;
            newColor = rgbToUint32(r, g, b);
            return true;
        }
};

#endif
