#include <stdint.h>

#include "Pot.h"
#include "Midi.h"
#include "Sequencer.h"

Sequencer seq(120);

void tempoPotChangeMethod(uint16_t val_) {
  seq.setTempo(32 + (int)((val_/127.f) * 512.f)); 
}

Pot potpin(A0, 127, &tempoPotChangeMethod);

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(31250); //magical baud rate for midi 31250
  Serial.flush(); //idk if this is necessary.
  seq.setTempo(120);
  
  seq.getPattern(0)->randomize(24);
  //seq.activatePattern(0);

  seq.getPattern(1)->setSize(4);
  seq.getPattern(1)->getStep(0)->setPitch(37);
  seq.getPattern(1)->getStep(0)->setLength(16);
  seq.getPattern(1)->getStep(1)->setVelocity(0);
  seq.getPattern(1)->getStep(2)->setVelocity(127);
  seq.getPattern(1)->getStep(3)->setVelocity(0);
  seq.activatePattern(1);
  
  seq.play();
}

void loop() {
  potpin.update();
  seq.update();
}




