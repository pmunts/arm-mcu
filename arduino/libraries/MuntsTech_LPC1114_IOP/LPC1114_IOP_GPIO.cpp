// Raspberry Pi LPC1114 I/O Processor Expansion Board GPIO pin services

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

#include "LPC1114_IOP_GPIO.h"

namespace LPC1114_IOP
{
  // Default parameterless constructor -- The resulting object will not be
  // usable until reconstructed or Init() has been called!

  GPIO::GPIO(void)
  {
    this->server = nullptr;
    this->pin = 0xFFFFFFFF;
  }

  // Construct a GPIO pin, given direction and initial state

  GPIO::GPIO(Transport server, uint32_t pin, uint32_t direction, bool state)
  {
    GPIO::Init(server, pin, direction, state);
  }

  // Construct a GPIO pin, given configuration mode

  GPIO::GPIO(Transport server, uint32_t pin, uint32_t mode)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Validate parameters

    if (!IS_GPIO(pin) && !IS_LED(pin))
      RaiseError("Invalid GPIO pin number");

    if (mode >= LPC1114_GPIO_MODE_SENTINEL)
      RaiseError("Invalid GPIO pin mode");

    cmd.command = SPIAGENT_CMD_CONFIGURE_GPIO;
    cmd.pin = pin;
    cmd.data = mode;

    server->Transaction(&cmd, &resp);
    CheckError("GPIO CONFIGURE MODE", resp.error);

    this->server = server;
    this->pin = pin;
  }

  // Initialize a GPIO pin, given direction and initial state

  void GPIO::Init(Transport server, uint32_t pin, uint32_t direction, bool state)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Validate parameters

    if (!IS_GPIO(pin) && !IS_LED(pin))
      RaiseError("Invalid GPIO pin number");

    if (direction >= LPC1114_GPIO_DIRECTION_SENTINEL)
      RaiseError("Invalid GPIO pin direction");

    if (direction)
      cmd.command = SPIAGENT_CMD_CONFIGURE_GPIO_OUTPUT;
    else
      cmd.command = SPIAGENT_CMD_CONFIGURE_GPIO_INPUT;

    cmd.pin = pin;
    cmd.data = state;

    server->Transaction(&cmd, &resp);
    CheckError("GPIO CONFIGURE", resp.error);

    this->server = server;
    this->pin = pin;
  }

  // Initialize a GPIO pin, given configuration mode

  void GPIO::Init(Transport server, uint32_t pin, uint32_t mode)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Validate parameters

    if (!IS_GPIO(pin) && !IS_LED(pin))
      RaiseError("Invalid GPIO pin number");

    if (mode >= LPC1114_GPIO_MODE_SENTINEL)
      RaiseError("Invalid GPIO pin mode");

    cmd.command = SPIAGENT_CMD_CONFIGURE_GPIO;
    cmd.pin = pin;
    cmd.data = mode;

    server->Transaction(&cmd, &resp);
    CheckError("GPIO CONFIGURE MODE", resp.error);

    this->server = server;
    this->pin = pin;
  }

  // Configure GPIO pin mode

  void GPIO::ConfigureMode(uint32_t mode)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    // Validate parameters

    if (mode >= LPC1114_GPIO_MODE_SENTINEL)
      RaiseError("Invalid GPIO pin mode");

    cmd.command = SPIAGENT_CMD_CONFIGURE_GPIO;
    cmd.pin = this->pin;
    cmd.data = mode;

    this->server->Transaction(&cmd, &resp);
    CheckError("GPIO CONFIGURE MODE", resp.error);
  }

  // Configure GPIO pin interrupt edge

  void GPIO::ConfigureInterruptEdge(uint32_t edge)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    // Validate parameters

    if (edge >= LPC1114_GPIO_INTERRUPT_SENTINEL)
      RaiseError("Invalid GPIO pin interrupt edge");

    cmd.command = SPIAGENT_CMD_CONFIGURE_GPIO_INTERRUPT;
    cmd.pin = this->pin;
    cmd.data = edge;

    this->server->Transaction(&cmd, &resp);
    CheckError("GPIO CONFIGURE INTERRUPT", resp.error);
  }

  // Read GPIO pin state

  bool GPIO::Get(void)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    cmd.command = SPIAGENT_CMD_GET_GPIO;
    cmd.pin = this->pin;
    cmd.data = 0;

    this->server->Transaction(&cmd, &resp);
    CheckError("GPIO GET", resp.error);

    return resp.data;
  }

  // Write GPIO pin state

  void GPIO::Put(bool state)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    cmd.command = SPIAGENT_CMD_PUT_GPIO;
    cmd.pin = this->pin;
    cmd.data = state;

    this->server->Transaction(&cmd, &resp);
    CheckError("GPIO PUT", resp.error);
  }

  // Read GPIO pin state

  GPIO::operator bool(void)
  {
    return this->Get();
  }

  // Write GPIO pin state

  void GPIO::operator=(const bool state)
  {
    this->Put(state);
  }
}
