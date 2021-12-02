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

    // Add dim white solid color to all LEDs and then random color sparkle.
    // auto white = new SolidColorEffect(0xffffff);
    // auto dim = new DimEffect(10);
    // allLedsSegment.forEach([white, dim](int index){
    //     leds[index]->removeEffect(0);
    //     leds[index]->addEffect((Effect*)white);
    //     leds[index]->addEffect((Effect*)dim);

    //     auto sparkle = new RandomColorSparkleEffect(50, 200, 1);
    //     leds[index]->addEffect((Effect*)sparkle);
    // });

    auto white = new SolidColorEffect(0xffffff);

    auto blue = new SolidColorEffect(0x1b218f);
    auto blueF = [blue](int index) {
        leds[index]->removeEffect(0);
        leds[index]->addEffect((Effect*)blue);

        // auto sparkle = new RandomColorSparkleEffect(50, 200, 1);
        auto sparkle = new SparkleEffect(100, 400, 2);
        leds[index]->addEffect((Effect*)sparkle);
    };

    segments[0]->forEach([white](int index){
        leds[index]->removeEffect(0);
        leds[index]->addEffect((Effect*)white);
    });
    segments[1]->forEach([white](int index){
        leds[index]->removeEffect(0);
        leds[index]->addEffect((Effect*)white);
    });
    segments[10]->forEach([white](int index){
        leds[index]->removeEffect(0);
        leds[index]->addEffect((Effect*)white);
    });
    segments[12]->forEach([white](int index){
        leds[index]->removeEffect(0);
        leds[index]->addEffect((Effect*)white);
    });

    for (int x = 2; x < 4; x++) {
        segments[x]->forEach(blueF);
    }

    // Then rmove all effects from the two arcs and add rainbow effect.
    auto rainbow = new FadeRainbowEffect(10, 1);

    auto dim = new DimEffect(4);
    shortArc->forEach([white, dim](int index){
        leds[index]->removeEffect(0);
        leds[index]->addEffect((Effect*)white);
        // auto sparkle = new RandomColorSparkleEffect(50, 200, 1);
        auto sparkle = new SparkleEffect(50, 200, 1, 0);
        leds[index]->addEffect((Effect*)sparkle);
    });

    longArc->forEach([white, dim](int index){
        leds[index]->removeEffect(0);
        leds[index]->addEffect((Effect*)white);
        // auto sparkle = new RandomColorSparkleEffect(50, 200, 1);

        auto sparkle = new SparkleEffect(50, 200, 1, 0);
        leds[index]->addEffect((Effect*)sparkle);
    });


    auto red = new SolidColorEffect(0x70040d);
    auto redF = [red](int index) {
        leds[index]->removeEffect(0);
        leds[index]->addEffect((Effect*)red);
        
        // auto sparkle = new RandomColorSparkleEffect(50, 200, 1);
        auto sparkle = new SparkleEffect(100, 400, 2);
        leds[index]->addEffect((Effect*)sparkle);
    };


    int c[] = { 5, 6, 7, 9, 11 };
    for (int y = 0; y < 5; y++) {
        int index = c[y];
        segments[index]->forEach(redF);
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


