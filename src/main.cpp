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

    // Apply solid white effect to all LEDs first.
    auto white = new SolidColorEffect(0xffffff);
    auto whiteDim = new DimEffect(4);
    allLedsSegment.forEach([white, whiteDim](int index){
        leds[index]->removeEffect(0);
        leds[index]->addEffect((Effect*)white);
        leds[index]->addEffect((Effect*)whiteDim);
    });

    // Apply rainbow effect to left eye.
    auto rainbow = new ChasingRainbowEffect(1, 256, 5);
    auto dim = new DimEffect(1);
    segments[5]->forEach([rainbow, dim](int index){
        auto l = leds[index];
        l->removeEffect(0);
        l->removeEffect(1);
        l->addEffect((Effect*)rainbow);
        l->addEffect((Effect*)dim);
    });

    // And right eye.
    segments[11]->forEach([rainbow, dim](int index){
        auto l = leds[index];
        l->removeEffect(0);
        l->removeEffect(1);
        l->addEffect((Effect*)rainbow);
        l->addEffect((Effect*)dim);
    });

    // Apply pulsing color and sparkles to all circle segments.
    static const uint32_t sparkleColors[] = {
        0x00ff0000, 0x0000ff00, 0x000000ff,
        0x00ffff00, 0x0000ffff, 0x00ff00ff
    };

    for (int i = 0; i < numCircles; i++) {
        auto sparkle = new SparkleEffect(1, 100, 300, 6, sparkleColors);
        circles[i]->forEach([white, sparkle, whiteDim](int index){
            auto l = leds[index];
            l->removeEffect(0);
            l->removeEffect(1);
          
            l->addEffect((Effect*)white);
            l->addEffect((Effect*)whiteDim);
            l->addEffect((Effect*)sparkle);
        });
    }

    // Check to help map segments.
    //checkSegments();

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


