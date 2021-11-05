#ifndef EFFECTS_H
#define EFFECTS_H

#include "./../WS2812/WS2812Serial.h"
#include "Map.h"
#include "LinkedList.h"

typedef bool (*EffectAction_t)(
    int ledX, 
    int ledY, 
    int ledZ, 
    int ledIndex, 
    unsigned int frame,
    uint32_t currentColor, 
    uint32_t& result
);

class EffectLed {

    public:

        /**
         * @brief Construct a new Led object
         * 
         * @param driver The LED driver.
         * @param index The index of this LED in it's strip.
         * @param map The map to set x, y, and z values from the index.
         */
        EffectLed(
            WS2812Serial* driver,
            int index,
            LedMap* map
        ) : 
            _driver { driver },
            _ledIndex { index } 
        {
            _ledX = 0; //map->getX(_ledIndex);
            _ledY = 0; //map->getY(_ledIndex);
            _ledZ = 0; //map->getZ(_ledIndex);
            _color = 0;
            _effectList = LinkedList<EffectAction_t>();
        };

        /**
         * @brief Run through all effects and update this LEDs color value.
         */
        void update(unsigned int frame) {

            // Init working var.
            uint32_t color = _color;

            // Get first effect item.
            auto effect= _effectList.start();

            // For all efects...
            while (effect != NULL) {

                // Check if it gives us an updated color.
                uint32_t r;
                bool hasNewColor = effect(_ledX, _ledY, _ledZ, _ledIndex, frame, color, r);

                // If it does, then update color.
                if(hasNewColor) color = r;
            
                // Go on to next effect.
                effect = _effectList.next();
            }

            // If the color has changed, then update the LED.
            if (color != _color) {
                _driver->setPixel(_ledIndex, color);
                _color = color;
            }
        };

        void addEffect(EffectAction_t effect, int index = -1) {
            _effectList.insert(effect, index);
        };

        void removeEffect(int index = -1) {
            _effectList.remove(index);
        };

    private:

    // Pointer to the driver for this LED.
    WS2812Serial* _driver;

    // The index of this LED in the LED strip.
    int _ledIndex;

    // The physical location of this LED in the installation.
    int _ledX;
    int _ledY;
    int _ledZ;
    
    // The current LED color;
    uint32_t _color;

    // List of effects.
    LinkedList<EffectAction_t> _effectList;
};

#endif
