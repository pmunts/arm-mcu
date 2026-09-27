// LPC1114 I/O Processor Motor output services

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

#include "LPC1114_IOP_Motor.h"

namespace LPC1114_IOP
{
  // Default parameterless constructor -- The resulting object will not be
  // usable until reconstructed or Init() has been called!

  Motor::Motor(void)
  {
    this->server = nullptr;
    this->dir = nullptr;
    this->pwm1 = nullptr;
    this->pwm2 = nullptr;
    this->servo = nullptr;
    this->ired = nullptr;
    this->channel = 0;
    this->motor = 0;
  }

  // Motor controlled with a PWM speed output and a GPIO direction output

  Motor::Motor(Transport server, PWM *pwmout, GPIO *dirout)
  {
    Motor::Init(server, pwmout, dirout);
  }

  void Motor::Init(Transport server, PWM *pwmout, GPIO *dirout)
  {
    // Validate parameters

    if (server == nullptr)
      RaiseError("Server parameter is NULL");

    if (pwmout == nullptr)
      RaiseError("PWM output parameter is NULL");

    if (dirout == nullptr)
      RaiseError("Direction output parameter is NULL");

    // Stop motor

    pwmout->Put(0.0);
    dirout->Put(true);

    // Save parameters

    this->server = server;
    this->dir = dirout;
    this->pwm1 = pwmout;
    this->pwm2 = nullptr;
    this->servo = nullptr;
    this->ired = nullptr;
    this->channel = 0;
    this->motor = 0;
  }

  // Motor controlled with two PWM outputs (clockwise and counterclockwise)

  Motor::Motor(Transport server, PWM *pwmcw, PWM *pwmccw)
  {
    Motor::Init(server, pwmcw, pwmccw);
  }

  void Motor::Init(Transport server, PWM *pwmcw, PWM *pwmccw)
  {
    // Validate parameters

    if (server == nullptr)
      RaiseError("Server parameter is NULL");

    if (pwmcw == nullptr)
      RaiseError("Clockwise PWM output parameter is NULL");

    if (pwmccw == nullptr)
      RaiseError("Counterclockwise PWM output parameter is NULL");

    // Stop motor

    pwmcw->Put(0.0);
    pwmccw->Put(0.0);

    // Save parameters

    this->server = server;
    this->dir = nullptr;
    this->pwm1 = pwmcw;
    this->pwm2 = pwmccw;
    this->servo = nullptr;
    this->ired = nullptr;
    this->channel = 0;
    this->motor = 0;
  }

  // Motor controlled with a servo output (continuous rotation servo)

  Motor::Motor(Transport server, Servo *servo)
  {
    Motor::Init(server, servo);
  }

  void Motor::Init(Transport server, Servo *servo)
  {
    // Validate parameters

    if (server == nullptr)
      RaiseError("Server parameter is NULL");

    if (servo == nullptr)
      RaiseError("Servo output parameter is NULL");

    // Stop motor

    servo->Put(LPC1114_SERVO_NEUTRAL);

    // Save parameters

    this->server = server;
    this->dir = nullptr;
    this->pwm1 = nullptr;
    this->pwm2 = nullptr;
    this->servo = servo;
    this->ired = nullptr;
    this->channel = 0;
    this->motor = 0;
  }

  // Motor controlled by LEGO Power Functions Infrared Remote Control Protocol

  Motor::Motor(Transport server, LEGORC *ired, uint32_t channel, uint32_t motor)
  {
    Motor::Init(server, ired, channel, motor);
  }

  void Motor::Init(Transport server, LEGORC *ired, uint32_t channel, uint32_t motor)
  {
    // Validate parameters

    if (server == nullptr)
      RaiseError("Server parameter is NULL");

    if (ired == nullptr)
      RaiseError("Infrared Emitter parameter is NULL");

    if ((channel < 1) || (channel > 4))
      RaiseError("Invalid channel number");

    if ((motor < LEGORC_MOTORA) || (motor > LEGORC_MOTORB))
      RaiseError("Invalid motor ID");

    // Stop motor

    ired->Put(channel, motor, LEGORC_FORWARD, 0);

    // Save parameters

    this->server = server;
    this->dir = nullptr;
    this->pwm1 = nullptr;
    this->pwm2 = nullptr;
    this->servo = nullptr;
    this->ired = ired;
    this->channel = channel;
    this->motor = motor;
  }

  // Set motor speed

  void Motor::Put(const double velocity)
  {
    // Check for full construction

    if (this->server == nullptr)
      RaiseError("Object has not been fully constructed");

    // Validate parameters

    if ((velocity < LPC1114_MOTOR_SPEED_MIN) ||
      (velocity > LPC1114_MOTOR_SPEED_MAX))
      RaiseError("Invalid motor velocity");

    // PWM speed and GPIO direction

    if (this->dir != nullptr)
    {
      if (velocity >= 0.0)
      {
        this->pwm1->Put(0.0);
        this->dir->Put(true);
        this->pwm1->Put(100.0*velocity);
      }
      else
      {
        this->pwm1->Put(0.0);
        this->dir->Put(false);
        this->pwm1->Put(-100.0*velocity);
      }

      return;
    }

    // Clockwise PWM and counterclockwise PWM

    else if (this->pwm2 != nullptr)
    {
      if (velocity >= 0.0)
      {
        this->pwm2->Put(0.0);
        this->pwm1->Put(100.0*velocity);
      }
      else
      {
        this->pwm1->Put(0.0);
        this->pwm2->Put(-100.0*velocity);
      }

      return;
    }

    // Continuous rotation servo

    else if (this->servo != nullptr)
    {
      this->servo->Put(velocity);
    }

    // LEGO Power Function Infrared Remote Control

    else if (this->ired != nullptr)
    {
      if (velocity >= 0.0)
        this->ired->Put(this->channel, this->motor, LEGORC_FORWARD,
          uint32_t(7.0*velocity));
      else
        this->ired->Put(this->channel, this->motor, LEGORC_REVERSE,
          uint32_t(-7.0*velocity));
    }
  }

  // Set motor speed

  void Motor::operator =(const double velocity)
  {
    this->Put(velocity);
  }
}
