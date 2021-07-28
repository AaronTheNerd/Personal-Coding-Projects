#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#define LED_PIN   11
#define LED_COUNT 50


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);


void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip.begin();             // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();              // Turn OFF all pixels ASAP
  strip.setBrightness(255);  // Set BRIGHTNESS to max
  Serial.begin(38400);       // Turn on serial
  delay(500);
  char data = waitForByte(); // Wait for python dummy byte
  if (data != 'a') {         // Check that the dummy byte was transmitted correctly
    Serial.write("Fail.");
    exit(0);
  }
  Serial.write("begin");     // Tell python the arduino is ready
  playSequence();            // Play the sequence based on serial input
  delay(5000);
}


void loop() {
  rainbow(50); 
}


void requestBytes(uint8_t bytes) {
  Serial.write(bytes);
}


uint8_t waitForByte() {
  while (Serial.available() <= 0);
  if (Serial.available() > 0)
    return 0xff & Serial.read();
  return 0;
}


uint16_t waitFor2Bytes() {
  uint8_t incoming_byte;
  uint16_t ret = 0;
  for (size_t i = 0; i < 2; ++i) {
    incoming_byte = waitForByte();
    ret |= (0xff & incoming_byte) << ((1 - i) * 8);
  }
  return ret;
}


uint32_t waitFor4Bytes() {
  uint8_t incoming_byte;
  uint32_t ret = 0;
  for (size_t i = 0; i < 4; ++i) {
    incoming_byte = waitForByte();
    ret |= (0xff & incoming_byte) << ((3 - i) * 8);
  }
  return ret;
}


void playSequence() {
  long start;
  bool forever;
  uint32_t frame_count;
  uint16_t hold = 0;
  uint8_t repeats = 0, led_count = 0, index = 0, red = 0, green = 0, blue = 0;
  requestBytes(5);
  repeats = waitForByte();
  frame_count = waitFor4Bytes();
  delay(500);
  forever = repeats == 0;
  for (size_t i = 0; (i < repeats) || forever; ++i) {
    for (size_t j = 0; j < frame_count; ++j) { // For each frame in animation
      start = millis();
      requestBytes(3);
      strip.clear();                           // clear strip
      hold = waitFor2Bytes();                  // grab 2 bytes for hold
      led_count = waitForByte();               // grab 1 byte for led_count 
      requestBytes(led_count << 2);
      for (size_t k = 0; k < led_count; ++k) { // for each LED index, color pair
        index = waitForByte();                 // grab and set colors at index
        red = waitForByte();
        green = waitForByte();
        blue = waitForByte();
        strip.setPixelColor(index, strip.Color(red, green, blue));
      }
      strip.show();                            // show color strip
      delay(hold - (millis() - start));        // hold colors for set time
    }
  }
  strip.clear();
  strip.show();
}


// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}
