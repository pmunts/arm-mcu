// Arduino DC Motor Test

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

// Low level motor control command

void WriteMotor(uint8_t dirpin, uint8_t pwmpin, int velocity)
{
  // Clip motor speeds
  if (velocity < -255) velocity = -255;
  if (velocity >  255) velocity = 255;

  if (velocity < 0)
  {
    digitalWrite(dirpin, false);
    analogWrite(pwmpin, -velocity);
  }
  else
  {
    digitalWrite(dirpin, true);
    analogWrite(pwmpin,  velocity);
  }
}

// Pin assignments

#if defined(ARDUINO_SEEED_XIAO_RP2040) || defined(ARDUINO_SEEED_XIAO_RP2040)
// MUNTS-0021 River Tech Motor Driver Board
const int DIRA = D7;  // Left  wheel direction control
const int PWMA = D8;  // Left  wheel speed control
const int DIRB = D9;  // Right wheel direction control
const int PWMB = D10; // Right wheel speed control
#else
// Grove sockets D2 and D4
const int DIRA = D2;  // Left  wheel direction control
const int PWMA = D3;  // Left  wheel speed control
const int DIRB = D4;  // Right wheel direction control
const int PWMB = D5;  // Right wheel speed control
#endif

// High level motion command -- left and right are velocity values
// from -255 (full speed reverse) to +255 (full speed ahead).

void move(int left, int right, int millisecs)
{
  WriteMotor(DIRA, PWMA, left);
  WriteMotor(DIRB, PWMB, right);
  delay(millisecs);
  WriteMotor(DIRA, PWMA, 0);
  WriteMotor(DIRB, PWMB, 0);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n\ecArduino DC Motor\n");
  Serial.flush();

  pinMode(DIRA, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(PWMB, OUTPUT);
  move(0, 0, 0);

  move(255, 0,  1000); // Left  wheel forward
  move(0, 255,  1000); // Right wheel forward
  move(-255, 0, 1000); // Left  wheel reverse
  move(0, -255, 1000); // Right wheel reverse
}

void loop()
{
}
