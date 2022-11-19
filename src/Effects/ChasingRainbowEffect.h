#ifndef CHASINGRAINBOWEFFECT_H
#define CHASINGRAINBOWEFFECT_H

#include "ChasingFadeEffect.h"
#include "./../Util/ColorConverters.h"

/**
 * @brief Chasing rainbow effect.
 */
class ChasingRainbowEffect : public ChasingFadeEffect {

    public:

        /**
         * @brief Construct a new Chasing Rainbow Effect object
         * 
         * @param frameDivisor To calculate animation frame. Higher value ==
         * slower animation.
         * @param animationLength Total number of frames in the animation.
         * @param fadeStep Number of 'steps' in the color difference 
         * between neighboring LEDs. Higher value == 'narrower' rainbow.
         */
        ChasingRainbowEffect(
            int animationLength,
            int fadeStep
        ) :
        ChasingFadeEffect(
            animationLength,
            fadeStep,
            3,
            _rainbowColors
        )
        {}

    private:

        static const uint32_t _rainbowColors[];

};

const uint32_t ChasingRainbowEffect::_rainbowColors[] = 
    { 0xff0000, 0x00ff00, 0x0000ff };

#endif
