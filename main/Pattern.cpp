#include <stdint.h>
#include "Pattern.h"

Pattern::Pattern() {
  size = 8; //in beats, not sixteenths.
  swing = 0;
  currentSixteenth = 0;
}

void Pattern::randomize(uint16_t seed_) {
  randomSeed(seed_);
  for(uint8_t i = 0; i < size; i++) {
    step[i].setPitch(random(16,64));
    step[i].setVelocity(random(0,127));
    step[i].setLength(random(1,16));
  }
}

void Pattern::setSize(uint8_t size_) {
  size = size_;
}

void Pattern::setSwing(uint8_t swing_) {
  swing = swing_;
}

uint8_t Pattern::getSize() {
  return size;
}

uint8_t Pattern::getSwing() {
  return swing;
}

Step* Pattern::getStep(uint8_t stepID_) {
  return &step[stepID_];
}

void Pattern::setStep(uint8_t step_) {
  if(step_ < size) {
    currentSixteenth = step_*16;
  }else{
    //throw error
  }
}

void Pattern::reset() {
  currentSixteenth = 0;
}

void Pattern::stop(Midi* midiManager_) {
  for(uint8_t i; i < size; i++) {
    step[i].stop(midiManager_); //stop playing every note.
  }
}

void Pattern::sixteenthTick(Midi* midiManager_) {
  if(currentSixteenth % 16 == 0){//if exactly one notelength has passed.
    step[(int)floor(currentSixteenth / 16)].play(midiManager_);//play the note in this spot
  }

  currentSixteenth++;
  if(currentSixteenth >= size*16) {
    currentSixteenth = 0;
  }
}
