#include <FastLED.h>

#define LED_PIN_FRONT     3
#define NUM_LEDS_FRONT   37

#define LED_PIN_SIDES     4
#define NUM_LEDS_SIDES   21

CRGB leds_FRONT[NUM_LEDS_FRONT];
CRGB leds_SIDES[NUM_LEDS_SIDES];

#define BRIGHTNESS_FRONT  4
#define BRIGHTNESS_SIDES  16
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

DEFINE_GRADIENT_PALETTE( lucky_charms ) {
    0, 0, 0, 0,
   105, 255, 71,209,
   110, 162, 118,216,
   115, 151, 212,245,
   120, 71, 186, 225,
   125, 161, 219, 182,
   130, 250, 251, 139,
   135, 204, 187, 178,
   140, 157, 122, 216,
   145, 225, 71, 209,
   255, 0, 0, 0
};

DEFINE_GRADIENT_PALETTE( fruit_punch ) {
    0, 227, 101,  3,
  117, 194, 18, 19,
  255,  92,  8, 192};

DEFINE_GRADIENT_PALETTE( green_yellow ) {
    0, 0, 0,  0,
    126, 0, 0, 0,
  127,  128,  255, 0,
  128, 164, 255, 0,
  129,  128,  255, 0,
  130, 0, 0, 0,
  255, 0, 0, 0,
  };

CRGBPalette16 currentPalette = green_yellow;
//CRGBPalette16 currentPalette = RainbowColors_p;
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
    
    FastLED.delay(24);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{

  for( int i = 0; i < NUM_LEDS_FRONT; ++i) {
        leds_FRONT[i] = ColorFromPalette(currentPalette, colorIndex, BRIGHTNESS_FRONT, currentBlending);
        colorIndex++;
    }
    
  for( int j = 0; j < NUM_LEDS_SIDES; ++j) {
        leds_SIDES[j] = ColorFromPalette(currentPalette, colorIndex, BRIGHTNESS_SIDES, currentBlending);
        colorIndex++;
    }    
}
