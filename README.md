# ATS Mini / Pocket Receiver (SI4732 + ESP32-S3) + wifi + irremote + ws2812b rgb led

This project is based on [esp32-si4732/ats-mini](https://github.com/esp32-si4732/ats-mini) and adds new functionality such as WiFi, IR remote control, RGB LED effects, and weather/AQI display.

You can download the .bin file from the release and flash it at 0x0, then connect the circuit according to the diagram below to use it.

![Circuit Diagram](https://raw.githubusercontent.com/kukkiksm/ats-mini-wifi/main/image/schem.png)  
![IR Remote](https://raw.githubusercontent.com/kukkiksm/ats-mini-wifi/main/image/irremote.jpg)

### 📡 IR Remote Functions

The remote control allows full operation of the receiver without touching the encoder knob:

| Button | Function |
|--------|----------|
| **1–9** | Recall **Memory Slots 1–9** |
| **\*** | **Cancel / Back** – exit menu immediately |
| **#** | **RGB LED On/Off Toggle** |
| **0** | Change **RGB effect** |
| **OK** | Confirm / Select |
| **◀ ▶** | Adjust frequency **down / up** |
| **▲ ▼** | Normal mode: **Volume up/down**<br>Menu mode: **Navigate menu items** |

---

## Based on the following sources

- Volos Projects: [TEmbedFMRadio](https://github.com/VolosR/TEmbedFMRadio)  
- PU2CLR, Ricardo: [SI4735](https://github.com/pu2clr/SI4735)  
- Ralph Xavier: [SI4735](https://github.com/ralphxavier/SI4735)  
- Goshante: [ats20_ats_ex](https://github.com/goshante/ats20_ats_ex)  
- G8PTN, Dave: [ATS_MINI](https://github.com/G8PTN/ATS_MINI)  

---

## Releases

Check out the [Releases page](../../releases) for downloadable firmware.

---

## Documentation

The hardware, software, and flashing documentation is available at:  
👉 https://esp32-si4732.github.io/ats-mini/

---

## Discuss

- GitHub Discussions – the best place for feature requests, observations, sharing, etc.  
- TalkRadio Telegram Chat – informal space to chat in Russian and English.  
- **Si4732 Mini Receiver All Bands** – Facebook group (unofficial).  
