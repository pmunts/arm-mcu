// LPC1114 I/O Processor message transport services

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

#ifdef ARDUINO
#include <Wire.h>
#endif

#include "LPC1114_IOP_Transport.h"

namespace LPC1114_IOP
{
#ifdef __unix__
  // Unix platforms use libspiagent

  Transport_Class::Transport_Class(void)
  {
    int32_t error;

    spiagent_open(DefaultServer, &error);
    CheckError("spiagent_open()", error);
  }

  Transport_Class::Transport_Class(const char *servername)
  {
    int32_t error;

    spiagent_open(servername, &error);
    CheckError("spiagent_open()", error);
  }

  void Transport_Class::Transaction(SPIAGENT_COMMAND_MSG_t *cmd,
    SPIAGENT_RESPONSE_MSG_t *resp)
  {
    int32_t error;

    spiagent_command(cmd, resp, &error);
    CheckError("spiagent_command()", error);
  }
#endif

#ifdef __mbedos__
  // Mbed OS platforms use I2C

  Transport_Class::Transport_Class(void)
  {
    this->bus = new I2C(I2C_SDA, I2C_SCL);
    this->addr = DefaultAddress << 1;
    this->ready = nullptr;
  }

  Transport_Class::Transport_Class(I2C *bus, uint8_t addr, PinName ready)
  {
    this->bus = bus;
    this->addr = addr << 1;

    if (ready == NC)
      this->ready = nullptr;
    else
      this->ready = new DigitalIn(ready);
  }

  void Transport_Class::Transaction(SPIAGENT_COMMAND_MSG_t *cmd,
    SPIAGENT_RESPONSE_MSG_t *resp)
  {
    if (this->bus->write(this->addr, (char *) cmd,
        sizeof(SPIAGENT_COMMAND_MSG_t)))
      RaiseError("I2C.write() failed");

    if (this->ready == nullptr)
    {
      // Pause between I2C write and read, to give the LPC1114 time to
      // execute the command
      wait_us((cmd->command == SPIAGENT_CMD_PUT_LEGORC) ? 20000 : 100);
    }
    else
    {
      // Wait a short time to avoid a race condition:
      // (READY deasserted too late)
      wait_us(10);

      // Wait until READY is reasserted
      while (!this->ready->read())
        ThisThread::yield();
    }

    if (this->bus->read(this->addr, (char *) resp,
        sizeof(SPIAGENT_RESPONSE_MSG_t)))
      RaiseError("I2C.read() failed");
  }
#endif

#ifdef ARDUINO
  // Arduino platforms use I2C

  Transport_Class::Transport_Class(void)
  {
  }

  void Transport_Class::Init(uint8_t addr, int ready)
  {
    if (ready >= 0) pinMode(ready, INPUT);

    this->addr  = addr;
    this->ready = ready;

#ifdef I2C_SDA_PIN
    // Override normal SDA PIN
    I2C_BUS.setSDA(I2C_SDA_PIN);
#endif
#ifdef I2C_SCL_PIN
    // Override normal SCL PIN
    I2C_BUS.setSCL(I2C_SCL_PIN);
#endif

    I2C_BUS.begin();
  }

  void Transport_Class::Transaction(SPIAGENT_COMMAND_MSG_t *cmd,
    SPIAGENT_RESPONSE_MSG_t *resp)
  {
    uint8_t *p;
    int len;

    // Send the command message

    p = (uint8_t *) cmd;

    I2C_BUS.beginTransmission(this->addr);

    len = I2C_BUS.write(p, sizeof(SPIAGENT_COMMAND_MSG_t));
    if (len != sizeof(SPIAGENT_COMMAND_MSG_t)) RaiseError("I2C_BUS.write() failed");

    I2C_BUS.endTransmission();

    // Pause between I2C write and read, to give the LPC1114 time to
    // execute the command

    if (this->ready >= 0)
    {
      while (!digitalRead(this->ready));
    }
    else if (cmd->command == SPIAGENT_CMD_PUT_LEGORC)
    {
      delayMicroseconds(10000);
      delayMicroseconds(10000);
    }
    else
      delayMicroseconds(100);

    // Receive the response message

    p = (uint8_t *) resp;
    len = 0;

    I2C_BUS.requestFrom(this->addr, sizeof(SPIAGENT_RESPONSE_MSG_t));

    while (I2C_BUS.available())
    {
      *p++ = I2C_BUS.read();
      len++;
    }

    if (len != sizeof(SPIAGENT_RESPONSE_MSG_t)) RaiseError("I2C_BUS.read() failed");
  }
#endif
}
