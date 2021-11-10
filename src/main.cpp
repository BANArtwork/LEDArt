#include <Arduino.h>
#include "./WS2812/WS2812Serial.h"
#include "./Effects/EffectLed.h"
#include "./Effects/Map.h"
#include "./Effects/Effects.h"
#include "Logger.h"
#include "Memcheck.h"
#include "Effects/HeartsEffect.h"

// LED signal pin.
const int ledPin = 5;

// Total number of LEDs in the piece.
const int numleds = 74;

// GRAM.
byte drawingMemory[numleds * 3];
DMAMEM byte displayMemory[numleds * 12];

// LED Driver.
WS2812Serial ledDriver(
    numleds, 
    displayMemory, 
    drawingMemory, 
    ledPin, 
    WS2812_GRB
);

// List of LEDs.
LinkedList<EffectLed*> leds = LinkedList<EffectLed*>();

void setup() {

    // Set up logger.
    logSetup();

    // Start the LED driver.
    ledDriver.begin();

    // Create LEDs
    int i;
    for(i = 0; i < numleds; i++) {
        EffectLed* f = new EffectLed([](int i2, uint32_t c) { ledDriver.setPixel(i2, c); }, i, &map0);
        leds.insert(f);
    }

    // For each heart...
    for (i = 0; i < numHearts; i++){
        auto h = hearts[i];

        // Create heart effect.
        auto heartsEffect = new HeartEffect(100, 400, h.firstLed);

        // Add the effect to each LED in the heart.
        int x;
        for (x = h.firstLed; x < h.firstLed + h.numLeds; x++) {
            leds[x]->addEffect((Effect*)heartsEffect);
        }
    }

    log("Setup complete");
}

void checkLeds() {

    // Frame counter.
    static unsigned int frame = 0;

    // Time check.
    static unsigned long time = millis();
    unsigned long check = millis();
    if (check - time > 20) {
        time = check;
    
        // Run through list of LEDs and update them.
        EffectLed* led = leds.start();
        while (led != NULL) {
            led->update(frame);
            led = leds.next();
        }

        // Show updated LEDs.
        ledDriver.show();
        frame++;
    }
}

void loop() {
   checkLeds();
}


