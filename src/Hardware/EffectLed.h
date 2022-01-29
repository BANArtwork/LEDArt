#ifndef EFFECTLED_H
#define EFFECTLED_H

#include "WS2812/WS2812Serial.h"
#include "./Util/LinkedList.h"
#include "./Effects/Effect.h"
#include "LedMap.h"

/**
 * @brief A class to describe an LED which has a series of effects applied to
 * generate its color pattern.
 */
class EffectLed {

    public:

        /**
         * @brief Method signature for a driver that will set the pixel color.
         */
        typedef void (*PixelDriver_t)(int index, uint32_t color);

        /**
         * @brief Construct a new Led object
         * 
         * @param driver The LED driver.
         * @param index The index of this LED in it's strip.
         * @param map The map to set x, y, and z values from the index.
         */
        EffectLed(
            PixelDriver_t driver,
            int index,
            LedMap* map
        ) : 
            _driver { driver },
            _ledIndex { index } 
        {
            _ledX = map->getX(_ledIndex);
            _ledY = map->getY(_ledIndex);
            _ledZ = map->getZ(_ledIndex);
            _color = 0;
            _effectList = LinkedList<Effect*>();
        };

        /**
         * @brief Run through all effects and update this LEDs color value.
         */
        void update(unsigned int frame) {

            // Init working var.
            uint32_t color = 0;

            // Run each effect action.
            _effectList.forEach([&](Effect* effect){
                if (effect->isActive()) {
                    color = effect->effectAction(
                        _ledX, 
                        _ledY, 
                        _ledZ, 
                        _ledIndex, 
                        frame, 
                        color, 
                        _color
                    );
                }
            });

            // If the color has changed, then update the LED.
            if (color != _color) {
                _driver(_ledIndex, color);
                _color = color;
            }
        };

        /**
         * @brief Add an effect to this LED.
         * 
         * @param effect The effect to add.
         * @param index Where in the list to add it. (-1 adds to end of list)
         */
        void addEffect(Effect* effect, int index = -1) {
            _effectList.insert(effect, index);
        };

        /**
         * @brief Remove an effect.
         * 
         * @param index Index of the effect to remove. (-1 removes last effect)
         */
        void removeEffect(int index = -1) {
            _effectList.remove(index);
        };

        uint32_t getColor() {
            return _color;
        }
        
    private:

        // Driver for this LED.
        PixelDriver_t _driver;

        // The index of this LED in the LED strip.
        int _ledIndex;

        // The physical location of this LED in the installation.
        int _ledX;
        int _ledY;
        int _ledZ;
            
        // The current LED color;
        uint32_t _color;

        // List of effects.
        LinkedList<Effect*> _effectList;
};

#endif
