#include <Arduino.h>
#include "button_time_pulse.h"

button_time_pulse::button_time_pulse(byte buttonPin, unsigned int debounceTime, bool isMicro, void(*onReleased)() = nullCallback, void(*onPressed)() = nullCallback){
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
        if(!triggerIn){
            triggerIn = true;
            pulseIn = true;
            lastTimestamp = curTime;
            triggerOut = false;
            onPressed();
        }
    } else {
        if((lastTimestamp + debounceTime) > curTime) triggerIn = false;
        if(!triggerOut){
            triggerOut = true;
            pulseOut = true;
            pressedTime = curTime - lastTimestamp;
            onReleased();
        }
    }
}

void button_time_pulse::nullCallback(){};