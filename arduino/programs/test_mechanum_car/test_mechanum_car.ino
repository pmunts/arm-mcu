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

#include <Arduino_ARM.h>
#include <Motor-PWM1.h>

MuntsTech::Motor::PWM1::Output_Class MotorFrontLeft;
MuntsTech::Motor::PWM1::Output_Class MotorFrontRight;
MuntsTech::Motor::PWM1::Output_Class MotorRearLeft;
MuntsTech::Motor::PWM1::Output_Class MotorRearRight;

void setup()
{
  // Initialize motor driver outputs

  MotorFrontLeft.Initialize(D2,  D3,  10000);
  MotorFrontRight.Initialize(D4, D5,  10000);
  MotorRearLeft.Initialize(D6,   D7,  10000);
  MotorRearRight.Initialize(D26, D27, 10000);

  // Forward

  MotorFrontLeft.write(1.0);
  MotorFrontRight.write(1.0);
  MotorRearLeft.write(1.0);
  MotorRearRight.write(1.0);
  delay(2000);
  MotorFrontLeft.write(0.0);
  MotorFrontRight.write(0.0);
  MotorRearLeft.write(0.0);
  MotorRearRight.write(0.0);

  // Reverse

  MotorFrontLeft.write(-1.0);
  MotorFrontRight.write(-1.0);
  MotorRearLeft.write(-1.0);
  MotorRearRight.write(-1.0);
  delay(2000);
  MotorFrontLeft.write(0.0);
  MotorFrontRight.write(0.0);
  MotorRearLeft.write(0.0);
  MotorRearRight.write(0.0);

  // Left

  MotorFrontLeft.write(-1.0);
  MotorFrontRight.write(1.0);
  MotorRearLeft.write(1.0);
  MotorRearRight.write(-1.0);
  delay(2000);
  MotorFrontLeft.write(0.0);
  MotorFrontRight.write(0.0);
  MotorRearLeft.write(0.0);
  MotorRearRight.write(0.0);

  // Right

  MotorFrontLeft.write(1.0);
  MotorFrontRight.write(-1.0);
  MotorRearLeft.write(-1.0);
  MotorRearRight.write(1.0);
  delay(2000);
  MotorFrontLeft.write(0.0);
  MotorFrontRight.write(0.0);
  MotorRearLeft.write(0.0);
  MotorRearRight.write(0.0);
}

void loop()
{
}
