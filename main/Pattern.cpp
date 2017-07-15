#include <stdint.h>
#include "Pattern.h"

Pattern::Pattern() {
  length = 8;
  swing = 0;
  currentStep = 0;
}

void Pattern::randomize() {
  randomSeed(millis());
  for(uint8_t i = 0; i < length; i++) {
    step[i].setNote(random(32,64));
    step[i].setVelocity(random(0,127));
    step[i].setLength(random(1,64));
  }
}

void Pattern::setLength(uint8_t length_) {
  length = length_;
}

void Pattern::setSwing(uint8_t swing_) {
  swing = swing_;
}

uint8_t Pattern::getLength() {
  return length;
}

uint8_t Pattern::getSwing() {
  return swing;
}

Step* Pattern::getStep(uint8_t stepID_) {
  return &step[stepID_];
}

void Pattern::setStep(uint8_t step_) {
  currentStep = step_;
}

void Pattern::reset() {
  currentStep = 0;
}

void Pattern::stop() {
  for(uint8_t i; i < length; i++) {
    step[i].stop(); //stop playing every note.
  }
}

void Pattern::update(unsigned long currentTime_, float beatLength_) {
  for(uint8_t i = 0; i < length; i++) {
    step[i].update(currentTime_, beatLength_);
  }
}

void Pattern::beatTick(unsigned long currentTime_) {
  currentStep++;
  if(currentStep >= length) {
    currentStep = 0;
  }
  step[currentStep].play(currentTime_);
}
