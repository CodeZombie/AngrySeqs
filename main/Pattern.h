#ifndef Pattern_h
#define Pattern_h


#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include "Step.h"
#include "Midi.h"

class Pattern {
  private:
    uint8_t size; //in beats.
    uint8_t swing;
    Step step[16];
    uint16_t currentSixteenth;
    bool playing;
  public:
    Pattern();
    void randomize(uint16_t seed_);
    void setSize(uint8_t size_);
    void setSwing(uint8_t swing_);
    uint8_t getSize();
    uint8_t getSwing();
    Step* getStep(uint8_t stepID_);
    void setStep(uint8_t step_);
    void reset();
    void stop(Midi* midiManager_);
    void sixteenthTick(Midi* midiManager_);
};

#endif
