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

class Pattern {
  private:
    uint8_t length;
    uint8_t swing;
    Step step[16];
    uint8_t currentStep;
    bool playing;
  public:
    Pattern();
    void randomize();
    void setLength(uint8_t length_);
    void setSwing(uint8_t swing_);
    uint8_t getLength();
    uint8_t getSwing();
    Step* getStep(uint8_t stepID_);
    void setStep(uint8_t step_);
    void reset();
    void stop();
    void update(unsigned long currentTime_, float beatLength_);
    void beatTick(unsigned long currentTime_); //called when one beat has passed.
};

#endif
