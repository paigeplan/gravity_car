#include <FastLED.h>


// accelerometer libs
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

//DEFINE_GRADIENT_PALETTE( black_to_red_to_white_p ) {
//  0,    0,   0,   0,  /* at index 0,   black(0,0,0) */
//  192, 0,   0,   255,  /* at index 192, red(255,0,0) */
//  255, 0, 255, 0   /* at index 255, white(255,255,255) */
//};

DEFINE_GRADIENT_PALETTE( black_to_red_to_white_p ) {
  0,    230,   62,   98,  /* at index 0,   black(0,0,0) */
  128, 20,   0,   170,  /* at index 192, red(255,0,0) */
  255, 0, 177, 20   /* at index 255, white(255,255,255) */
};

CRGBPalette16 pal = black_to_red_to_white_p;

#define LED_PIN     5
#define NUM_LEDS    8
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];



void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens


  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }

  // lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

  Serial.print("Range = "); Serial.print(2 << lis.getRange());
  Serial.println("G");

  // lis.setDataRate(LIS3DH_DATARATE_50_HZ);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

}

void loop() {
lis.read();
Serial.print(lis.y);
  /* Or....get a new sensor event, normalized */
//  sensors_event_t event;
//  lis.getEvent(&event);


 // float y_accel = event.acceleration.y;
  /* Display the results (acceleration is measured in m/s^2) */
//  Serial.print("Y: "); Serial.print(y_accel);

  Serial.print(" m/s^2 \t");


  int led_color_index = constrain(map(lis.y, -15000, 15000, 0, 255), 0, 255);
  Serial.println(led_color_index);
  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( pal, led_color_index, BRIGHTNESS, NOBLEND);
  }
  FastLED.show();
  delay(10);
}
