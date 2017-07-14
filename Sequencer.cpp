#include "Sequencer.h"

Sequencer::Sequencer(uint16_t tempo_) {
  tempo = tempo_;
  beatLength = (60.f/tempo)*1000.f;
  timeAccumulator = 0;
  for(uint8_t i = 0; i < 8; i++) {
    activePattern[i] = -1;
  }
}

void Sequencer::setTempo(uint16_t tempo_) {
  tempo = tempo_;
  beatLength = (60.f/tempo)*1000.f;
}

void Sequencer::activatePattern(uint8_t patternID_) {
  //pattern[patternID_].play();
  for(uint8_t i = 0; i < 8; i++) {
    if(activePattern[i] == -1) {
      activePattern[i] = patternID_;
      return;
    }
  }
}

void Sequencer::deactivatePattern(uint8_t patternID_) {
  pattern[patternID_].stop();
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
  for(uint8_t i = 0; i < 8; i++) {
    if(activePattern[i] != -1) {
      pattern[activePattern[i]].play();
    }
  }
}

void Sequencer::stop() {
  playing = false;
  for(uint8_t i = 0; i < 8; i++) {
    if(activePattern[i] != -1) {
      pattern[activePattern[i]].stop();
    }
  }
}

void Sequencer::update() {
  if(playing) {
    if(millis() >= timeAccumulator + beatLength) { //if it has been an entire beat (or more)
      for(uint8_t i = 0; i < 8; i++) {
        if(activePattern[i] != -1) {
          pattern[activePattern[i]].beatTick(millis()); //send each pattern a beat tick
        }
      }
      timeAccumulator += beatLength;
    }

    for(uint8_t i = 0; i < 8; i++) {
      if(activePattern[i] != -1) {
        pattern[activePattern[i]].update(millis(), beatLength);
      }
    }
  }
}
