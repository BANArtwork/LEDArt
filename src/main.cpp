#include <Arduino.h>
#include "./WS2812/WS2812Serial.h"
#include "./Effects/EffectLed.h"
#include "./Effects/Map.h"
#include "./Effects/Effects.h"
#include "Logger.h"
#include "Memcheck.h"

const int numled = 147;
const int pin = 5;

byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED

WS2812Serial ledDriver(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

LinkedList<EffectLed*> leds = LinkedList<EffectLed*>();

// bool sparkles2() {

//     unsigned int rnd = rand() % 100;
//     auto e = [rnd](int x, int y, int z, int i3, unsigned int f, uint32_t c, uint32_t& r) { return sparkles(10, 20, 20, rnd, x, y, z, i3, f, c, r); };
// }

void setup() {

    logSetup();

    // Start the LED driver.
    ledDriver.begin();

    int i;

        auto slowRainbow = new FadeRainbowEffect(10, 4);
        auto fastRainbow = new FadeRainbowEffect(10, 1);
        auto dim = new DimEffect(1);
        auto solid = new SolidColorEffect(0);

    // For each LED in the arc...
    for(i = 0; i < numled; i++) {

        // Create EffecTLed object.
        EffectLed* f = new EffectLed([](int i2, uint32_t c) { ledDriver.setPixel(i2, c); }, i, &map0);
        f->addEffect((Effect*)solid);

        // Add the LED to the list.
        leds.insert(f);
    }

    for(i = 0; i < 74; i++) {
        auto l = leds[i];
        if (l == NULL) break;
        l->removeEffect(0);

        auto sparkle = new SparkleEffect(20, 500, rand());

        l->addEffect((Effect*)slowRainbow);
        l->addEffect((Effect*)dim);
        l->addEffect((Effect*)sparkle);
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


