#include <stdint.h>
#include "Sequencer.h"

Sequencer seq(120);

void setup() {
  Serial.begin(31250); //magical baud rate for midi 31250
  Serial.flush(); //idk if this is necessary.
  midiAllNotesOff(); //not sure if this is doing anything
  
  seq.setTempo(160);
  
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

void loop() {
  seq.update();
}




