#include "Sequencer.h"

Sequencer::Sequencer(uint16_t tempo_) {
  tempo = tempo_;
  beatLength = (60.f/tempo)*1000.f;
  beatCount = 0; //number of beats since we started playing
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
  pattern[patternID_].setStep(beatCount % pattern[patternID_].getLength()); //keep the pattern on-time with the rest of the sequence.
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
  beatCount = 0;
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
     for(uint8_t i = 0; i < 8; i++) {
      if(activePattern[i] != -1) {
        pattern[activePattern[i]].update(millis(), beatLength);
      }
    }

    //send midi clock msg at 24 ppqn (pulses per quarter note)
    if(millis() >= ppqnAccumulator + (beatLength/24)) {
      Serial.write(0xf8);
      ppqnAccumulator += (beatLength/24);
    }
    
    if(millis() >= timeAccumulator + beatLength) { //if it has been an entire beat (or more)
      beatCount++;
      if(beatCount >= 64) { //reset the beatCount at 64 beats to avoid overflows. 64 chosen because thats the absolute logical maximum you would probably ever make a pattern. To be replaced with a constant
        beatCount = 0;
      }
      for(uint8_t i = 0; i < 8; i++) {
        if(activePattern[i] != -1) {
          pattern[activePattern[i]].beatTick(millis()); //send each pattern a beat tick
        }
      }
      timeAccumulator += beatLength;
    }
  }
}
