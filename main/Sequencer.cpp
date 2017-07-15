#include "Sequencer.h"

Sequencer::Sequencer(uint16_t tempo_) {
  tempo = tempo_;
  beatLength = (60.f/tempo)*1000.f;
  outputClockAccumulator = 0;
  sixteenthAccumulator = 0;
  sixteenthCount = 0;
  for(uint8_t i = 0; i < 8; i++) {
    activePattern[i] = -1;
  }
}

void Sequencer::setTempo(uint16_t tempo_) {
  tempo = tempo_;
  beatLength = (60.f/tempo)*1000.f;
}

void Sequencer::activatePattern(uint8_t patternID_) {
  pattern[patternID_].setStep((int)floor(sixteenthCount/16) % pattern[patternID_].getSize()); //Set the newly activated pattern's step to the step it'd be at if it had started playing right when the system started ticking.
  for(uint8_t i = 0; i < 8; i++) {
    if(activePattern[i] == -1) {
      activePattern[i] = patternID_;
      return;
    }
  }
}

void Sequencer::deactivatePattern(uint8_t patternID_) {
  pattern[patternID_].stop(&midiManager);
  for(uint8_t i = 0; i < 8; i++) {
    if(activePattern[i] == patternID_) {
      activePattern[i] = -1;
    }
  }
}

Pattern* Sequencer::getPattern(uint8_t patternID_) {
  return &pattern[patternID_];
}

void Sequencer::play() {
  playing = true;
  sixteenthCount = 0;
}

void Sequencer::stop() {
  playing = false;
  for(uint8_t i = 0; i < 8; i++) {
    if(activePattern[i] != -1) {
      pattern[activePattern[i]].stop(&midiManager);
    }
  }
}

void Sequencer::update() {
  if(playing) {
    //send midi clock msg at 24 ppqn (pulses per quarter note)
    if(millis() >= outputClockAccumulator + (beatLength/24)) {
      Serial.write(0xf8);//send the device a clock signal
      outputClockAccumulator += (beatLength/24);
    }
    
    
    if(millis() >= sixteenthAccumulator + (beatLength/16)) { //if it has been one sixteenth note.
      midiManager.sixteenthTick();
      for(uint8_t i = 0; i < 8; i++) {//for every active pattern..
        if(activePattern[i] != -1) {
          pattern[activePattern[i]].sixteenthTick(&midiManager); //send each pattern a beat tick
        }
      }
      
      sixteenthCount++;
      if(sixteenthCount >= 64*16) { //64*16 to account for at maximum, 64 beats.
        sixteenthCount = 0;
      }
      sixteenthAccumulator += (beatLength/16);
    }
  }
}
