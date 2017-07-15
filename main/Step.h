#ifndef Step_h
#define Step_h

#include "Midi.h"

class Step {
  private:
    uint8_t pitch; //http://www.electronics.dit.ie/staff/tscarff/Music_technology/midi/midi_note_numbers_for_octaves.htm
    uint8_t velocity; //0-127
    uint8_t length; //# of sixteenth-notes
  public:
    Step();
    uint8_t getPitch();
    uint8_t getVelocity();
    uint8_t getLength();
    void setPitch(uint8_t pitch_);
    void setVelocity(uint8_t velocity_);
    void setLength(uint8_t length_);
    
    void play(Midi* midiManager_);
    void stop(Midi* midiManager_);
};

#endif
