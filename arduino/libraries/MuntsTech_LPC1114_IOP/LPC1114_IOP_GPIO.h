// LPC1114 I/O Processor GPIO pin services

// Copyright (C)2017-2018, Philip Munts, President, Munts AM Corp.
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

#ifndef _LPC1114_IOP_GPIO_H_
#define _LPC1114_IOP_GPIO_H_

#include "LPC1114_IOP_Common.h"

namespace LPC1114_IOP
{
  struct GPIO
  {
    // Default parameterless constructor -- The resulting object will not be
    // usable until reconstructed or Init() has been called!
    GPIO(void);

    // Construct a GPIO pin, given direction and initial state
    GPIO(Transport server, uint32_t pin, uint32_t direction, bool state);

    // Construct a GPIO pin, given configuration mode
    GPIO(Transport server, uint32_t pin, uint32_t mode);

    // Initialize a GPIO pin, given direction and initial state
    void Init(Transport server, uint32_t pin, uint32_t direction, bool state);

    // Initialize a GPIO pin, given configuration mode
    void Init(Transport server, uint32_t pin, uint32_t mode);

    // Configure GPIO pin mode
    void ConfigureMode(uint32_t mode);

    // Configure GPIO pin interrupt edge
    void ConfigureInterruptEdge(uint32_t edge);

    // Read GPIO pin state
    bool Get(void);

    // Write GPIO pin state
    void Put(bool state);

    operator bool(void);

    void operator=(const bool);

  private:

    Transport server;
    uint32_t pin;
  };
}

#endif
