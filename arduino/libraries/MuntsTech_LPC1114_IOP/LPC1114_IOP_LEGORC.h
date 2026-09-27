// LPC1114 I/O Processor LEGO Power Functions Remote Control services

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

#ifndef _LPC1114_IOP_LEGORC_H_
#define _LPC1114_IOP_LEGORC_H_

#include "LPC1114_IOP_Common.h"

namespace LPC1114_IOP
{
  struct LEGORC
  {
    // Default parameterless constructor -- The resulting object will not be
    // usable until reconstructed or Init() has been called!
    LEGORC(void);

    // Construct a LEGO Power Functions Remote Control output, given a GPIO pin
    // number
    LEGORC(Transport server, uint32_t pin);

    // Initialize a LEGO Power Functions Remote Control output, given a GPIO pin
    // number
    void Init(Transport server, uint32_t pin);

    // Issue LEGO Power Functions Remote Control command
    void Put(uint32_t channel, uint32_t motor, uint32_t direction,
      uint32_t speed);

  private:

    Transport server;
    uint32_t pin;
  };
}

#endif
