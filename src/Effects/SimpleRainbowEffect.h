#ifndef SIMPLERAINBOWEFFECT_H
#define SIMPLERAINBOWEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"
#include "./../Util/Colors.h"

/**
 * @brief Simple rainbow effect with predefined colors.
 */
class SimpleRainbowEffect : Effect {

    public:

        SimpleRainbowEffect() {}

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
            return simpleRainbow(ledIndex, frame, newColor);
        }

    private:

        // Colors to cycle through.
        static constexpr uint32_t colors[] = {
            RED_SOFT, 
            GREEN_SOFT, 
            BLUE_SOFT, 
            YELLOW_SOFT, 
            PINK_SOFT, 
            ORANGE_SOFT, 
            WHITE_SOFT
        };

        static bool simpleRainbow(
            int ledIndex, 
            unsigned int frame,
            uint32_t& newColor
        ) {
            unsigned int i = (ledIndex + frame) % 7;
            auto c = colors[i];
            newColor = c;
            return true;
        }
};

#endif
