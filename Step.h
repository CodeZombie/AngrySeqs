#ifndef Step_h
#define Step_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif


#define MIDI_NOTEON 0x90
#define MIDI_NOTEOFF 0x80

void midiNoteCommand(int command_, int pitch_, int velocity_); 

void midiAllNotesOff(); 


class Step {
  private:
    uint8_t note; //http://www.electronics.dit.ie/staff/tscarff/Music_technology/midi/midi_note_numbers_for_octaves.htm
    uint8_t velocity; //0-127
    uint8_t length; //used as follows: (4/length). A length value of 1 = 4 beats. length value of 4 = 1 beat. length value of 8 = half a beat, etc.
    bool playing;
    unsigned long playStartTime; //the time (in ms) that the note started playing.
  public:
    Step();
    uint8_t getNote();
    uint8_t getVelocity();
    uint8_t getLength();
    void setNote(uint8_t note_);
    void setVelocity(uint8_t velocity_);
    void setLength(uint8_t length_);
    void play(unsigned long currentTime_);//sets playStartTime, and sets "playing" to true.
    void stop();
    bool isPlaying();
    void update(unsigned long currentTime_, float beatLength); //tells the note if it needs to stop playing
};

#endif
