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

#include "LPC1114_IOP_LEGORC.h"

namespace LPC1114_IOP
{
  // Default parameterless constructor -- The resulting object will not be
  // usable until reconstructed or Init() has been called!

  LEGORC::LEGORC(void)
  {
    this->server = nullptr;
    this->pin = 0xFFFFFFFF;
  }

  // Construct a LEGO Power Functions Remote Control output, given a GPIO pin
  // number

  LEGORC::LEGORC(Transport server, uint32_t pin)
  {
    LEGORC::Init(server, pin);
  }

  // Initialize LEGO Power Functions Remote Control output, given a GPIO pin
  // number

  void LEGORC::Init(Transport server, uint32_t pin)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Validate parameters

    if (!IS_GPIO(pin))
      RaiseError("Invalid GPIO pin number");

    cmd.command = SPIAGENT_CMD_CONFIGURE_GPIO_OUTPUT;
    cmd.pin = pin;
    cmd.data = false;

    server->Transaction(&cmd, &resp);
    CheckError("GPIO CONFIGURE", resp.error);

    this->server = server;
    this->pin = pin;
  }

  // Issue LEGO Power Functions Remote Control command

  void LEGORC::Put(uint32_t channel, uint32_t motor, uint32_t direction,
    uint32_t speed)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    // Validate parameters

    if ((channel < 1) || (channel > 4))
      RaiseError("Invalid channel number");

    if (motor >= LEGORC_MOTOR_SENTINEL)
      RaiseError("Invalid motor ID");

    if (direction >= LEGORC_DIRECTION_SENTINEL)
      RaiseError("Invalid direction");

    if (speed > 255)
      RaiseError("Invalid speed");

    // Build the command structure

    cmd.command = SPIAGENT_CMD_PUT_LEGORC;
    cmd.pin = this->pin;
    cmd.data = speed | (direction << 8) | (motor << 16) | (channel << 24);

    // Issue the command

    this->server->Transaction(&cmd, &resp);
    CheckError("LEGO RC PUT", resp.error);
  }
}
