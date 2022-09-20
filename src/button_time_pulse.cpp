#include <Arduino.h>
#include "button_time_pulse.h"

namespace mrc{

    void nullCallback(buttonArgs) {};

    button_time_pulse::button_time_pulse(uint8_t buttonPin, uint16_t debounceTime, bool isMicro, void(*onReleased)(buttonArgs), void(*onPressed)(buttonArgs)){
        pinMode(buttonPin, INPUT);
        this->buttonPin = buttonPin;
        this->debounceTime = debounceTime;
        this->isMicro = isMicro;
        this->onPressed = onPressed;
        this->onReleased = onReleased;
    }


    void button_time_pulse::poll(){
        unsigned long curTime = isMicro ? micros() : millis();
        data.pulseIn = false;
        data.pulseOut = false;
        if(digitalRead(buttonPin)){
            if((data.outTimestamp + debounceTime) < curTime) data.triggerOut = false;
            if(!data.triggerIn){
                data.triggerIn = true;
                data.pulseIn = true;
                data.inTimestamp = curTime;
                onPressed(data);
            }
        } else {
            if((data.inTimestamp + debounceTime) < curTime) data.triggerIn = false;
            if(!data.triggerOut){
                data.triggerOut = true;
                data.pulseOut = true;
                data.outTimestamp = curTime;
                data.pressedTime = data.outTimestamp - data.inTimestamp;
                onReleased(data);
            }
        }
    }
}