#include <Arduino.h>
#include "button_time_pulse.h"

void nullCallback() {};

button_time_pulse::button_time_pulse(byte buttonPin, unsigned int debounceTime, bool isMicro, void(*onReleased)(), void(*onPressed)()){
    this->buttonPin = buttonPin;
    this->debounceTime = debounceTime;
    this->isMicro = isMicro;
    this->onPressed = onPressed;
    this->onReleased = onReleased;
}

void button_time_pulse::poll(){
    unsigned long curTime = isMicro ? micros() : millis();
    pulseIn = false;
    pulseOut = false;
    if(digitalRead(buttonPin)){
        if((outTimestamp + debounceTime) < curTime) triggerOut = false;
        if(!triggerIn){
            triggerIn = true;
            pulseIn = true;
            inTimestamp = curTime;
            onPressed();
        }
    } else {
        if((inTimestamp + debounceTime) < curTime) triggerIn = false;
        if(!triggerOut){
            triggerOut = true;
            pulseOut = true;
            outTimestamp = curTime;
            pressedTime = outTimestamp - inTimestamp;
            onReleased();
        }
    }
}