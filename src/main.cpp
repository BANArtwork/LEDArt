#include <Arduino.h>
#include "./WS2812/WS2812Serial.h"
#include "./Effects/EffectLed.h"
#include "./Effects/Map.h"

const int numled = 5;
const int pin = 24;

// Usable pins:
//   Teensy LC:   1, 4, 5, 24
//   Teensy 3.2:  1, 5, 8, 10, 31   (overclock to 120 MHz for pin 8)
//   Teensy 3.5:  1, 5, 8, 10, 26, 32, 33, 48
//   Teensy 3.6:  1, 5, 8, 10, 26, 32, 33
//   Teensy 4.0:  1, 8, 14, 17, 20, 24, 29, 39
//   Teensy 4.1:  1, 8, 14, 17, 20, 24, 29, 35, 47, 53

byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED

WS2812Serial ledDriver(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

LinkedList<EffectLed*> leds = LinkedList<EffectLed*>();



/*
#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF
*/

#define RED    0x160000
#define GREEN  0x001600
#define BLUE   0x000016
#define YELLOW 0x101400
#define PINK   0x120009
#define ORANGE 0x100400
#define WHITE  0x101010

uint32_t colors[] = {RED, GREEN, BLUE, YELLOW, PINK, ORANGE, WHITE};
bool rainbow(
    int ledX, 
    int ledY, 
    int ledZ, 
    int ledIndex, 
    unsigned int frame,
    uint32_t currentColor, 
    uint32_t& result
) {
    unsigned int i = (ledIndex + frame) % 7;
    auto c = colors[i];
    result = c;
    return true;
}

void colorWipe(int color, int wait) {
  for (int i=0; i < ledDriver.numPixels(); i++) {
    ledDriver.setPixel(i, color);
    ledDriver.show();
    delayMicroseconds(wait);
  }
}

const int ledPin =  LED_BUILTIN;
int ledState = LOW;  

void setup() {

    pinMode(ledPin, OUTPUT);

    // Init serial.
    Serial.begin(9600);
    while (!Serial) {;}

    Serial.println("start");

    ledDriver.begin();

    int i;
    for(i = 0; i < 5; i++) {

        EffectLed* f = new EffectLed(&ledDriver, i, NULL);
        f->addEffect(rainbow);
        leds.insert(f);
    }
}

void toggleLed() {
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
}

void mine() {
    static unsigned int f = 0;
    static unsigned long time = millis();
    unsigned long check = millis();
    if (check - time > 200) {
        time = check;
    
        
        EffectLed* led = leds.start();
        while (led != NULL) {
            led->update(f);
            led = leds.next();
        }

        ledDriver.show();
        f++;
    }
}

void test() {


    //Serial.println("test");

    
  // change all the LEDs in 1.5 seconds
  int microsec = 1500000 / ledDriver.numPixels();

  colorWipe(RED, microsec);
  colorWipe(GREEN, microsec);
  colorWipe(BLUE, microsec);
  colorWipe(YELLOW, microsec);
  colorWipe(PINK, microsec);
  colorWipe(ORANGE, microsec);
  colorWipe(WHITE, microsec);
}


void loop() {

   // test();
   mine();
    toggleLed();
    delay(200);
}


