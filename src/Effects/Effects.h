#ifndef EFFECTS_H
#define EFFECTS_H

#include "Colors.h"
#include <stdint.h>
#include <Arduino.h>
#include "./../Logger.h"
#include "Util.h"

/**
 * @brief Base effect class.
 */
class Effect {

    public:

        virtual bool effectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            long unsigned int currentColor, 
            long unsigned int& result
        );
};

/**
 * @brief Just set LED to the given color.
 */
class SolidColorEffect : Effect {

    public:

        SolidColorEffect(uint32_t color) : _color { color } {}

        bool effectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            long unsigned int currentColor, 
            long unsigned int& result
        ) {
            result = _color;
            return true;
        }

    private:

        uint32_t _color;
};

/**
 * @brief Fading rainbow effect.
 */
class FadeRainbowEffect : Effect {

    public:

        FadeRainbowEffect(int fadeStep, int speed) : 
            _fadeStep { fadeStep }, 
            _speed { speed } {}

        bool effectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            long unsigned int currentColor, 
            long unsigned int& result
        ) {
            return fadeRainbow(
                _fadeStep, 
                _speed, 
                ledX, 
                ledY, 
                ledZ, 
                ledIndex, 
                frame, 
                currentColor, 
                result
            );
        }

    private:

        int _fadeStep;
        int _speed;

        static bool fadeRainbow(
            int fadeStep,
            int speed,
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t& result
        ) {
            // Get frame for this effect (frame / speed factor).
            unsigned int x = frame / speed;

            // Add LED index to create rainbow pattern.
            x = (ledIndex + x);

            // Multiply by fade step to set physical length of rainbow.
            x = x * fadeStep;
            
            // Mod by 768 to loop rainbow effect.
            x = x % 768;

            // Calculate RGB values for this step.
            uint8_t r, g, b;
            if (x < 256) {
                r = 255 - x;
                g = x;
                b = 0;
            } else if (x < 512) {
                r = 0;
                g = 511 - x;
                b = x - 256;
            } else {
                r = x - 512;
                g = 0;
                b = 767 - x;
            }

            // Set result and return true.
            result = rgbToUint32(r, g, b);
            return true;
        }
};

/**
 * @brief Effect to dim LEDs.
 */
class DimEffect : Effect {

    public:

        DimEffect(int dimFactor) : _dimFactor { dimFactor } {}
        
        bool effectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            long unsigned int currentColor, 
            long unsigned int& result
        ) {
            return dim(
                _dimFactor, 
                ledX, 
                ledY, 
                ledZ, 
                ledIndex, 
                frame, 
                currentColor, 
                result
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
            uint32_t& result
        ) {
            uint8_t r, g, b;
            uint32toRgb(currentColor, r, g, b);
            r /= d;
            g /= d;
            b /= d;
            result = rgbToUint32(r, g, b);
            return true;
        }
};

class SparkleEffect : Effect {

    public:

        SparkleEffect(int speed, int frequency, int rand) : 
            _speed { speed }, 
            _frequency { frequency },
            _rand { rand } {}
        
        bool effectAction(
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            long unsigned int currentColor, 
            long unsigned int& result
        ) {
            return sparkle(
                _speed,
                _frequency, 
                _rand,
                ledX, 
                ledY, 
                ledZ, 
                ledIndex, 
                frame, 
                currentColor, 
                result
            );
        }

    private:

        int _speed;
        int _frequency;
        int _rand;

        static bool sparkle(
            int speed,
            int frequency,
            int rand,
            int ledX, 
            int ledY, 
            int ledZ, 
            int ledIndex, 
            unsigned int frame,
            uint32_t currentColor, 
            uint32_t& result
        ) {
            // Calculate var for sparkle animation.
            unsigned int x = frame + rand;
            x = x % frequency;
            x = x * speed;
            uint8_t w;

            // Fade up.
            if (x < 256) {
                w = x;

            // Fade down.
            } else if (x < 512) {
                w = 511 - x;

            // No sparkle.
            } else {
                return false;
            }

            // Get greater of current color or white value.
            uint8_t r, g, b;
            uint32toRgb(currentColor, r, g, b);
            r = (w > r) ? w : r;
            g = (w > g) ? w : g;
            b = (w > b) ? w : b;

            // Set result and return true.
            result = rgbToUint32(r, g, b);
            return true; 
        }
};


/**
 * @brief Simple colors array.
 */
uint32_t colors[] = {
    RED_SOFT, 
    GREEN_SOFT, 
    BLUE_SOFT, 
    YELLOW_SOFT, 
    PINK_SOFT, 
    ORANGE_SOFT, 
    WHITE_SOFT
};

/**
 * @brief A simple scrolling rainbow effect.
 */
bool simpleRainbow(
    int ledX, 
    int ledY, 
    int ledZ, 
    int ledIndex, 
    unsigned int frame,
    uint32_t currentColor, 
    uint32_t& result
) {
    unsigned int i = (ledIndex + frame) % 7;
    auto c = colors[i];
    result = c;
    return true;
}



#endif
