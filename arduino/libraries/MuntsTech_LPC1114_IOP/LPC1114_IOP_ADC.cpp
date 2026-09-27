// LPC1114 I/O Processor A/D converter input services

// Copyright (C)2018, Philip Munts, President, Munts AM Corp.
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

#include "LPC1114_IOP_ADC.h"

namespace LPC1114_IOP
{
  // Default parameterless constructor -- The resulting object will not be
  // usable until reconstructed or Init() has been called!

  ADC::ADC(void)
  {
    this->server = nullptr;
    this->pin = 0xFFFFFFFF;
  }

  // Construct an analog input

  ADC::ADC(Transport server, uint32_t pin)
  {
    ADC::Init(server, pin);
  }

  // Initialize an analog input

  void ADC::Init(Transport server, uint32_t pin)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Validate parameters

    if (!IS_ANALOG(pin))
      RaiseError("Invalid analog input pin number");

    cmd.command = SPIAGENT_CMD_CONFIGURE_ANALOG_INPUT;
    cmd.pin = pin;

    server->Transaction(&cmd, &resp);
    CheckError("CONFIGURE ANALOG INPUT", resp.error);

    this->server = server;
    this->pin = pin;
  }

  // Sample analog input

  uint32_t ADC::Get(void)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    cmd.command = SPIAGENT_CMD_GET_ANALOG;
    cmd.pin = this->pin;
    cmd.data = 0;

    this->server->Transaction(&cmd, &resp);
    CheckError("GPIO GET", resp.error);

    return resp.data;
  }

  // Sample analog input voltage

  double ADC::Voltage(void)
  {
    return this->Get()*ADC_STEPSIZE;
  }

  // Sample analog input

  ADC::operator uint32_t(void)
  {
    return this->Get();
  }

  // Sample analog input voltage

  ADC::operator double(void)
  {
    return this->Voltage();
  }
}
