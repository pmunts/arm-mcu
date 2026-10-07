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
#include <SONAR-M5Stack-Ultrasonic-I2C.h>

MuntsTech::SONAR::M5Stack_Ultrasonic_I2C::RangeFinder_Class SONAR;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n\ecArduino M5 Stack Ultrasonic-I2C SONAR Test\n");
  Serial.flush();

  // Board specific I2C bus initialization

#if   defined(ARDUINO_CYTRON_MAKER_NANO_RP2040)
  // Maker Port 0
  Wire.setSCL(1);
  Wire.setSDA(0);
#elif defined(ARDUINO_SEEED_XIAO_RP2040) || defined(ARDUINO_SEEED_XIAO_RP2350)
  #ifdef MUNTS_0021_REV3
    // Edge pins D8 and D10
    Wire.setSCL(3);
    Wire.setSDA(2);
  #else
    // Edge pins D4 and D5
    Wire.setSCL(7);
    Wire.setSDA(6);
  #endif
#elif defined(ARDUINO_SPARKFUN_PROMICRO_RP2040) || defined(ARDUINO_SPARKFUN_PROMICRO_RP2350)
  Wire.setSCL(17);
  Wire.setSDA(16);
#elif defined(ARDUINO_PIMORONI_TINY2350)
  Wire.setSCL(13);
  Wire.setSDA(12);
#else
  // Raspberry Pi Pico default
  Wire.setSCL(5);
  Wire.setSDA(4);
#endif

  SONAR.Initialize(&Wire, 0x57);
}

void loop()
{
  Serial.print("Distance: ");
  Serial.println(SONAR.read());
  delay(500);
}
