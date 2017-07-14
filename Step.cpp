#include "Step.h"

void midiNoteCommand(int command_, int pitch_, int velocity_) {
  Serial.write(command_);
  Serial.write(pitch_);
  Serial.write(velocity_);
}

void midiAllNotesOff() {
  Serial.write(0x78);
}


Step::Step(){
  note = 48;
  velocity = 32;
  length = 8; //4 == note length of 1 bar
  playing = false;
  playStartTime = 0;
}

uint8_t Step::getNote() {
  return note;
}

uint8_t Step::getVelocity() {
  return velocity;
}

uint8_t Step::getLength() {
  return length;
}

void Step::setNote(uint8_t note_) {
  note = note_;
}

void Step::setVelocity(uint8_t velocity_) {
  velocity = velocity_;
}

void Step::setLength(uint8_t length_) {
  length = length_;
}

void Step::play(unsigned long currentTime_) {
  playStartTime = currentTime_;
  playing = true;
  midiNoteCommand(MIDI_NOTEON, note, velocity);
}

void Step::stop() {
  playing = false;
  midiNoteCommand(MIDI_NOTEOFF, note, 0);
}

bool Step::isPlaying() {
  return playing;
}

void Step::update(unsigned long currentTime_, float beatLength_) {
  if(isPlaying()) {
    if(currentTime_ - playStartTime >= beatLength_ * (4.f/length)) { //if the time passed since this note started playing is greater or equal to the length of the note
      stop();
    }
  }
}
