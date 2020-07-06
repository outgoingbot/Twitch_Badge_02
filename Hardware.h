 /*
 HARDWARE
 WS2812 Pin =     5 - D1 - GPIO5
 MAX7219 Data =   HMOSI - D7 - GPIO13
 MAX7219 Clock =  HSCLK - D5 - GPIO14
 MAX7219 Load =   15 - D8 - GPIO15
 Button 1  =      4 - D2 - GPIO4
 Button 2  =      0 - D3 - GPIO0
 */
//---------------------PINS----------------------
#define BTN1_PIN  4 // D2 - GPIO4
#define BTN2_PIN  0 // D3 - GPIO0
#define LOAD_PIN  15 // D8 - GPIO15
#define LED_PIN   5 // D1 - GPIO5

//---------------------RGB LEDS----------------------
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>
#define NUMPIXELS  12
#define LED_TYPE  WS2812B
#define BRIGHTNESS  255 
#define COLOR_ORDER GRB
CRGB leds[NUMPIXELS];

//---------------------LED MATRIX----------------------
#include "CharTable.h"
#include <LEDMatrixDriver.hpp>
#define numCols 16
#define numRows 16
#define FONT_3X5 0
#define FONT_8X8 1

bool buffTemp[numCols][numRows]; //screen buffer-ish //screen buffer-ish (bool uses same amount of ram as byte)! this is inefficient this should be  byte[32]
//maps library to hardware// depends on board
//byte X1[16] = {7,6,5,4,3,2,1,0,7,6,5,4,3,2,1,0};
//byte Y2[16] = {0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7};
//byte Y3[16] = {0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7};
byte X1[16] = {7,6,5,4,3,2,1,0,7,6,5,4,3,2,1,0};
byte Y2[16] = {8,15,14,13,12,11,10,9,24,31,30,29,28,27,26,25};
byte Y3[16] = {0,7,6,5,4,3,2,1, 16,23,22,21,20,19,18,17};
byte myOffset = 8; //  "center" of screen. width/2 = 16/2 = 8
const uint8_t LEDMATRIX_CS_PIN = LOAD_PIN;
const int LEDMATRIX_SEGMENTS = 4;
const int LEDMATRIX_WIDTH    = LEDMATRIX_SEGMENTS * 8;
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);


void setupHardware(){
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(BTN1_PIN,INPUT);
	pinMode(BTN2_PIN,INPUT);
	
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUMPIXELS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(BRIGHTNESS);
	FastLED.clear(true);
  		
	lmd.setEnabled(true);
	lmd.setIntensity(2);   // 0 = low, 10 = high	
}
