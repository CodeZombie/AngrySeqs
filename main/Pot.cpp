#include "Pot.h"

Pot::Pot(uint8_t pin_, uint16_t potResolution_, void (*changeMethod_)(uint16_t)) {
  pin = pin_;
  potResolution = potResolution_;
  changeMethod = changeMethod_;
}

void Pot::init() {
  value = analogRead(pin);
  for(int i = 0; i < 16; i++) {
    value = round((((smoothfactor * analogRead(pin)) + (smoothfactor * value)) / 1023.f) * potResolution);
  }
}

void Pot::update() {
  uint16_t oldValue = value;
  value = round((((smoothfactor * analogRead(pin)) + (smoothfactor * oldValue)) / 1023.f) * potResolution);
  if(oldValue != value) {
    changeMethod(value);
  }
}
  
uint16_t Pot::getValue() {
  return value;
}
