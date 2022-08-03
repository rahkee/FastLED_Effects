#include "FastLED.h"
#define NUM_LEDS 37

#define PIN_A 2
CRGB leds_A[NUM_LEDS];

#define PIN_B 3
CRGB leds_B[NUM_LEDS];

// Fire
DEFINE_GRADIENT_PALETTE( Fire_1_gp ) {
    0, 255,  64,  0,
  127, 255, 128,  0,
  255, 255,255,  64};



CRGBPalette16 currentPalette = Fire_1_gp;

/* GLOBAL VARIABLES */
uint8_t paletteIndex;
uint8_t chaosTheory;

void setup()
{
  FastLED.addLeds<WS2812, PIN_A, GRB>(leds_A, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<WS2812, PIN_B, GRB>(leds_B, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(192);
}

void loop() 
{

  chaosTheory = random(1, 10);

  EVERY_N_SECONDS(random(1, 5)) {
    meteorRain(CRGB::Black, ColorFromPalette(currentPalette, paletteIndex, random(92, 192), LINEARBLEND), random(1, 10), random(500, 2500), true, random(10, 40), 2);    
  }

  EVERY_N_SECONDS(random(1, 5)) {
    meteorRain(CRGB::Black, ColorFromPalette(currentPalette, paletteIndex, random(92, 192), LINEARBLEND), random(1, 10), random(500, 2500), true, random(10, 40), 1);    
  }

  paletteIndex += chaosTheory;
} 

uint8_t whichStrand;

void meteorRain(CRGB ColorBackground, CRGB ColorMeteor, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay, int StrandValue) 
{  

  if (StrandValue % 2) {

    // set background color
    fill_solid(leds_A, NUM_LEDS, ColorBackground );
  
    for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
      // fade color to background color for all LEDs
      for(int j=0; j<NUM_LEDS; j++) {
        if( (!meteorRandomDecay) || (random(10)>5) ) {
          leds_A[j] = fadeTowardColor(leds_A[j], ColorBackground, meteorTrailDecay );       
        }
      }
     
      // draw meteor
      for(int j = 0; j < meteorSize; j++) {
        if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
          leds_A[i-j]= ColorMeteor;
        }
      }
     
      FastLED.show();
      delay(SpeedDelay);
    }
  } else {
    // set background color
    fill_solid(leds_B, NUM_LEDS, ColorBackground );
  
    for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
      // fade color to background color for all LEDs
      for(int j=0; j<NUM_LEDS; j++) {
        if( (!meteorRandomDecay) || (random(10)>5) ) {
          leds_B[j] = fadeTowardColor(leds_A[j], ColorBackground, meteorTrailDecay );       
        }
      }
     
      // draw meteor
      for(int j = 0; j < meteorSize; j++) {
        if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
          leds_B[i-j]= ColorMeteor;
        }
      }
     
      FastLED.show();
      delay(SpeedDelay);
    }
  }
}

// Functies from Kriegsman example
CRGB fadeTowardColor( CRGB& cur, const CRGB& target, uint8_t amount)
{
  nblendU8TowardU8( cur.red,   target.red,   amount);
  nblendU8TowardU8( cur.green, target.green, amount);
  nblendU8TowardU8( cur.blue,  target.blue,  amount);
  return cur;
}

// function used by "fadeTowardColor"
void nblendU8TowardU8( uint8_t& cur, const uint8_t target, uint8_t amount)
{
  if( cur == target) return;
  
  if( cur < target ) {
    uint8_t delta = target - cur;
    delta = scale8_video( delta, amount);
    cur += delta;
  } else {
    uint8_t delta = cur - target;
    delta = scale8_video( delta, amount);
    cur -= delta;
  }
}
