#ifndef HEARTSEFFECT_H
#define HEARTSEFFECT_H

#include "Effect.h"
#include "./../Util/ColorConverters.h"

// Struct to define the hearts and a list of hearts.
typedef struct Heart {
    int firstLed;
    int numLeds;
} Heart_t;

// The hearts.
const int numHearts = 14;
const Heart hearts[numHearts] = {
    Heart { 0, 5 },
    Heart { 5, 5 },
    Heart { 10, 5 },
    Heart { 15, 5 },
    Heart { 20, 5 },
    Heart { 25, 7 },
    Heart { 32, 5 },
    Heart { 37, 5 },
    Heart { 42, 5 },
    Heart { 47, 5 },
    Heart { 52, 5 },
    Heart { 57, 7 },
    Heart { 64, 5 },
    Heart { 69, 5 }
};

// Colors for the hearts.
const int numColors = 7;
const uint32_t Colors[numColors] = {
    0xff0000, // full red
    0xff0000, // full red
    0xff0000, // full red
    // 0xff66f7, // pinkish
    // 0xa600ff, // purple
    0xfffb00, // yellow
    0xfffb00, // yellow
    0xfffb00, // yellow
    0xffffff  // white
};

class HeartEffect : Effect {

    public:

        /**
         * @brief Construct a new Heart Effect object
         * 
         * @param animationFrames Number of frames to go from black to full 
         * color and back to black. Higher number = slower animation.
         * @param animationWindow Number of frames that define the window in 
         * which the animation should occur. Higher number = less frequent
         * animation.
         * @param firstLed The index of the first LED in the heart.
         */
        HeartEffect(
            int animationFrames, 
            int animationWindow, 
            int firstLed
        ) : 
            _animationWindow { animationWindow },
            _animationFrames { animationFrames },
            _firstLed { firstLed } {
                _firstFrame = rand();
            }

        bool effectAction(
            uint32_t ledX, 
            uint32_t ledY, 
            uint32_t ledZ, 
            uint32_t ledIndex, 
            uint32_t frame,
            uint32_t currentColor, 
            uint32_t previousColor,
            uint32_t& newColor
        ) {
            
            // Get the frame for the animation.
            uint32_t f = (frame + _firstFrame) % _animationWindow;

            // Calculate animation color step. If this is the last frame 
            // of the animation...
            if(heartAnimationStep(f, _animationFrames, _color, newColor)) {

                // And this is the first LED in the heart...
                if (ledIndex == _firstLed) {

                    // Set a new random first animation frame.
                    _firstFrame = rand();

                    //Pick a new random color.
                    int x = rand() % numColors;
                    _color = Colors[x];
                }
            }
            return true;
        };

    private:

        int _animationWindow;
        int _animationFrames;
        int _firstFrame;
        int _firstLed;
        uint32_t _color;

        static bool heartAnimationStep(
            int animationFrame,
            int animationLength,
            uint32_t heartColor,
            uint32_t& newColor
        ) {
            // Working var.
            uint32_t x;

            // Fading up...
            if (animationFrame < animationLength / 2) {
                x = animationFrame;
            
            // Fading down...
            } else if (animationFrame < animationLength) {
                 x = animationLength - animationFrame;

            // No animation.
            } else if (animationFrame == animationLength) {
                newColor = 0;

                // Return true to indicate last frame.
                return true;
            } else {
                newColor = 0;

                // Otherwise, return false.
                return false;
            }

            // Get RGB of current heart color.
            uint8_t r, g, b;
            uint32_t rR, gG, bB;
            uint32toRgb(heartColor, r, g, b);

            // Interpolate to current animation frame.
            rR = x * r;
            gG = x * g;
            bB = x * b;
            rR /= animationLength;
            gG /= animationLength;
            bB /= animationLength;
            r = rR;
            g = gG;
            b = bB;

            // Set new color.
            newColor = rgbToUint32(r, g, b);
            return false;
        }
};

#endif
