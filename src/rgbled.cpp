#include "rgbled.h"

void RGBLed::begin(uint8_t brightness) {
    FastLED.addLeds<WS2812B, RGB_LED_PIN, GRB>(leds, RGB_NUM_LEDS);
    FastLED.setBrightness(brightness);
    off();
}

void RGBLed::setColor(CRGB color) {
    leds[0] = color;
    FastLED.show();
}

void RGBLed::setColor(uint8_t r, uint8_t g, uint8_t b) {
    leds[0] = CRGB(r, g, b);
    FastLED.show();
}

void RGBLed::off() {
    leds[0] = CRGB::Black;
    FastLED.show();
}

void RGBLed::setHSV(uint8_t hue, uint8_t sat, uint8_t val) {
    CHSV hsv(hue, sat, val);
    CRGB rgbColor;
    hsv2rgb_rainbow(hsv, rgbColor);
    setColor(rgbColor);
}

// 🟢 Party Mode แบบกะพริบรัวๆ
void RGBLed::startPartyMode() {
    partyOn = true;
    lastBlink = millis();
    nextInterval = 80; // กำหนดจังหวะ 80ms = เร็ว มันส์
}

void RGBLed::stopPartyMode() {
    partyOn = false;
    off();
}

void RGBLed::update() {
    if (!partyOn) return;

    unsigned long now = millis();
    if (now - lastBlink >= nextInterval) {
        lastBlink = now;

        // สลับสีรัวๆ แบบสุ่ม
        CHSV hsv(random8(), 255, 255);
        CRGB rgbColor;
        hsv2rgb_rainbow(hsv, rgbColor);
        setColor(rgbColor);
    }
}
