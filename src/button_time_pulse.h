#include "Arduino.h"

namespace mrc{

    struct buttonArgs{
            //is true for one programm cycle once the button has been pressed
            bool pulseIn = false;
            //is true for one programm cycle once the button has been released
            bool pulseOut = false;
            //is true once the button has been pressed, till button is relaesed
            bool triggerIn = true;
            //is true once the button has been released, till button is pressed
            bool triggerOut = true;
            //is the time the button has been pressed, till it was released
            uint64_t pressedTime = 0;
            //is the raw timestamp when the button has been pressed
            uint64_t inTimestamp = 0; 
            //is the raw timestamp when the button has been released
            uint64_t outTimestamp = 0;
        };

    void nullCallback(buttonArgs);

    class button_time_pulse {
    public:
        buttonArgs data;
        uint8_t buttonPin = -1;
        bool isMicro;
        uint16_t debounceTime = 0;
        void(*onPressed)(buttonArgs);
        void(*onReleased)(buttonArgs);

        // @param buttonPin pinMode is declared in the library
        // @param debounceTime the time to wait to accept new input
        // @param isMicro when true micros() is used as a time basis, millis() otherwise (from Arduino.h)
        // @param onReleased the callback for the release-button-event with buttonArgs
        // @param onPressed the callback for the pressed-button-event with buttonArgs
        button_time_pulse(uint8_t buttonPin, uint16_t debounceTime, bool isMicro, void(*onReleased)(buttonArgs) = nullCallback, void(*onPressed)(buttonArgs) = nullCallback);

        void poll();
    };
}