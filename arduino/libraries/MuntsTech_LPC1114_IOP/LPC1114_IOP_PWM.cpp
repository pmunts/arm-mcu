// LPC1114 I/O Processor Pulse Width Modulated output services

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

#include "LPC1114_IOP_PWM.h"

namespace LPC1114_IOP
{
  // Default parameterless constructor -- The resulting object will not be
  // usable until reconstructed or Init() has been called!

  PWM::PWM(void)
  {
    this->server = nullptr;
    this->pin = 0xFFFFFFFF;
  }

  // Construct a PWM output

  PWM::PWM(Transport server, uint32_t pin, uint32_t freq, double dutycycle)
  {
    PWM::Init(server, pin, freq, dutycycle);
  }

  // Initialize a PWM output

  void PWM::Init(Transport server, uint32_t pin, uint32_t freq,
    double dutycycle)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Validate parameters

    if (!IS_PWM(pin))
      RaiseError("Invalid PWM output pin number");

    if ((dutycycle < LPC1114_PWM_DUTY_MIN) && (dutycycle > LPC1114_PWM_DUTY_MAX))
      RaiseError("Invalid PWM duty cycle");

    // Configure PWM output

    cmd.command = SPIAGENT_CMD_CONFIGURE_PWM_OUTPUT;
    cmd.pin = pin;
    cmd.data = freq;

    server->Transaction(&cmd, &resp);
    CheckError("CONFIGURE PWM OUTPUT", resp.error);

    // Set initial duty cycle

    cmd.command = SPIAGENT_CMD_PUT_PWM;
    cmd.pin = pin;
    cmd.data = uint32_t(655.35*dutycycle + 0.5);

    server->Transaction(&cmd, &resp);
    CheckError("PWM PUT", resp.error);

    this->server = server;
    this->pin = pin;
  }

  // PWM output method

  void PWM::Put(const double dutycycle)
  {
    SPIAGENT_COMMAND_MSG_t cmd;
    SPIAGENT_RESPONSE_MSG_t resp;

    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    // Validate parameters

    if ((dutycycle < LPC1114_PWM_DUTY_MIN) && (dutycycle > LPC1114_PWM_DUTY_MAX))
      RaiseError("Invalid PWM duty cycle");

    cmd.command = SPIAGENT_CMD_PUT_PWM;
    cmd.pin = this->pin;
    cmd.data = uint32_t(655.35*dutycycle + 0.5);

    this->server->Transaction(&cmd, &resp);
    CheckError("PWM PUT", resp.error);
  }

  // PWM output operator

  void PWM::operator =(const double dutycycle)
  {
    this->Put(dutycycle);
  }

//****************************************************************************

  static double Position_To_Dutycycle(uint32_t freq, double position)
  {
    return (0.5E-1*position + 1.5E-1)*freq;
  }

  // Default parameterless constructor -- The resulting object will not be
  // usable until reconstructed or Init() has been called!

  Servo::Servo(void)
  {
    this->output = nullptr;
  }

  // Construct a Servo output

  Servo::Servo(Transport server, uint32_t pin, uint32_t freq, double position)
  {
    this->frequency = freq;
    this->output = new PWM(server, pin, freq,
      Position_To_Dutycycle(this->frequency, position));
  }

  // Initialize a servo output

  void Servo::Init(Transport server, uint32_t pin, uint32_t freq,
    double position)
  {
    this->frequency = freq;
    this->output = new PWM(server, pin, freq,
      Position_To_Dutycycle(this->frequency, position));
  }

  // Servo output method

  void Servo::Put(const double position)
  {
    // Check for full construction

    if (this->output == nullptr)
      RaiseError("Object has not been fully constructed");

    // Validate parameters

    if ((position < LPC1114_SERVO_MIN) && (position > LPC1114_SERVO_MAX))
      RaiseError("Invalid servo position");

    this->output->Put(Position_To_Dutycycle(this->frequency, position));
  }

  // Servo output operator

  void Servo::operator =(const double position)
  {
    this->Put(position);
  }
}
