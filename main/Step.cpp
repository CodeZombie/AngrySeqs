#include "Step.h"

/* Idea:
 * Have some kind of Midi-note-manager system that Steps communicate with. When a step wants to play a note, it sends its data to the midi-note-manager which will store a copy of that note, with pitch, velocity and note length, and handle the playing
 * and stopping of that note. This way Steps don't have to worry about calling NOTEOFF for every pitch they may have triggered, as it'll all be handled as a stack of immutable commands in a separate system. This will get rid of the
 * previousNote hack.
 */


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
  previousNote = -1;
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
  previousNote = note;
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
  if(previousNote != -1) {
    midiNoteCommand(MIDI_NOTEOFF, previousNote, 0); //send a note-off command just in case the current note is playing..
    previousNote = -1;
  }
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
