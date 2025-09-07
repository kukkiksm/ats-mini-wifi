#ifndef IRREMOTE_H
#define IRREMOTE_H

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

struct IRMap {
  uint32_t code;
  int action; // action <0 = พิเศษ, >=0 = memory index
};

class IRRemote {
public:
  IRRemote(int pin);
  void begin();
  bool handle();
  bool wasRemoteClicked();

private:
  IRrecv irrecv;
  decode_results results;
  bool remoteClicked;

  void processCode(uint32_t code);
};

#endif
