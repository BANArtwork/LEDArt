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

uint32_t colors[] = {0x7f7f7f, 0xaf4f4f, 0xcf0f0f};

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

    auto rainbow = new ChasingRainbowEffect(256, 5);
    rainbow->setFrameDivisor(5);
    auto dim = new DimEffect(10);
    auto chase = new ChasingEffect(560, 280, 0x7f7f7f, 30); // 1 = 560, 2 = 280, 3 = 186
    chase->setSpeed(1);

    auto chase2 = new ChasingEffect(560, 560, 0x7f7f7f, 60); // 1 = 560, 2 = 280, 3 = 186
    auto chase3 = new ChasingEffect(560, 186, 0xff0000, 10); // 1 = 560, 2 = 280, 3 = 186
chase2->setSpeed(2);
chase2->setSpeed(3);
    static int cycleCounter = 0;

    chase->setOnAnimationCompleteCallback([chase](){    
         cycleCounter++;
        cycleCounter %= 6;
        chase->setSpeed(cycleCounter + 1);
        chase->setColor(colors[cycleCounter % 3]);
        logSprintf("Cycle counter: %d\r\n", cycleCounter);
   
    });
    chase2->setOnAnimationCompleteCallback([chase2](){    
         cycleCounter++;
        cycleCounter %= 6;
        chase2->setSpeed(cycleCounter + 2);
        chase2->setColor(colors[cycleCounter % 3]);
        logSprintf("Cycle counter: %d\r\n", cycleCounter);
   
    });
    chase3->setOnAnimationCompleteCallback([chase3](){    
         cycleCounter++;
        cycleCounter %= 6;
        chase3->setSpeed(cycleCounter + 3);
        logSprintf("Cycle counter: %d\r\n", cycleCounter);
   
    });
    
        allLedsSegment.forEach([rainbow, dim, chase, chase2, chase3](int index) {

            leds[index]->removeEffect(0);
            //leds[index]->addEffect((Effect*)rainbow);
            auto sparkle = new SparkleEffect(400, 500);
            //leds[index]->addEffect((Effect*)sparkle);
            leds[index]->addEffect((Effect*)chase);
            leds[index]->addEffect((Effect*)chase2);
            leds[index]->addEffect((Effect*)chase3);
            leds[index]->addEffect((Effect*)dim);
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
    #ifdef USE_LOG
        if (Serial.available()) {
        Serial.clear();
    #endif
    checkLeds();
    #ifdef USE_LOG
        }
    #endif
}


