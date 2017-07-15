#ifndef Pot_h
#define Pot_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

class Pot {
  private:
    uint16_t value = 0;
    uint8_t pin = 0;
    uint16_t potResolution = 0;
    const float smoothfactor = .5; //.15
    void (*changeMethod)(uint16_t);
  public:
    Pot(uint8_t pin_, uint16_t potResolution_, void (*changeMethod_)(uint16_t));
    void init();
    void update();
    uint16_t getValue();
};
#endif
