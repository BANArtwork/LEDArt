#include <Arduino.h>

// Uncomment to turn logging on.
//#define USE_LOG

// Uncomment to step through frames with serial commands.
//#define SERIAL_FRAME_STEP
#if defined(SERIAL_FRAME_STEP)
#define USE_LOG
#endif

#include "Util/Logger.h"
#include "Util/Memcheck.h"

#include "Installation.h"
#include "Hardware/Driver.h"
#include "Hardware/EffectLed.h"

#include "Effects/DimEffect.h"
#include "Effects/ChasingRainbowEffect.h"
#include "Effects/HeartsEffect.h"
#include "Effects/SolidColorEffect.h"
#include "Effects/SparkleEffect.h"
#include "Effects/SimpleRainbowEffect.h"
#include "Effects/WhatADayAwayEffect.h"
#include "Effects/TwoColorFadeEffect.h"
#include "Effects/RandomColorSparkleEffect.h"
#include "Effects/RadiateEffect.h"
#include "Effects/SegmentFadeEffect.h"
#include "Effects/PulseRainbowEffect.h"
//#include "Effects/MultiLedSparkleEffect.h"

void updateLeds(int frame);
void checkSegments();

// List of LEDs.
LinkedList<EffectLed*> leds = LinkedList<EffectLed*>();

void setup() {

    // Set up logger.
    logSetup();

    // Start the LED driver.
    ledDriver.begin();

    // Effect to black out all LEDs on startup.
    auto black = new SolidColorEffect(0);

    // For all LEDs...
    allLedsSegment.forEach([black](int index){

        // Create EffectLed object.
        EffectLed* f = new EffectLed(
            [](int i, uint32_t c) { ledDriver.setPixel(i, c); }, 
            index, 
            &map0
        );

        // Black out LED.
        f->addEffect((Effect*)black);

        // Add to the list of LEDs.
        leds.insert(f);
    });
    
    // Update to apply black effect.
    updateLeds(0);

    // Check to help map segments.
     checkSegments();

     //auto rainbow = new ChasingRainbowEffect(1, 768, 20);
    // static const uint32_t c[] = {0x00ffffff, 0, 0, 0};
    // auto rainbow = new ChasingFadeEffect(1, 256, 20, 4, c);
    // auto dim = new DimEffect(10);
    // allLedsSegment.forEach([rainbow, dim](int index){
    //     leds[index]->removeEffect(0);
    //     leds[index]->addEffect((Effect*)rainbow);
    //     leds[index]->addEffect((Effect*)dim);
    // });

    log("Setup complete");
}

/**
 * @brief For each segment in the segments array, alternate between red 
 * and green. This method is to help map and build the segments list.
 */
void checkSegments() {

    auto red = new SolidColorEffect(0xff0000);
    auto green = new SolidColorEffect(0x00ff00);
    auto dim = new DimEffect(10);

    int i;
    for (i = 0; i < numSegments; i++) {
        auto color = (i % 2) ? red : green;
        auto seg = segments[i];
        seg->forEach([color, dim](int ledIndex) {
            auto led = leds[ledIndex];
            led->removeEffect(0);
            led->addEffect((Effect*)color);
            led->addEffect((Effect*)dim);
        });
    }

    updateLeds(0);
}

void updateLeds(int frame) {

    // Run through list of LEDs and update them.
    EffectLed* led = leds.start();
    while (led != NULL) {
        led->update(frame);
        led = leds.next();
    }

    // Show updated LEDs.
    ledDriver.show();
}

void checkLeds() {

    // Frame counter.
    static unsigned int frame = 0;

    // If debug stepping, check for Serial input.
    #if defined(SERIAL_FRAME_STEP)
    if (!Serial.available()) return;
    int c = Serial.read();
    if (c != ' ') return;
    #endif

    // Update LEDs.
    updateLeds(frame);
        
    // Debug print the current frame.
    #if defined(SERIAL_FRAME_STEP)
    Serial.printf("%d ", frame);
    #endif

    // Inc frame.
    frame++;
}


void loop() {
    checkLeds();
}


