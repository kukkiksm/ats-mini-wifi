#ifndef IRREMOTE_H
#define IRREMOTE_H

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// struct สำหรับ map ปุ่ม IR → action
struct IRMap {
    uint32_t code;
    int action;
};

class IRRemote {
public:
    IRRemote(int pin);
    void begin();
    bool handle();
    bool wasRemoteClicked();

    // ✅ ต้องประกาศตรงนี้ ไม่งั้น .cpp ใช้ไม่ได้
    void processCode(uint32_t c);

private:
    IRrecv irrecv;
    decode_results results;
    bool remoteClicked;
};

#endif
