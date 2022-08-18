#include <FastLED.h>

#define LED_PIN     13
#define NUM_LEDS    2
#define BRIGHTNESS  192
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.

DEFINE_GRADIENT_PALETTE( fire ) {
    0, 255,  0, 0,
  255, 255, 179, 0,
};

CRGBPalette16 currentPalette = fire;
TBlendType    currentBlending;


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(BRIGHTNESS);
    
    currentPalette = fire;
    currentBlending = LINEARBLEND;
}


void loop()
{    
    static uint8_t startIndex = 0;
    startIndex += random(255); /* motion speed */
    
    fill_solid(leds, NUM_LEDS, ColorFromPalette(currentPalette, startIndex, random8(startIndex + 64, BRIGHTNESS), currentBlending));        
    FastLED.show();
    fadeToBlackBy(leds, NUM_LEDS, 24);
    FastLED.delay(random(96));
}
