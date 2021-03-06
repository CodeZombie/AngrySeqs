#ifndef Sequencer_h
#define Sequencer_h

#include "Pattern.h"
#include "Midi.h"

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

// Your class header here...
class Sequencer {
  private:
    uint16_t tempo;
    bool playing;
    float beatLength;
    Pattern pattern[8];
    int8_t activePattern[8];
    Midi midiManager;
    float outputClockAccumulator;
    float sixteenthAccumulator;
    uint16_t sixteenthCount;
  public:
    Sequencer(uint16_t tempo_);
    void setTempo(uint16_t tempo_);
    void activatePattern(uint8_t patternID_);
    void deactivatePattern(uint8_t patternID_);
    Pattern* getPattern(uint8_t patternID_);
    void play();
    void stop();
    void update();
    void copyPattern(uint8_t fromPatternID_, uint8_t toPatternID_);
};
#endif
