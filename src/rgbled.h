#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>
#include <FastLED.h>

#define RGB_LED_PIN 12     // ขาเชื่อมต่อ WS2812B
#define RGB_NUM_LEDS 1     // จำนวนหลอด

class RGBLed {
public:
    void begin(uint8_t brightness = 100);
    void setColor(CRGB color);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setHSV(uint8_t hue, uint8_t sat = 255, uint8_t val = 255);
    void off();

    // ✅ โหมดกะพริบมั่วๆ (non-blocking)
    void startPartyMode();
    void stopPartyMode();
    void update();

private:
    CRGB leds[RGB_NUM_LEDS];
    bool partyOn = false;
    unsigned long lastBlink = 0;
    unsigned long nextInterval = 0;
};

#endif
