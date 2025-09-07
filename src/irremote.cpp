#include "irremote.h"
#include "Globals.h"
#include "Menu.h"
#include "Draw.h"
#include "Storage.h"
#include "rgbled.h"

// external references from main code
extern SI4735_fixed rx;
extern uint8_t volume;
extern uint16_t currentFrequency;
extern int16_t currentBFO;
extern uint16_t currentCmd;
extern int encoderCount;
extern bool updateFrequency(int newFreq, bool wrap);
extern void recallMemorySlot(uint8_t idx);
extern void doBand(int dir);
extern bool rgbOn;
extern RGBLed rgb;

// map codes
static IRMap irMap[] = {
    {16718055, -1}, // Vol+
    {16730805, -2}, // Vol-
    {16716015, -3}, // Freq--
    {16734885, -4}, // Freq++
    {16753245, 0},  // mem0
    {16736925, 1},  // mem1
    {16769565, 2},  // mem2
    {16720605, 3},  // mem3
    {16712445, 4},  // mem4
    {16761405, 5},  // mem5
    {16769055, 6},  // mem6
    {16754775, 7},  // mem7
    {16748655, 8},  // mem8
    {16750695, 9},  // mem9
    {16738455, -5}, // *
    {16756815, -6}, // #
    {16726215, -7}  // OK
};

IRRemote::IRRemote(int pin) : irrecv(pin), remoteClicked(false) {}

void IRRemote::begin()
{
    irrecv.enableIRIn();
}

bool IRRemote::handle()
{
    if (irrecv.decode(&results))
    {
        processCode(results.value);
        irrecv.resume();
        return true;
    }
    return false;
}

bool IRRemote::wasRemoteClicked()
{
    if (remoteClicked)
    {
        remoteClicked = false;
        return true;
    }
    return false;
}

void IRRemote::processCode(uint32_t c)
{
    for (auto &m : irMap)
    {
        if (m.code == c)
        {
            if (m.action >= 0)
            {
                recallMemorySlot(m.action);
            }
            else
            {
                switch (m.action)
                {
                case -1: // Vol+
                    if (isMenuMode(currentCmd) || isSettingsMode(currentCmd) || currentCmd == CMD_MENU)
                    {
                        encoderCount = -1;
                    }
                    else
                    {
                        if (volume < 63)
                            volume++;
                        rx.setVolume(volume);
                    }
                    break;
                case -2: // Vol-
                    if (isMenuMode(currentCmd) || isSettingsMode(currentCmd) || currentCmd == CMD_MENU)
                    {
                        encoderCount = +1;
                    }
                    else
                    {
                        if (volume > 0)
                            volume--;
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
                case -5: // *
                    Serial.println("Pressed * (Cancel)");
                    // ถ้าอยู่ในเมนูหรือ modal command → ออกได้เลย
                    if (currentCmd != CMD_NONE)
                    {
                        currentCmd = CMD_NONE;
                        drawScreen(nullptr, nullptr);
                    }
                    break;
                case -6: // #
#if ENABLE_RGBLED
                    Serial.println("Pressed # (toggle RGB)");
                    rgbOn = !rgbOn;
                    if (rgbOn)
                    {
                        CHSV hsv(random(256), 255, 255);
                        rgb.setHSV(hsv.h, hsv.s, hsv.v);
                    }
                    else
                    {
                        rgb.off();
                    }
#else
                    Serial.println("Pressed # (Band +)");
                    doBand(+1);
                    drawScreen(nullptr, nullptr);
#endif
                    break;
                case -7: // OK
                    Serial.println("Pressed OK");
                    remoteClicked = true;
                    break;
                }
            }
        }
    }
}
