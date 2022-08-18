#include <FastLED.h>

#define LED_PIN_FRONT     3
#define NUM_LEDS_FRONT   37

#define LED_PIN_SIDES     4
#define NUM_LEDS_SIDES   37

CRGB leds_FRONT[NUM_LEDS_FRONT];
CRGB leds_SIDES[NUM_LEDS_SIDES];

#define BRIGHTNESS  128
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

#define UPDATES_PER_SECOND 100
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



CRGBPalette16 currentPalette = bhw2_grrrrr_gp;
TBlendType    currentBlending = LINEARBLEND;

void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN_FRONT, COLOR_ORDER>(leds_FRONT, NUM_LEDS_FRONT).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, LED_PIN_SIDES, COLOR_ORDER>(leds_SIDES, NUM_LEDS_SIDES).setCorrection( TypicalLEDStrip );
}


void loop()
{    
    static uint8_t startIndex = 0;
    startIndex = startIndex - 1; /* motion speed */
    
    FillLEDsFromPaletteColors(startIndex);
    
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    
    for( int i = 0; i < NUM_LEDS_FRONT; ++i) {
        leds_FRONT[i] = ColorFromPalette(currentPalette, colorIndex, BRIGHTNESS, currentBlending);
        colorIndex++;
    }

    for( int j = 0; j < NUM_LEDS_SIDES; ++j) {
        leds_SIDES[j] = ColorFromPalette(currentPalette, colorIndex, BRIGHTNESS, currentBlending);
        colorIndex++;
    }
}
