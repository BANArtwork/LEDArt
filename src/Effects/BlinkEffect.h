#ifndef BLINKEFFECT_H
#define BLINKEFFECT_H

#include <stdint.h>
#include "Effect.h"

class BlinkEffect : Effect{

    public:

        BlinkEffect(
            uint32_t blinkColor, 
            int blinkFrames, 
            int onFrames
        ) :
            _blinkColor { blinkColor },
            _blinkFrames { blinkFrames },
            _onFrames { onFrames } 
        { 
            _rand = rand(); 
        }

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
            uint32_t c;
            bool ok = BlinkEffectAction(_blinkColor, _blinkFrames, _onFrames, frame, _rand, c);
            if(!ok) return false;
            newColor = c;
            return true;
        }

    protected:

        uint32_t _blinkColor;
        int _blinkFrames;
        int _onFrames;
        unsigned int _rand;

        static bool BlinkEffectAction(uint32_t blinkColor, int blinkFrames, int onFrames, int frame, unsigned int& rand, uint32_t& newColor) {
            int x = (frame + rand) % blinkFrames;
            if (x > onFrames) return false;
            newColor = blinkColor;
            return true;
        }
};

#endif
