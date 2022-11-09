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

#define BUTTON_PIN 9

void updateLeds(int frame);
void checkSegments(const Segment** segs, int numSegs, uint32_t c1, uint32_t c2);

// List of LEDs.
LinkedList<EffectLed*> leds = LinkedList<EffectLed*>();

// Dim effects.
Effect* dim1;
Effect* dim2;
Effect* dim3;
Effect* rainbow;
Effect* pink;
Effect* chase;
Effect* sparkles;

void deactivateAll() {
    dim1->deactivate();
    dim2->deactivate();
    dim3->deactivate();
    rainbow->deactivate();
    pink->deactivate();
    chase->deactivate();
    sparkles->deactivate();
}

void setup() {

    // Set up logger.
    logSetup();

    pinMode(BUTTON_PIN, INPUT_PULLUP);

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

     rainbow = (Effect*) new ChasingRainbowEffect(5, 256, 5);
    dim1 = (Effect*) new DimEffect(1);
    dim2 = (Effect*) new DimEffect(2);
    dim3 = (Effect*) new DimEffect(4);
    pink = (Effect*) new SolidColorEffect(0xfc03c6);
    uint32_t redSparkle[1] = { 0xff0000 };
    sparkles = (Effect*) new SparkleEffect(1, 5, 20, 1, redSparkle);
    dim2->deactivate();
    dim3->deactivate();

     chase = (Effect*) new ChasingEffect(6, 60, 0x7f7f7f, 5);

    
        allLedsSegment.forEach([rainbow, chase, pink, sparkles, dim1, dim2, dim3 ](int index) {

            leds[index]->removeEffect(0);

            leds[index]->addEffect(rainbow);
            leds[index]->addEffect(chase);

            leds[index]->addEffect(pink);

       //     auto sparkle = new SparkleEffect(1, 400, 500);
            leds[index]->addEffect((Effect*)dim1);
            leds[index]->addEffect((Effect*)dim2);
            leds[index]->addEffect((Effect*)dim3);
            //leds[index]->addEffect((Effect*)sparkle);

            leds[index]->addEffect(sparkles);
        });
    
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

void switchModes(int mode) {

    deactivateAll();

    switch(mode) {
        case 0:
        case 1:
        case 2:
            rainbow->activate();
            chase->activate();
            break;

        case 3:
        case 4:
        case 5:
            pink->activate();
            sparkles->activate();
            break;
    }

    switch(mode) {
        case 0:
        case 3:
            dim1->activate();
            break;

        case 1:
        case 4:
            dim2->activate();
            break;

        case 2:
        case 5:
            dim3->activate();
            break;
    }
}

void checkButton() {

    static int startTime = 0;
    static bool pressing = false;
    static int mode = 3;


    if (!digitalRead(BUTTON_PIN)) {
        if (!pressing) {
            startTime = millis();
            pressing = true;
        } else if (millis() - startTime > 200) {
            mode++;
            mode = mode % 6;
            switchModes(mode);
            pressing = false;
        }
    } else {
        pressing = false;
    }
}

void loop() {
   checkLeds();
   checkButton();
}


