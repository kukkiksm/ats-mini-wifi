#include "irremote.h"
#include "Globals.h"
#include "Menu.h"
#include "Draw.h"
#include "Storage.h"
#include "rgbled.h"

// external references
extern SI4735_fixed rx;
extern uint8_t volume;
extern uint16_t currentFrequency;
extern int16_t currentBFO;
extern uint16_t currentCmd;
extern int encoderCount;
extern bool updateFrequency(int newFreq, bool wrap);
extern void recallMemorySlot(uint8_t idx);
extern void doBand(int dir);
extern RGBLed rgb;

// from Globals.cpp
extern bool rgbOn;
extern int rgbeffect;

static IRMap irMap[] = {
    {16718055, -1}, // Vol+
    {16730805, -2}, // Vol-
    {16716015, -3}, // Freq--
    {16734885, -4}, // Freq++
    {12345678, 0},  // mem0 (dummy code)
    {16753245, 1},  // mem1
    {16736925, 2},  // mem2
    {16769565, 3},  // mem3
    {16720605, 4},  // mem4
    {16712445, 5},  // mem5
    {16761405, 6},  // mem6
    {16769055, 7},  // mem7
    {16754775, 8},  // mem8
    {16748655, 9},  // mem9
    {16738455, -5}, // *
    {16756815, -6}, // #
    {16726215, -7}, // OK
    {16750695, -8}, // ปุ่ม 0 จริง → RGB effect
};

IRRemote::IRRemote(int pin) : irrecv(pin), remoteClicked(false) {}

void IRRemote::begin() {
    irrecv.enableIRIn();
}

bool IRRemote::handle() {
    if (irrecv.decode(&results)) {
        // 👉 debug: แสดงค่าที่รีโมทส่งมา
        Serial.printf("IR raw code: %u (0x%X)\n", results.value, results.value);

        processCode(results.value);
        irrecv.resume();
        return true;
    }
    return false;
}

bool IRRemote::wasRemoteClicked() {
    if (remoteClicked) {
        remoteClicked = false;
        return true;
    }
    return false;
}

// โค้ดจริงที่จัดการปุ่ม
void IRRemote::processCode(uint32_t c) {
    for (auto &m : irMap) {
        if (m.code == c) {
            if (m.action >= 0) {
                // ✅ Memory slot 1–9
                recallMemorySlot(m.action);
            } else {
                switch (m.action) {
                case -1: // Vol+
                    if (isMenuMode(currentCmd) || isSettingsMode(currentCmd) || currentCmd == CMD_MENU) {
                        encoderCount = -1;
                    } else {
                        if (volume < 63) volume++;
                        rx.setVolume(volume);
                    }
                    break;

                case -2: // Vol-
                    if (isMenuMode(currentCmd) || isSettingsMode(currentCmd) || currentCmd == CMD_MENU) {
                        encoderCount = +1;
                    } else {
                        if (volume > 0) volume--;
                        rx.setVolume(volume);
                    }
                    break;

                case -3:
                    updateFrequency(currentFrequency - getCurrentStep()->step, true);
                    drawScreen(nullptr, nullptr);
                    break;

                case -4:
                    updateFrequency(currentFrequency + getCurrentStep()->step, true);
                    drawScreen(nullptr, nullptr);
                    break;

                case -5: // * Cancel
                    Serial.println("Pressed * (Cancel)");
                    if (currentCmd != CMD_NONE) {
                        currentCmd = CMD_NONE;
                        drawScreen(nullptr, nullptr);
                    }
                    break;

                case -6: // # Toggle RGB
#if ENABLE_RGBLED
                    rgbOn = !rgbOn;
                    if (rgbOn) {
                        rgb.setMode((RGBMode)rgbeffect);
                        Serial.println("RGB ON");
                    } else {
                        rgb.off();
                        Serial.println("RGB OFF");
                    }
#else
                    doBand(+1);
                    drawScreen(nullptr, nullptr);
#endif
                    break;

                case -7: // OK
                    Serial.println("Pressed OK");
                    remoteClicked = true;
                    break;

                case -8: // ปุ่ม 0 → RGB effect
#if ENABLE_RGBLED
                    if (rgbOn) {
                        rgbeffect++;
                        if (rgbeffect > 5) rgbeffect = 0;
                        rgb.setMode((RGBMode)rgbeffect);
                        Serial.printf("RGB effect changed -> %d\n", rgbeffect);
                    } else {
                        Serial.println("RGB is OFF, enable first with #");
                    }
#endif
                    break;
                }
            }
        }
    }
}
