#include "FastLED.h"
#define NUM_LEDS 26

#define PIN_A 13
CRGB leds_A[NUM_LEDS];

// Warlock
DEFINE_GRADIENT_PALETTE( Warlock ) {
    0, 0,  172,  0,
  255, 148,255,  0};
  
// Fire
DEFINE_GRADIENT_PALETTE( Fire ) {
    0, 255,  64,  0,
  127, 255, 128,  0,
  255, 255,255,  64};

// Gradient palette "bhw2_grrrrr_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_grrrrr.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_grrrrr_gp ) {
    0, 184, 15,155,
   35,  78, 46,168,
   84,  65,169,230,
  130,   9,127,186,
  163,  77,182,109,
  191, 242,246, 55,
  216, 142,128,103,
  255,  72, 50,168};



CRGBPalette16 currentPalette = Fire;

/* GLOBAL VARIABLES */
uint8_t paletteIndex;
uint8_t chaosTheory;

void setup()
{
  FastLED.addLeds<WS2812, PIN_A, GRB>(leds_A, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(92);
}

void loop() 
{
  chaosTheory = random8(1, 10);
                                  // color                                                               // meteor size // meteor decay  // meteor random decay
  meteorRain(CRGB::Black, ColorFromPalette(currentPalette, paletteIndex, random8(92, 192), LINEARBLEND), random8(1, 3), random8(750, 1500), true, random8(5, 26));  
  // test: to make sure 26 (largest delay is no more than numLeds?
  // or test: to see if last number should be half of numLeds, NUM_LEDS / 2?
    

  fadeToBlackBy(leds_A, NUM_LEDS, NUM_LEDS);
  FastLED.delay(chaosTheory * 100);

  paletteIndex += chaosTheory;
} 

void meteorRain(CRGB ColorBackground, CRGB ColorMeteor, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) 
{  
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
