#include "Arduino.h"

void nullCallback();
void nullCallback(unsigned long);

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
    void(*onReleased)(unsigned long);

    // @param buttonPin pinMode is declared in the library
    // @param debounceTime the time to wait to accept new input
    // @param isMicro when true micros() is used as a time basis, millis() otherwise (from Arduino.h)
    // @param onPressed the callback for the pressed-button-event without parameters
    button_time_pulse(byte buttonPin, unsigned int debounceTime, bool isMicro, void(*onPressed)() = nullCallback);

    // @param buttonPin pinMode is declared in the library
    // @param debounceTime the time to wait to accept new input
    // @param isMicro when true micros() is used as a time basis, millis() otherwise (from Arduino.h)
    // @param onRelease the callback for the release-button-event with pressed-time parameter
    button_time_pulse(byte buttonPin, unsigned int debounceTime, bool isMicro, void(*onReleased)(unsigned long) = nullCallback);

    // @param buttonPin pinMode is declared in the library
    // @param debounceTime the time to wait to accept new input
    // @param isMicro when true micros() is used as a time basis, millis() otherwise (from Arduino.h)
    // @param onRelease the callback for the release-button-event with pressed-time parameter
    // @param onPressed the callback for the pressed-button-event without parameters
    button_time_pulse(byte buttonPin, unsigned int debounceTime, bool isMicro, void(*onReleased)(unsigned long) = nullCallback, void(*onPressed)() = nullCallback);

    void poll();
};