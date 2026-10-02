// MUNTS-0020 Seeed Xiao RP2040/RP2350 Motor Driver Board Services

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

#ifndef _MUNTSTECH_MUNTS_0020_H
#define _MUNTSTECH_MUNTS_0020_H

#include <Motor-TB6612.h>

namespace MuntsTech::MUNTS_0020::Motors
{
  const unsigned MAPWM = 7;
  const unsigned MAIN1 = 6;
  const unsigned MAIN2 = 0;

  const unsigned MBPWM = 1;
  const unsigned MBIN1 = 27;
  const unsigned MBIN2 = 2;

  const unsigned SERVO1 = 3;
  const unsigned SERVO2 = 4;

  const unsigned GROVE0 = 29;
  const unsigned GROVE1 = 28;

  MuntsTech::Motor::TB6612::Output_Class MotorA;
  MuntsTech::Motor::TB6612::Output_Class MotorB;

  void InitializeAB(unsigned freq)
  {
    MotorA.Initialize(MAPWM, MAIN1, MAIN2, freq);
    MotorB.Initialize(MBPWM, MBIN1, MBIN2, freq);
  }
}

#endif
