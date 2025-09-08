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

void RGBLed::setMode(RGBMode m) {
    mode = m;
    lastUpdate = millis();
    hue = 0;
    blinkState = false;

    // reset ค่าเริ่มต้นสำหรับบางโหมด
    if (mode == MODE_SOLID) {
        setColor(CRGB::Blue); // ค่าเริ่ม solid เป็นฟ้า (เปลี่ยนได้)
    }
}

void RGBLed::update() {
    unsigned long now = millis();

    switch (mode) {
    case MODE_SOLID:
        // ใช้สีล่าสุดที่ตั้งด้วย setColor() หรือ setHSV()
        break;

    case MODE_BLINK:
        if (now - lastUpdate > 500) { // กระพริบทุก 0.5s
            blinkState = !blinkState;
            leds[0] = blinkState ? CRGB::Blue : CRGB::Black;
            FastLED.show();
            lastUpdate = now;
        }
        break;

    case MODE_BREATH: {
        uint8_t b = beatsin8(30, 0, 255); // เอฟเฟกต์หายใจ
        leds[0] = CRGB(0, b, 255);        // ฟ้าอ่อน → ฟ้าเข้ม
        FastLED.show();
        break;
    }

    case MODE_RAINBOW:
        if (now - lastUpdate > 30) {
            hue++;
            leds[0] = CHSV(hue, 255, 255);
            FastLED.show();
            lastUpdate = now;
        }
        break;

    case MODE_PARTY:
        if (now - lastUpdate > 80) {
            leds[0] = CHSV(random8(), 255, 255);
            FastLED.show();
            lastUpdate = now;
        }
        break;
    }
}
