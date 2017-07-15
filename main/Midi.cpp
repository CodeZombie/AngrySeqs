#include "Midi.h"

Midi::Midi() {
  //initialize all notes
  for(uint8_t i = 0; i < 64; i++) {
    noteData[i][0] = 0;
    noteData[i][1] = -1;
  }
}

void Midi::playNote(int8_t pitch_, int8_t length_, int8_t velocity_){
  //find a disabled note slot, pass it the data from the arguments, then trigger the midi event.
  //if there is no empty slot (very unlikely, but possible, I guess), choose the active note with the smallest length, disable it, turn it's midi note off, and then use that spot
  
  bool foundEmptySlot = false;
  for(uint8_t i = 0; i < 64; i++) {
    if(noteData[i][1] == -1) {
      noteData[i][0] = pitch_;
      noteData[i][1] = length_;
      foundEmptySlot = true;
      break;
    }
  }
  if(foundEmptySlot == false) {
    //find and choose an active note with the smallest length, disable it, turn it's midi note off, and then use that spot
  }
  midiNoteOn(pitch_, velocity_);
}

void Midi::stopNote(int8_t pitch_){
  midiNoteOff(pitch_);
}

void Midi::sixteenthTick() {
  for(uint8_t i = 0; i < 64; i++) {//for each note slot
    if(noteData[i][1] != -1) {//if the note slot is active
      noteData[i][1] -= 1;//subtract one sixteenth from it's time
      if(noteData[i][1] <= 0) { //if its at or below 0 note length
        midiNoteOff(noteData[i][0]); //turn the note off
        noteData[i][1] = -1; //and deactivate the slot.
      }
    }
  }
}

void Midi::midiNoteOn(int8_t pitch_, int8_t velocity_){
  Serial.write(0x90);
  Serial.write(pitch_);
  Serial.write(velocity_);
}

void Midi::midiNoteOff(int8_t pitch_){
  Serial.write(0x80);
  Serial.write(pitch_);
  Serial.write(0);
}

void Midi::midiAllNotesOff() {
  Serial.write(0x78);
}

