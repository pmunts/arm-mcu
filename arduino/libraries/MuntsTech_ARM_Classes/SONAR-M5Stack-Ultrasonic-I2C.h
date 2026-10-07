// Copyright (C)2026, Philip Munts dba Munts Technologies.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef _SONAR_M5STACK_ULTRASONIC_I2C_H_
#define _SONAR_M5STACK_ULTRASONIC_I2C_H_

#include <Wire.h>
#include <pins_arduino.h>
#include <rangefinder-interface.h>

using namespace MuntsTech::Interfaces::RangeFinder;

namespace MuntsTech::SONAR::M5Stack_Ultrasonic_I2C
{
  struct RangeFinder_Class: public RangeFinder_Interface
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    RangeFinder_Class()
    {
      this->bus  = nullptr;
      this->addr = 0x00;
    }

    // M5 Stack Ultrasonic-I2C SONAR rangefinder object initializer

    void Initialize(TwoWire *I2CBus = &Wire, uint8_t I2CAddr = 0x57)
    {
      this->bus  = I2CBus;
      this->addr = I2CAddr;
      this->bus->begin();
    }

    float read(void)
    {
      // Transmit ping

      this->bus->beginTransmission(this->addr);
      this->bus->write(0x01);
      this->bus->endTransmission();

      delay(5);

      // Receive echo

      this->bus->requestFrom(this->addr, 3);
      uint8_t byte1 = this->bus->read();
      uint8_t byte2 = this->bus->read();
      uint8_t byte3 = this->bus->read();

      uint32_t rawdist = (byte1 << 16) | (byte2 << 8) | byte3;

      return float(rawdist)/10000.0F; // centimeters
    }

  private:

    TwoWire *bus;
    uint8_t addr;
  };
}

#endif
