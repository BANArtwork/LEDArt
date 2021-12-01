#include <Arduino.h>

// Uncomment to turn logging on.
//#define USE_LOG

#include "Util/Logger.h"
#include "Util/Memcheck.h"

#include "Installation.h"
#include "Hardware/Driver.h"
#include "Hardware/EffectLed.h"

#include "Effects/DimEffect.h"
#include "Effects/FadeRainbowEffect.h"
#include "Effects/HeartsEffect.h"
#include "Effects/SolidColorEffect.h"
#include "Effects/SparkleEffect.h"
#include "Effects/SimpleRainbowEffect.h"
#include "Effects/WhatADayAwayEffect.h"
#include "Effects/TwoColorFadeEffect.h"
#include "Effects/RandomColorSparkleEffect.h"

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

    // auto white = new SolidColorEffect(0xffffff);
    // auto sparkle = new RandomColorSparkleEffect(10, 10);

    // allLedsSegment.forEach([white, sparkle](int index){
    //     leds[index]->removeEffect(0);
    //     leds[index]->addEffect((Effect*)white);
    //     leds[index]->addEffect((Effect*)sparkle);
    // });

    // auto rainbow = new FadeRainbowEffect(10, 5);

    // shortArc->forEach([rainbow](int index){
    //     leds[index]->removeEffect(0);
    //     leds[index]->removeEffect(1);
    //     leds[index]->addEffect((Effect*)rainbow);
    // });

    // longArc->forEach([rainbow](int index){
    //     leds[index]->removeEffect(0);
    //     leds[index]->removeEffect(1);
    //     leds[index]->addEffect((Effect*)rainbow);
    // });

    // auto dim = new DimEffect(10);
    // allLedsSegment.forEach([dim](int index){
    //     leds[index]->addEffect((Effect*)dim);
    // });

    // Check to help map segments.
    checkSegments();

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


