/* Simple I2C driver services */

// Copyright (C)2015-2016, Philip Munts, President, Munts AM Corp.
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

#ifndef _I2C_H
#define _I2C_H

_BEGIN_STD_C

typedef enum
{
  I2C_PORT1,
  I2C_PORT2,
  I2C_PORT3,
  I2C_PORT4,
  I2C_PORT5,
  I2C_PORT6,
  I2C_PORT7,
  I2C_PORT8
} I2C_PORT_t;

int i2c_slave_init(unsigned port, uint8_t addr);

ssize_t i2c_slave_read(unsigned port, uint8_t *rxbuf, size_t rxsize);

ssize_t i2c_slave_write(unsigned port, uint8_t *txbuf, size_t txsize);

int i2c_master_init(unsigned port);

ssize_t i2c_master_read(unsigned port, uint8_t slaveaddr,
  uint8_t *rxbuf, size_t rxsize);

ssize_t i2c_master_write(unsigned port, uint8_t slaveaddr,
  uint8_t *txbuf, size_t txsize);

int i2c_master_transaction(unsigned port, uint8_t slaveaddr,
  uint8_t *txbuf, size_t txsize, uint8_t *rxbuf, size_t rxsize);

_END_STD_C
#endif
