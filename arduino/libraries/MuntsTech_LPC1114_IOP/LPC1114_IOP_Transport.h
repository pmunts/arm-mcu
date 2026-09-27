// LPC1114 I/O Processor message transport services

// Copyright (C)2017-2026, Philip Munts dba Munts Technologies.
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

#ifndef _LPC1114_IOP_TRANSPORT_H_
#define _LPC1114_IOP_TRANSPORT_H_

#ifdef __mbedos__
#include <mbed.h>
#endif

#ifdef ARDUINO
#ifdef __ARM_ARCH
#include <Arduino_ARM.h>
#else
#include <Arduino.h>
#endif
#endif

#include "LPC1114_IOP_Common.h"

namespace LPC1114_IOP
{
  struct Transport_Class: Transport_Interface
  {
    // Default parameterless constructor
    // Note: Must "Do The Right Thing" on all platforms!

    Transport_Class(void);

    // Dispatch a command to the LPC1114 I/O Processor and fetch the response

    void Transaction(SPIAGENT_COMMAND_MSG_t *cmd,
      SPIAGENT_RESPONSE_MSG_t *resp);

#ifdef __unix__
    // Unix platforms use libspiagent

    static constexpr const char *DefaultServer = "ioctl://localhost";

    Transport_Class(const char *servername);
#endif

#ifdef __mbedos__
    // Mbed OS platforms use I2C

    static const uint8_t DefaultAddress = 0x44;

    Transport_Class(I2C *bus, uint8_t addr = DefaultAddress, PinName ready = NC);

  private:

    I2C     *bus;
    uint8_t addr;
    DigitalIn *ready;
#endif

#ifdef ARDUINO
    // Arduino platforms use I2C

#ifndef I2C_BUS
#define I2C_BUS Wire
#endif

    static const uint8_t DefaultAddress = 0x44;

    void Init(uint8_t addr = DefaultAddress, int ready = -1);

  private:

    uint8_t addr;
    int ready;
#endif
  };
}

#endif
