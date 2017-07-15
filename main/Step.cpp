#include "Step.h"

/* Idea:
 * Have some kind of Midi-note-manager system that Steps communicate with. When a step wants to play a note, it sends its data to the midi-note-manager which will store a copy of that note, with pitch, velocity and note length, and handle the playing
 * and stopping of that note. This way Steps don't have to worry about calling NOTEOFF for every pitch they may have triggered, as it'll all be handled as a stack of immutable commands in a separate system. This will get rid of the
 * previousNote hack.
 */

Step::Step(){
  pitch = 48;
  length = 2; //in sixteenths. 8 = half a note.
   velocity = 32;
}

uint8_t Step::getPitch() {
  return pitch;
}

uint8_t Step::getVelocity() {
  return velocity;
}

uint8_t Step::getLength() {
  return length;
}

void Step::setPitch(uint8_t pitch_) {
  pitch = pitch_;
}

void Step::setVelocity(uint8_t velocity_) {
  velocity = velocity_;
}

void Step::setLength(uint8_t length_) {
  length = length_;
}

void Step::play(Midi* midiManager_) {
  midiManager_->playNote(pitch, length, velocity);
}

void Step::stop(Midi* midiManager_) {
  midiManager_->stopNote(pitch);
}
