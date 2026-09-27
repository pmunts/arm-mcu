// LPC1114 I/O Processor 32-bit Counter/Timer services

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

#include "LPC1114_IOP_Timer.h"

namespace LPC1114_IOP
{
  // Default parameterless constructor -- The resulting object will not be
  // usable until reconstructed or Init() has been called!

  Timer::Timer(void)
  {
    this->server = nullptr;
    this->timer = 0xFFFFFFFF;
  }

  // Construct a timer object

  Timer::Timer(Transport server, uint32_t timer)
  {
    Timer::Init(server, timer);
  }

  // Initialize a timer object

  void Timer::Init(Transport server, uint32_t timer)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Validate parameters

    if (server == nullptr)
      RaiseError("Server parameter is NULL");

    if (timer >= LPC1114_TIMER_ID_SENTINEL)
      RaiseError("Invalid timer ID");

    // Dispatch the command

    cmd.command = SPIAGENT_CMD_INIT_TIMER;
    cmd.pin = timer;
    cmd.data = 0;

    this->server->Transaction(&cmd, &resp);
    CheckError("TIMER INIT", resp.error);

    this->server = server;
    this->timer = timer;
  }

  // Configure timer mode

  void Timer::ConfigureMode(uint32_t mode)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    // Validate parameters

    if (timer >= LPC1114_TIMER_ID_SENTINEL)
      RaiseError("Invalid timer ID");

    if (mode >= LPC1114_TIMER_MODE_SENTINEL)
      RaiseError("Invalid timer mode");

    // Dispatch the command

    cmd.command = SPIAGENT_CMD_CONFIGURE_TIMER_MODE;
    cmd.pin = this->timer;
    cmd.data = mode;

    this->server->Transaction(&cmd, &resp);
    CheckError("TIMER MODE", resp.error);
  }

  // Configure prescaler

  void Timer::ConfigurePrescaler(uint32_t divisor)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    // Validate parameters

    if (divisor == 0)
      RaiseError("Invalid prescaler value");

    // Dispatch the command

    cmd.command = SPIAGENT_CMD_CONFIGURE_TIMER_MODE;
    cmd.pin = this->timer;
    cmd.data = divisor;

    this->server->Transaction(&cmd, &resp);
    CheckError("TIMER MODE", resp.error);
  }

  // Configure capture edge

  void Timer::ConfigureCapture(uint32_t edge, bool intr)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    // Validate parameters

    if (edge >= LPC1114_TIMER_CAPTURE_EDGE_SENTINEL)
      RaiseError("Invalid timer input edge");

    // Dispatch the command

    cmd.command = SPIAGENT_CMD_CONFIGURE_TIMER_MODE;
    cmd.pin = this->timer;
    cmd.data = edge | (intr << 4);

    this->server->Transaction(&cmd, &resp);
    CheckError("TIMER MODE", resp.error);
  }

  // Configure match register

  void Timer::ConfigureMatch(uint32_t match, uint32_t value, uint32_t action,
    bool intr, bool reset, bool stop)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    // Validate parameters

    if (match >= LPC1114_TIMER_MATCH_SENTINEL)
      RaiseError("Invalid match register ID");

    if (action >= LPC1114_TIMER_MATCH_OUTPUT_SENTINEL)
      RaiseError("Invalid match action");

    // Dispatch the command

    cmd.command = SPIAGENT_CMD_CONFIGURE_TIMER_MATCH0 + match;
    cmd.pin = this->timer;
    cmd.data = action | (intr << 4) | (reset << 5) | (stop << 6);

    this->server->Transaction(&cmd, &resp);
    CheckError("TIMER MATCH", resp.error);

    // Dispatch the command

    cmd.command = SPIAGENT_CMD_CONFIGURE_TIMER_MATCH0_VALUE + match;
    cmd.pin = this->timer;
    cmd.data = value;

    this->server->Transaction(&cmd, &resp);
    CheckError("TIMER MATCH VALUE", resp.error);
  }

  // Get current timer value

  uint32_t Timer::Get(void)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    static const uint32_t CounterAddresses[LPC1114_TIMER_ID_SENTINEL] =
    {
      0x40014008,
      0x40018008,
    };

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    // Dispatch the command

    cmd.command = SPIAGENT_CMD_GET_SFR;
    cmd.pin = CounterAddresses[this->timer];
    cmd.data = 0;

    this->server->Transaction(&cmd, &resp);
    CheckError("SFR GET", resp.error);

    return resp.data;
  }

  // Get latest capture value

  uint32_t Timer::GetCapture(void)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    static const uint32_t CaptureAddresses[LPC1114_TIMER_ID_SENTINEL] =
    {
      0x4001402C,
      0x4001802C,
    };

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    // Dispatch the command

    cmd.command = SPIAGENT_CMD_GET_SFR;
    cmd.pin = CaptureAddresses[this->timer];
    cmd.data = 0;

    this->server->Transaction(&cmd, &resp);
    CheckError("SFR GET", resp.error);

    return resp.data;
  }

  // Get latest capture delta value

  uint32_t Timer::GetCaptureDelta(void)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    // Dispatch the command

    cmd.command = SPIAGENT_CMD_GET_TIMER_CAPTURE_DELTA;
    cmd.pin = this->timer;
    cmd.data = 0;

    this->server->Transaction(&cmd, &resp);
    CheckError("TIMER GET CAPTURE DELTA", resp.error);

    return resp.data;
  }

  // Get current timer value

  Timer::operator uint32_t(void)
  {
    return this->Get();
  }
}
