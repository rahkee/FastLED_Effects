#include <FastLED.h>

#define LED_PIN_A     2
#define LED_PIN_B     3
#define NUM_LEDS_AB    37
CRGB leds_A[NUM_LEDS_AB];
CRGB leds_B[NUM_LEDS_AB];

#define LED_PIN_C     5
#define NUM_LEDS_C    6
CRGB leds_C[NUM_LEDS_C];

#define BRIGHTNESS  128
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

// Gradient palette "bhw1_minty_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_minty.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( mint ) {
    0,  23,195,130,
   99, 121,255,125,
  121, 182,255,184,
  127, 255,255,255,
  134, 182,255,184,
  153, 121,255,125,
  255,  23,195,130};

// Gradient palette "bhw1_13_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_13.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE( marshmallow ) {
    0, 255,255, 45,
  255, 157, 57,197};


// Gradient palette "bhw2_07_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_07.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( revlon ) {
    0,  92,  1,  1,
   26, 153, 20,  5,
   79, 232, 72, 12,
  127, 220,231, 89,
  173, 232, 72, 12,
  255,  92,  1,  1};

  // Gradient palette "bhw2_sherbet2_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_sherbet2.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( sherbet ) {
    0, 217,  1,  1,
   35, 249, 43, 19,
   71, 247,125,172,
  109, 206,  2, 32,
  163, 210, 23,  9,
  211, 255,255,255,
  232, 252,199, 88,
  255, 206,115, 52};


CRGBPalette16 currentPalette;
CRGBPalette16 fusionPalette = sherbet;
TBlendType    currentBlending;

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN_A, COLOR_ORDER>(leds_A, NUM_LEDS_AB).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, LED_PIN_B, COLOR_ORDER>(leds_B, NUM_LEDS_AB).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, LED_PIN_C, COLOR_ORDER>(leds_C, NUM_LEDS_C).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

    currentPalette = sherbet;
    currentBlending = LINEARBLEND;
}


void loop()
{  
  
//    ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex - 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);

    fill_solid(leds_C, NUM_LEDS_C, ColorFromPalette(fusionPalette, startIndex, random8(32, startIndex * 32), currentBlending));
        
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    
    for( int i = 0; i < NUM_LEDS_AB; ++i) {
        leds_A[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
        leds_B[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
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

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  10)  { currentPalette = purple_pink_blue;         currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { currentPalette = sherbet;   currentBlending = LINEARBLEND;  }
        if( secondHand == 30)  { currentPalette = mint;   currentBlending = LINEARBLEND;  }
        if( secondHand == 40)  { currentPalette = marshmallow;   currentBlending = LINEARBLEND;  }
    }
}



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
