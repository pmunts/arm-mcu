// Servo output services using the Arduino Servo library

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

// This servo class is most useful on RP2040 and RP2350 platforms, as the
// Arduino-Pico core replaces the interrupt driven Arduino Servo library
// with one providing the same API but implemented with PIO state machines.

#ifndef _MUNTSTECH_SERVO_ARDUINO_H
#define _MUNTSTECH_SERVO_ARDUINO_H

#include <cassert>
#include <Servo.h>
#include <servo-interface.h>

using namespace MuntsTech::Interfaces::Servo;

namespace MuntsTech::Servo::Arduino
{
  struct Output_Class: public Output_Interface
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Output_Class()
    {
      this->servo    = NULL;
      this->swing    = 0;
      this->midpoint = 0;
    }

    Output_Class(unsigned pin, float position = POSITION_NEUTRAL,
      float minwidth = 1.0E-3F, float maxwidth = 2.0E-3F)
    {
      this->Initialize(pin, position, minwidth, maxwidth);
    }

    // Servo output initializer

    void Initialize(unsigned pin, float position = POSITION_NEUTRAL,
      float minwidth = 1.0E-3F, float maxwidth = 2.0E-3F)
    {
      assert(position >= POSITION_MIN);
      assert(position <= POSITION_MAX);
      int minw = minwidth*1.0E6; // Convert to int microseconds
      int maxw = maxwidth*1.0E6; // Convert to int microseconds
      this->servo = new ::Servo();
      this->servo->attach(pin, minw, maxw);
      this->swing    = (maxw - minw)/2;
      this->midpoint = minw + swing;
      this->write(position);
    }

    // Servo output methods

    virtual void write(const float position)
    {
      assert(this->servo != NULL);
      assert(position >= POSITION_MIN);
      assert(position <= POSITION_MAX);
      int usec = this->midpoint + (int) this->swing*position;
      this->servo->writeMicroseconds(usec);
    }

    // Servo output operators

#ifdef ENABLE_ASSIGNMENT_OPERATOR
    void operator =(const float position)
    {
      this->write(position);
    }
#endif

  private:

    ::Servo *servo; // Arduino Servo object instance
    int midpoint;   // usec
    int swing;      // usec
  };
}

#endif
