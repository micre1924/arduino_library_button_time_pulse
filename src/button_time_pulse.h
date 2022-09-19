#include "Arduino.h"

void nullCallback();

class button_time_pulse {
public:
    byte buttonPin = -1;
    bool isMicro = false;
    bool pulseIn = false;
    bool pulseOut = false;
    bool triggerIn = false;
    bool triggerOut = false;
    unsigned long pressedTime = 0;
    unsigned long inTimestamp = 0;
    unsigned long outTimestamp = 0;
    unsigned int debounceTime = 0;
    void(*onPressed)();
    void(*onReleased)();

    button_time_pulse(byte buttonPin, unsigned int debounceTime, bool isMicro, void(*onReleased)() = nullCallback, void(*onPressed)() = nullCallback);
    void poll();
};