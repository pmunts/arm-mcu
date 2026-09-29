// MUNTS-0021 River Tech Motor Driver board services

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

#ifndef _MUNTSTECH_MUNTS_0021_H
#define _MUNTSTECH_MUNTS_0021_H

#include <Motor-PWM1.h>

namespace MuntsTech::MUNTS_0021::Motors
{
#ifdef MUNTS_0021_REV2
  const unsigned DIRA = 1;
  const unsigned PWMA = 2;
  const unsigned DIRB = 4;
  const unsigned PWMB = 3;
  const unsigned DIRC = 0;
  const unsigned PWMC = 7;
  const unsigned DIRD = 6;
  #ifdef ARDUINO_SEEED_XIAO_RP2040
    const unsigned PWMD = 29;
  #elifdef ARDUINO_SEEED_XIAO_RP2350
    const unsigned PWMD = 5;
  #else
    #error Unknown MCU module.
  #endif
#elifdef MUNTS_0021_REV3
  const unsigned DIRA = 6;
  #ifdef ARDUINO_SEEED_XIAO_RP2040
    const unsigned PWMA = 29;
  #elifdef ARDUINO_SEEED_XIAO_RP2350
    const unsigned PWMA = 5;
  #else
    #error Unknown MCU module.
  #endif
  const unsigned DIRB = 1;
  const unsigned PWMB = 28;
  const unsigned DIRC = 26;
  const unsigned PWMC = 7;
  const unsigned DIRD = 27;
  const unsigned PWMD = 0;
#else
  #error Unknown MUNTS-0021 board revision.
#endif

  MuntsTech::Motor::PWM1::Output_Class MotorA;
  MuntsTech::Motor::PWM1::Output_Class MotorB;
  MuntsTech::Motor::PWM1::Output_Class MotorC;
  MuntsTech::Motor::PWM1::Output_Class MotorD;

  void InitializeMotors(unsigned freq)
  {
    MotorA.Initialize(DIRA, PWMA, freq);
    MotorB.Initialize(DIRB, PWMB, freq);
    MotorC.Initialize(DIRC, PWMC, freq);
    MotorD.Initialize(DIRD, PWMD, freq);
  }
}

#endif
