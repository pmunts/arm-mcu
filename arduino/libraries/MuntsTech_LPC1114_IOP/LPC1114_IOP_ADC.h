// LPC1114 I/O Processor A/D converter input services

// Copyright (C)2018-2026, Philip Munts dba Munts Technologies.
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

#ifndef _LPC1114_IOP_ADC_H_
#define _LPC1114_IOP_ADC_H_

// ADC is defined as a macro in Arduino and MbedOS

#undef ADC
#undef ADC_RESOLUTION

#include "LPC1114_IOP_Common.h"

namespace LPC1114_IOP
{
  const uint32_t ADC_RESOLUTION = 10;
  const uint32_t ADC_STEPS      = 1024;
  const double   ADC_REFERENCE  = 3.3;
  const double   ADC_STEPSIZE   = ADC_REFERENCE/ADC_STEPS;

  struct ADC
  {
    // Default parameterless constructor -- The resulting object will not be
    // usable until reconstructed or Init() has been called!
    ADC(void);

    // Construct an analog input
    ADC(Transport server, uint32_t pin);

    // Initialize an analog input
    void Init(Transport server, uint32_t pin);

    // Sample analog input
    uint32_t Get(void);

    // Sample analog input voltage
    double Voltage(void);

    // Sample analog input
    operator uint32_t(void);

    // Sample analog input voltage
    operator double(void);

  private:

    Transport server;
    uint32_t pin;
  };
}

#endif
