// LPC1114 I/O Processor common functions

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

#ifdef __unix__
#include <cstring>
#include <string>
#endif

#ifdef __mbedos__
#include <mbed.h>
#include <assert.h>
#endif

#ifdef ARDUINO
#include <Arduino.h>
#endif

#include "LPC1114_IOP_Common.h"

namespace LPC1114_IOP
{
#ifdef __unix__
  // Unix platforms throw an exception upon an error

  void RaiseError(const char *message)
  {
    throw std::string("ERROR: ") + std::string(message);
  }

  void CheckError(const char *operation, int32_t error)
  {
    if (error)
      throw std::string("ERROR: ") + std::string(operation) +
        std::string(" failed, ") + std::string(strerror(error));
  }
#endif

#ifdef __mbedos__
  // Mbed OS platforms call assert() upon an error

  void RaiseError(const char *message)
  {
    printf("ERROR: %s\r\n\n", message);
    assert(false);
  }

  void CheckError(const char *operation, int32_t error)
  {
    if (error)
    {
      printf("ERROR: %s failed, %s\r\n\n", operation, strerror(error));
      assert(error == 0);
    }
  }
#endif

#ifdef ARDUINO
  // Arduino platforms print a message and exit upon an error

  void RaiseError(const char *message)
  {
    Serial.print("ERROR: ");
    Serial.print(message);
    Serial.print("\r\n\n");
    Serial.flush();
    exit(1);
  }

  void CheckError(const char *operation, int32_t error)
  {
    if (error)
    {
      Serial.print("ERROR: ");
      Serial.print(operation);
      Serial.print(" failed, error=");
      Serial.print(error, DEC);
      Serial.print("\r\n\n");
      Serial.flush();
      exit(1);
    }
  }
#endif
}
