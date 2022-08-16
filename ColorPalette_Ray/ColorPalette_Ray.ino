#include <FastLED.h>

#define LED_PIN_REAR     2
#define NUM_LEDS_REAR   15

#define LED_PIN_UNDER    3
#define NUM_LEDS_UNDER  21

#define LED_PIN_SIDES    4
#define NUM_LEDS_SIDES  30

CRGB leds_REAR[NUM_LEDS_REAR];
CRGB leds_UNDER[NUM_LEDS_UNDER];
CRGB leds_SIDES[NUM_LEDS_SIDES];

#define BRIGHTNESS  32
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

#define UPDATES_PER_SECOND 100

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


// Gradient palette "bhw1_06_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_06.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( purple_pink_blue ) {
    0, 184,  1,128,
  160,   1,193,182,
  219, 153,227,190,
  255, 255,255,255
};

DEFINE_GRADIENT_PALETTE( fire ) {
    0, 255,  0, 0,
  255, 255, 179, 0,
};

// Gradient palette "bhw2_10_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_10.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_10_gp ) {
    0,   0, 12,  0,
   61, 153,239,112,
  127,   0, 12,  0,
  165, 106,239,  2,
  196, 167,229, 71,
  229, 106,239,  2,
  255,   0, 12,  0};


CRGBPalette16 currentPalette = bhw2_10_gp;
CRGBPalette16 fusionPalette = fire;
TBlendType    currentBlending = LINEARBLEND;

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN_REAR, COLOR_ORDER>(leds_REAR, NUM_LEDS_REAR).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, LED_PIN_UNDER, COLOR_ORDER>(leds_UNDER, NUM_LEDS_UNDER).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, LED_PIN_SIDES, COLOR_ORDER>(leds_SIDES, NUM_LEDS_SIDES).setCorrection( TypicalLEDStrip );
}


void loop()
{    
    static uint8_t startIndex = 0;
    startIndex = startIndex - 1; /* motion speed */
    
    FillLEDsFromPaletteColors(startIndex);

    // DEFAULT: meteorRain(CRGB(0x10,0x00,0x00), CRGB(0xff,0xff,0x00),10 ,64 ,true, 30);
    // meteorRain(CRGB::Black, ColorFromPalette(currentPalette, startIndex, random(92, 192), LINEARBLEND), random(1, 10), random(500, 2500), true, random(10, 40));    

    fill_solid(leds_REAR, NUM_LEDS_REAR, ColorFromPalette(fusionPalette, random8(128), random8(128), currentBlending));        
    FastLED.show();
    fadeToBlackBy(leds_REAR, NUM_LEDS_REAR, 24);
    
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    
    for( int i = 0; i < NUM_LEDS_SIDES; ++i) {
        leds_SIDES[i] = ColorFromPalette(currentPalette, colorIndex, BRIGHTNESS, currentBlending);
        colorIndex++;
    }

    for( int j = 0; j < NUM_LEDS_UNDER; ++j) {
        leds_UNDER[j] = ColorFromPalette(currentPalette, colorIndex, BRIGHTNESS, currentBlending);
        colorIndex++;
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.

void meteorRain(CRGB ColorBackground, CRGB ColorMeteor, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) 
{  
  // set background color
  fill_solid(leds_SIDES, NUM_LEDS_SIDES, ColorBackground );

  for(int i = 0; i < NUM_LEDS_SIDES + NUM_LEDS_SIDES; i++) {
    // fade color to background color for all LEDs
    for(int j = 0; j < NUM_LEDS_SIDES; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        leds_SIDES[j] = fadeTowardColor(leds_SIDES[j], ColorBackground, meteorTrailDecay);       
      }
    }
   
    // draw meteor
    for(int k = 0; k < meteorSize; k++) {
      if(( i - k < NUM_LEDS_SIDES) && (i - k >= 0)) {
        leds_SIDES[i - k]= ColorMeteor;
      }
    }
   
//    FastLED.delay(SpeedDelay);
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
