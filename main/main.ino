#include <stdint.h>

#include "Pot.h"
#include "Sequencer.h"

Sequencer seq(120);

void tempoPotChangeMethod(uint16_t val_) {
  seq.setTempo(32 + (int)((val_/127.f) * 512.f));
}

Pot potpin(A0, 127, &tempoPotChangeMethod);

void setup() {
  Serial.begin(31250); //magical baud rate for midi 31250
  Serial.flush(); //idk if this is necessary.
  midiAllNotesOff(); //not sure if this is doing anything
  seq.setTempo(120);
  
  seq.getPattern(0)->randomize();
  seq.activatePattern(0);

  seq.getPattern(1)->setLength(4);
  seq.getPattern(1)->getStep(0)->setNote(32);
  seq.getPattern(1)->getStep(0)->setLength(2);
  seq.getPattern(1)->getStep(1)->setVelocity(0);
  seq.getPattern(1)->getStep(2)->setVelocity(0);
  seq.getPattern(1)->getStep(3)->setVelocity(0);
  seq.activatePattern(1);
  
  seq.play();
}

bool one = false;

void loop() {
  potpin.update();
  seq.update();


}




