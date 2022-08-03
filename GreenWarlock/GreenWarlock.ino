#include "FastLED.h"
#define NUM_LEDS 37

#define PIN_A 2
CRGB leds_A[NUM_LEDS];

#define PIN_B 3
CRGB leds_B[NUM_LEDS];

// Warlock
DEFINE_GRADIENT_PALETTE( WarlockFire ) {
    0, 64,  255,  0,
  255, 192,255,  0};

CRGBPalette16 currentPalette = WarlockFire;

uint8_t paletteIndex;
uint8_t chaosTheory;

void setup() {
  FastLED.addLeds<WS2812, PIN_A, GRB>(leds_A, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<WS2812, PIN_B, GRB>(leds_B, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(192);
}

void loop() {
  chaosTheory = random(1, 25);
  
  fill_solid(leds_A, NUM_LEDS, ColorFromPalette(currentPalette, paletteIndex, random(64, 192), LINEARBLEND) );  
  fill_solid(leds_B, NUM_LEDS, ColorFromPalette(currentPalette, paletteIndex, random(64, 192), LINEARBLEND) );
  
  FastLED.show();
  
  FastLED.delay(chaosTheory * 5);

  fadeToBlackBy(leds_A, NUM_LEDS, chaosTheory * 4);
  fadeToBlackBy(leds_B, NUM_LEDS, chaosTheory * 4);
  
  paletteIndex += chaosTheory;
}
