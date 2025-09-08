#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>
#include <FastLED.h>

#define RGB_LED_PIN 12     // ขาเชื่อมต่อ WS2812B
#define RGB_NUM_LEDS 1     // จำนวนหลอด

// ✅ โหมดไฟ RGB
enum RGBMode {
    MODE_SOLID = 0,   // สีคงที่
    MODE_BLINK,       // กระพริบ
    MODE_BREATH,      // หายใจ
    MODE_RAINBOW,     // ไล่สี彩虹
    MODE_PARTY        // เปลี่ยนสีสุ่มมันๆ
};

class RGBLed {
public:
    void begin(uint8_t brightness = 100);
    void setColor(CRGB color);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setHSV(uint8_t hue, uint8_t sat = 255, uint8_t val = 255);
    void off();

    void setMode(RGBMode m);
    void update();

private:
    CRGB leds[RGB_NUM_LEDS];
    RGBMode mode = MODE_SOLID;
    unsigned long lastUpdate = 0;
    uint8_t hue = 0;
    bool blinkState = false;
};

#endif
