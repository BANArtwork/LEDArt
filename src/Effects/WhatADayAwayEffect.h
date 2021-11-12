#ifndef WHAT_A_DAY_AWAY_EFFECT_H
#define WHAT_A_DAY_AWAY_EFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"
#include "../Hardware/Segment.h"
#include "../Util/Logger.h"
#include "../Util/LinkedList.h"
#include "../Hardware/EffectLed.h"

class WhatADayAwayEffect : Effect {

    public:

        WhatADayAwayEffect(
            int frameDiv, 
            const Segment* mainArc, 
            const Segment** spokes, 
            int numSpokes,
            LinkedList<EffectLed*>* leds
        ) :
            _frameDiv { frameDiv }, 
            _mainArc { mainArc },
            _spokes { spokes },
            _numSpokes { numSpokes },
            _leds { leds } {}

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
            return _effectAction(_frameDiv, _mainArc, _spokes, _leds, _numSpokes, ledIndex, frame, newColor);
        }

    private:

        const Segment* _mainArc;
        const Segment** _spokes;
        int _numSpokes;
        int _animationSteps;
        int _frameDiv;

        static const uint32_t TEAL = 0x38e1ff;
        static const uint32_t MAGENTA = 0xeb00e7;
        static const uint32_t MIDDLE = 0x009171f3;

        LinkedList<EffectLed*>* _leds;

        static bool _effectAction(
            int frameDiv,
            const Segment* mainArc,
            const Segment** spokes,
            LinkedList<EffectLed*>* leds,
            int numSpokes,
            int ledIndex, 
            unsigned int frame,
            uint32_t& newColor
        ) {
            // Spoke LED:
            if (!(mainArc->isInSegment(ledIndex))) {
                int spokeIndex = findSpokeSegment(spokes, numSpokes, ledIndex);
                int rootLed = (mainArc->getCount() * spokeIndex) / numSpokes;
                rootLed = (mainArc->getCount() - 1) - rootLed;
                uint32_t spokeColor = leds->get(rootLed)->getColor();
                newColor = spokeColor;
                return true;
            }

            // Animation halfway point.
            int half = mainArc->getCount();

            // Total number of animation frames.
            int animFrames = half * 2;

            // Cuurent animation frame.
            int currentFrame = ((frame / frameDiv) + ledIndex) % animFrames;

            // Fade from teal to magenta or from magenta back to teal.
            int interpPoint = (currentFrame < half) ? 
                currentFrame : 
                (animFrames - currentFrame);

            uint32_t c = interpolateColors(MAGENTA, TEAL, half, interpPoint);
            newColor = c;

            // pos = abs(ledindex - (steps / 2))

            return true;
        }

        static int findSpokeSegment(const Segment** spokes, int numSpokes, int x){
            int i;
            for (i = 0; i < numSpokes; i++) {
                if (spokes[i]->isInSegment(x)) return i;
            }
            return -1;
        }
};


#endif
