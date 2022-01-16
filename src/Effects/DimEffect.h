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
        
        uint32_t effectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            unsigned int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t previousColor
        ) {
            return divideColor(
                currentColor,
                _dimFactor
            );
        }

    private:

        int _dimFactor;
};

#endif
