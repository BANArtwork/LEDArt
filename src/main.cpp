#include <Arduino.h>

// Uncomment to turn logging on.
#define USE_LOG

// Uncomment to step through each frame one at a time based on serial input.
//#define USE_FRAME_STEP

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

// Pin definitions.
#define DISTANCE_PIN 14
#define MOTOR_LIMIT_PIN 22
#define MOTOR_PIN 4
#define SW1_PIN 8
#define SW2_PIN 9

// Operating modes.
typedef enum Modes {
    MODE_OFF,
    MODE_LEDS_ONLY_NO_PROX_SENSOR,
    MODE_LEDS_AND_MOTOR_WITH_PROX_SENSOR
} Modes_t;

// Method sigs.
void updateLeds(int frame);
void checkSegments(const Segment** segs, int numSegs, uint32_t c1, uint32_t c2);
Modes_t checkMode();
void checkLeds();
void activateLeds(bool active);
void activateMotor();
void deactivateMotor();

// List of LEDs.
LinkedList<EffectLed*> leds = LinkedList<EffectLed*>();

// Chase effects.
auto chase1 = new ChasingEffect(560);
auto chase2 = new ChasingEffect(560);
auto chase3 = new ChasingEffect(560);

void setup() {

    // Set up logger.
    logSetup();

    // Start the LED driver.
    ledDriver.begin();

    // Set up pins and write HIGH to motor pin to turn it off.
    pinMode(MOTOR_LIMIT_PIN, INPUT_PULLUP);
    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(SW1_PIN, INPUT_PULLUP);
    pinMode(SW2_PIN, INPUT_PULLUP);
    digitalWrite(MOTOR_PIN, HIGH);

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

    // Dim effect.
    auto dim = new DimEffect(10);

    // Set up chase effects.
    chase1->setChaseLength(280);
    chase1->setBlockLength(30);
    chase1->setColor(0xffffff);
    chase1->setSpeed(1);
    chase1->deactivate();

    chase2->setChaseLength(560);
    chase2->setBlockLength(60);
    chase2->setColor(0xffffff);
    chase2->setSpeed(2);
    chase2->deactivate();

    chase3->setChaseLength(186);
    chase3->setBlockLength(10);
    chase3->setColor(0xffffff);
    chase3->setSpeed(3);
    chase3->deactivate();

    // Attach chase effects and dim to LEDs.
    allLedsSegment.forEach([dim](int index) {
        leds[index]->removeEffect(0);
        leds[index]->addEffect((Effect*)chase1);
        leds[index]->addEffect((Effect*)chase2);
        leds[index]->addEffect((Effect*)chase3);
        leds[index]->addEffect((Effect*)dim);
    });

    // Check to help map segments.
    //checkSegments(segments, numSegments, 0x000000ff, 0x00ff00ff);
    //checkSegments(stars, numStars, 0x00ff0000, 0x0000ff00);

    log("Setup complete");
}

void loop() {

    // Step through each frame based on console input.
    #ifdef USE_LOG
    #ifdef USE_FRAME_STEP
        if (Serial.available()) {
        Serial.clear();
    #endif
    #endif

    bool useMotorAndProxSensor = false;

    static int cycleTime = 0;
    static int cycleCount = 0;
    static bool proxTrigger = false;

    // If limit switch is active, then kill the motor.
    if (digitalRead(MOTOR_LIMIT_PIN)) {
        logSprintf("loop: Motor limit hit. Deactivating motor.\r\n");
        deactivateMotor();
    }

    // Activate LEDs in case they were turned off.
    activateLeds(true);
    
    // Get operating mode from switches.
    Modes_t mode = checkMode();
    switch (mode) {

    // Continuous LEDs, no prox sensor or motor action: Clear flag.
    case MODE_LEDS_ONLY_NO_PROX_SENSOR:

        // Make sure chase effects are active.
        chase1->activate();
        chase2->activate();
        chase3->activate();

        useMotorAndProxSensor = false;
        break;

    // LEDs and motor action with prox sensor: Set flag
    case MODE_LEDS_AND_MOTOR_WITH_PROX_SENSOR:
        useMotorAndProxSensor = true;
        break;

    // Off mode: deactivate LEDs. Update to turn them off. Then return.
    case MODE_OFF:
    default:
        activateLeds(false);
        checkLeds();
        return;
    }

    // Update LEDs.
    checkLeds();
    
    // If cycle time has elapsed...
    int now = millis();
    if (now - cycleTime > 1000) {

        // Update time var.
        cycleTime = now;

        // Inc count.
        cycleCount++;
        cycleCount %= 20;

        int speed;
        
        // On the last cycle, if we are running 
        // with the prox sensor and motor...
        if (cycleCount >= 19 && useMotorAndProxSensor) {

            // Deactivate chase effects.
            chase1->deactivate();
            chase2->deactivate();
            chase3->deactivate();

            // Deactivate motor.
            deactivateMotor();

            // And clear the trigger flag.
            proxTrigger = false;
        } 
        
        // For the last 5 cycles set speed to 9.
        else if (cycleCount >= 15) {
            speed = 9;
        }  
        
        // For the first 5 cycles, set speed to 1.
        else if (cycleCount < 6) {
            speed = 1;
        } 
        
        // For all other cycles, speed is cycle - 5.
        else {
            speed = cycleCount - 5;
        }

        // Fade from white to red as speed increases.
        uint32_t color = interpolateColors(0xffffff, 0xff0000, 9, speed);
        chase1->setColor(color);
        chase2->setColor(color);
        chase3->setColor(color);

        // Set animation speed.
        chase1->setSpeed(speed);
        chase2->setSpeed(speed);
        chase3->setSpeed(speed);
    }

    // If not using motor and prox sensor, then we are done.
    if (!useMotorAndProxSensor) return;

    // Otherwise, if prox sensor is triggered...
    int distance = analogRead(DISTANCE_PIN);
    if (distance > 300 && proxTrigger == false) {

        logSprintf("Prox trigger. Distance: %d\r\n", distance);

        // Set flag to avoid retriggering before animation is complete.
        proxTrigger = true;

        // Activate chase effects.
        chase1->activate();
        chase2->activate();
        chase3->activate();
    }

    // If prox is triggered, then activate the motor.
    if (proxTrigger) {
        activateMotor();
    }

    #ifdef USE_LOG
    #ifdef USE_FRAME_STEP
        }
    #endif
    #endif
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

/**
 * @brief Update LEDs.
 * 
 * @param frame 
 */
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

/**
 * @brief Get operating mode from switches.
 * 
 * @return Modes_t 
 */
Modes_t checkMode() {

    static Modes_t lastMode;

    if (digitalRead(SW1_PIN)) {
        if (lastMode != MODE_OFF) {
            lastMode = MODE_OFF;
            logSprintf("Mode Off.\r\n");
        }
        return MODE_OFF;
    }

    if (!digitalRead(SW2_PIN)) {

        if (lastMode != MODE_LEDS_AND_MOTOR_WITH_PROX_SENSOR) {
            lastMode = MODE_LEDS_AND_MOTOR_WITH_PROX_SENSOR;
            logSprintf("Mode LEDs and motor with prox sensor.\r\n");
        }
        return MODE_LEDS_AND_MOTOR_WITH_PROX_SENSOR;
    }

    if (lastMode != MODE_LEDS_ONLY_NO_PROX_SENSOR) {
        lastMode = MODE_LEDS_ONLY_NO_PROX_SENSOR;
        logSprintf("Mode LEDs only. Continuous.\r\n");
    }
    return MODE_LEDS_ONLY_NO_PROX_SENSOR;
}

/**
 * @brief Update LEDs and frame counter.
 */
void checkLeds() {
    static unsigned int frame = 0;
    updateLeds(frame);
    frame++;
}

/**
 * @brief Turn LEDs on or off.
 * 
 * @param active 
 */
void activateLeds(bool active) {
    EffectLed* led = leds.start();
    while (led != NULL) {
        led->activate(active);
        led = leds.next();
    }
}

static int motorKillTime;
static bool motorRunning;

void activateMotor() {

    // If the limit switch is active...
    if(digitalRead(MOTOR_LIMIT_PIN)) {

        logSprintf("activateMotor: Motor limit hit. Deactivating.\r\n");

        // Then deactivate and bail.
        deactivateMotor();
        return;
    }

    // If the motor is already running then bail.
    if (motorRunning) {
        logSprintf("activatemotor: Motor already running.\r\n");
        return;
    }

    // If the spinner has not had enough time to drop all the way, then bail.
    int now = millis();
    if (now - motorKillTime < 3000) {
        logSprintf("activateMotor: Motor kill time not elapsed: %d.\r\n", now - motorKillTime);
        return;
    }

    logSprintf("activateMotor: Activating motor.\r\n");

    // Activate motor and set state flag.
    analogWrite(MOTOR_PIN, 1);
    motorRunning = true;
}

void deactivateMotor() {

    logSprintf("deactivateMotor: Deactivating motor.\r\n");

    // Set motor kill time.
    motorKillTime = millis();

    // Deactivate motor and set state flag.
    analogWrite(MOTOR_PIN, 255);
    motorRunning = false;
}