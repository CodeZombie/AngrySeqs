#ifndef Midi_h
#define Midi_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

class Midi {
  private:
    int8_t noteData[64][2]; //[0] = pitch, [1] = note length, in # of sixteenths. (so, 16=1 beat. 32 = 2 beats. 64 = 4 beats, etc). a length value of -1 == disabled.
    void midiNoteOn(int8_t pitch_, int8_t velocity);
    void midiNoteOff(int8_t pitch_);
  public:
    Midi();
    void playNote(int8_t pitch_, int8_t length_, int8_t velocity);
    void stopNote(int8_t pitch_);
    void sixteenthTick();
    void midiAllNotesOff();
};

#endif
