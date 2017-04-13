#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#include "Arduino.h"
#include <MySensors.h>

#define CHILD_ID_MOTION 2

MyMessage msg(CHILD_ID_MOTION, V_TRIPPED);


class HCSR501Sensor {
  private:
    uint8_t _pin;

  public:
    HCSR501Sensor(uint8_t pin)
    {
      _pin = pin;
    }

    void begin()
    {
      Serial.println("Setting up Motion Sensor");
      pinMode(_pin, INPUT);
    }

    uint8_t async()
    {
      return digitalPinToInterrupt(_pin);
    }

    void sync()
    {
      // Read digital motion value
        boolean tripped = digitalRead(_pin) == HIGH;
        Serial.print("Tripped: "); Serial.println(tripped);

        send(msg.set(tripped ? "1" : "0"));  // Send tripped value to gw
    }

     void present(uint8_t motion = CHILD_ID_MOTION)
     {
        // Register all sensors to gw (they will be created as child devices)
        ::present(motion, S_MOTION);
     }
};

#endif
