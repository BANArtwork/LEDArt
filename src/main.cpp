#include <Arduino.h>

// Uncomment to turn logging on.
//#define USE_LOG

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
#include "Effects/ChasingEffect.h"

void updateLeds(int frame);
void checkSegments(const Segment** segs, int numSegs, uint32_t c1, uint32_t c2);

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

    auto rainbow = new ChasingRainbowEffect(7, 256, 5);
    auto dim = new DimEffect(1);
    auto chase = new ChasingEffect(6, 80, 0xffffff, 10);

    
        allLedsSegment.forEach([rainbow, dim, chase](int index) {

            leds[index]->removeEffect(0);
            leds[index]->addEffect((Effect*)rainbow);
            auto sparkle = new SparkleEffect(1, 400, 500);
            //leds[index]->addEffect((Effect*)dim);
            //leds[index]->addEffect((Effect*)sparkle);
            leds[index]->addEffect((Effect*)chase);
        });
    
    // for (int i = 0; i < numStars; i++) {
    //     auto s = stars[i];
    //     //auto blink = new BlinkEffect(0xffffff, 500, 500);
    //     auto solid = new SolidColorEffect(0xffffff);
    //     s->forEach([ solid](int index) {
    //         leds[index]->removeEffect(0);
    //         leds[index]->removeEffect(1);
    //         //leds[index]->removeEffect(2);
    //         leds[index]->addEffect((Effect*)solid);
    //     });
    // };

    // allLedsSegment.forEach([rainbow, dim](int index) {
    //     leds[index]->removeEffect(0);
    //     leds[index]->addEffect((Effect*)rainbow);
    //     auto sparkle = new SparkleEffect(10, 1500, rand());
    //     leds[index]->addEffect((Effect*)sparkle);
    //     leds[index]->addEffect((Effect*)dim);
    // });

    // Check to help map segments.
    //checkSegments(segments, numSegments, 0x000000ff, 0x00ff00ff);
    //checkSegments(stars, numStars, 0x00ff0000, 0x0000ff00);

    log("Setup complete");
}

/**
 * @brief For each segment in the segments array, alternate between red 
 * and green. This method is to help map and build the segments list.
 */
void checkSegments(const Segment** segs, int numSegs, uint32_t c1, uint32_t c2) {

    auto red = new SolidColorEffect(c1);
    auto green = new SolidColorEffect(c2);
    auto dim = new DimEffect(3);

    int i;
    for (i = 0; i < numSegs; i++) {
        auto color = (i % 2) ? red : green;
        auto seg = segs[i];
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

    // Time check.
    //static unsigned long time = millis();
    //unsigned long check = millis();
    //if (check - time > 1) {
        //time = check;
    
        updateLeds(frame);
        frame++;
    //}
}

void loop() {
   checkLeds();
}


