// Skid Steer (aka Differential Steering) Vehicle Services

// Copyright (C)2026, Philip Munts dba Munts Technologies.
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

#ifndef _SKIDSTEER_H_
#define _SKIDSTEER_H_

#include <cassert>
#include <motor-interface.h>

using MuntsTech::Interfaces::Motor::Output;
using MuntsTech::Interfaces::Motor::SPEED_MIN;
using MuntsTech::Interfaces::Motor::SPEED_STOP;
using MuntsTech::Interfaces::Motor::SPEED_MAX;

namespace MuntsTech::SkidSteer
{
  static const float STEER_MIN  = -1.0F;
  static const float STEER_MAX  = +1.0F;
  static const float STEER_NONE =  0.0F;

  static const float SteeringSensitivity = 0.2;
  
  struct Vehicle2WD
  {
    // Parameterless stub constructor--Requires a subsequent
    // call to Initialize().

    Vehicle2WD()
    {
      this->LeftMotor  = nullptr;
      this->RightMotor = nullptr;
    }

    // 2WD Skid Steer vehicle constructor

    Vehicle2WD(Output left, Output right)
    {
      this->Initialize(left, right);
    }

    // 2WD Skid Steer vehicle initializer

    void Initialize(Output left, Output right)
    {
      assert(left  != nullptr);
      assert(right != nullptr);
      this->LeftMotor  = left;
      this->RightMotor = right;
    }

    // Initiate forward or reverse motion

    void Go(float newvelocity)
    {
      assert((newvelocity >= SPEED_MIN) && (newvelocity <= SPEED_MAX));
      this->LeftMotor->write(newvelocity);
      this->RightMotor->write(newvelocity);
      this->GoVelocity = newvelocity;
    }

    void Go(float newvelocity, unsigned milliseconds)
    {
      Go(newvelocity);
      delay(milliseconds);
    }

    // Stop motion

    void Stop(void)
    {
      Go(SPEED_STOP);
    }

    // Initiate a turn

    void Turn(float steering, unsigned milliseconds)
    {
      assert((steering >= STEER_MIN) && (steering <= STEER_MAX));
      if (steering == STEER_NONE) return;

      if (this->GoVelocity == SPEED_STOP)
      {
        // Spin in place
        this->LeftMotor->write(this->GoVelocity *(1.0 - SteeringSensitivity) + steering);
        this->RightMotor->write(this->GoVelocity*(1.0 - SteeringSensitivity) - steering);
      }
      else if (this->GoVelocity > SPEED_STOP)
      {
        // Moving forward
        this->LeftMotor->write(this->GoVelocity *(1.0 - SteeringSensitivity) + steering*SteeringSensitivity);
        this->RightMotor->write(this->GoVelocity*(1.0 - SteeringSensitivity) - steering*SteeringSensitivity);
      }
      else if (this->GoVelocity < SPEED_STOP)
      {
        // Moving reverse
        this->LeftMotor->write(this->GoVelocity *(1.0 - SteeringSensitivity) - steering*SteeringSensitivity);
        this->RightMotor->write(this->GoVelocity*(1.0 - SteeringSensitivity) + steering*SteeringSensitivity);
      }

      delay(milliseconds);

      // Resume forward or reverse motion
      Go(this->GoVelocity);
    }

  private:

    MuntsTech::Interfaces::Motor::Output LeftMotor;
    MuntsTech::Interfaces::Motor::Output RightMotor;

    float GoVelocity = MuntsTech::Interfaces::Motor::SPEED_STOP;
  };
}

#endif
