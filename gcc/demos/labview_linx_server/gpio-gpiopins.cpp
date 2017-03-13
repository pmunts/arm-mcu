// LabView LINX Remote I/O GPIO services for ARM Cortex M3/M4 GPIO pins

// Copyright (C)2016-2017, Philip Munts, President, Munts AM Corp.
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

#include <errno.h>
#include <gpiopins.h>
#include <string.h>

#include "gpio-gpiopins.h"

// GPIO pin constructor for an input pin

GPIO_GPIOPIN::GPIO_GPIOPIN(int32_t pin, uint32_t *input, uint32_t *output)
{
  this->IsOutput = false;
  this->IsConfigured = false;
  this->pin = pin;
  this->input = input;
  this->output = output;
}

// GPIO pin configuration method

void GPIO_GPIOPIN::configure(int32_t direction, int32_t *error)
{
  if (gpiopin_configure(this->pin, direction ? GPIOPIN_OUTPUT : GPIOPIN_INPUT) < 0)
  {
    *error = errno;
    return;
  }

  this->IsOutput = direction;
  this->IsConfigured = true;

  if (this->IsOutput) *(this->output) = false;
  *error = 0;
}

// GPIO pin read method

void GPIO_GPIOPIN::read(int32_t *state, int32_t *error)
{
  if (!this->IsConfigured)
  {
    if (gpiopin_configure(this->pin, GPIOPIN_INPUT) < 0)
    {
      *error = errno;
      return;
    }

    this->IsOutput = false;
    this->IsConfigured = true;
  }

  *state = *(this->input);
  *error = 0;
}

// GPIO pin write method

void GPIO_GPIOPIN::write(int32_t state, int32_t *error)
{
  if (!this->IsConfigured)
  {
    if (gpiopin_configure(this->pin, GPIOPIN_OUTPUT) < 0)
    {
      *error = errno;
      return;
    }

    this->IsOutput = true;
    this->IsConfigured = true;
  }

  *(this->output) = state;
  *error = 0;
}
