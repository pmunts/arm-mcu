// LEGO(R) Power Functions Remote Control transmitter protocol

// Reference the specification "LEGO(R) Power Functions RC Version 1.20"

// Copyright (C)2017, Philip Munts, President, Munts AM Corp.
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

// The following macros must be defined BEFORE including this file:
//
// TURN_LED_ON		Code fragment or function call
// TURN_LED_OFF		Code fragment or function call
// TURN_IRED_ON		Code fragment or function call
// TURN_IRED_OFF	Code fragment or function call
// DELAY38KHZ		Integer constant

#ifndef _LEGORC_H
#define _LEGORC_H

#include <stdint.h>

// LEGO Power Functions RC system constants

#define LEGO_RC_CHANNELS	4
#define LEGO_RC_MINSPEED	-7
#define LEGO_RC_MAXSPEED	7
#define LEGO_RC_REPETITIONS	5

// Motor identifiers

typedef enum
{
  ALLSTOP,
  MOTORA,
  MOTORB,
  COMBODIRECT,
  COMBOPWM,
  MOTOR_ID_SENTINEL
} motor_id_t;

// Protocol timing encoding follows

typedef enum { BIT_LOW, BIT_HIGH, BIT_START, BIT_STOP } lego_bit_t;

// 38 kHz half-cycles of silence following the mark burst

const uint8_t LEGO_RC_PAUSE[] = { 2*(16-6), 2*(27-6), 2*(45-6), 2*(45-6) };

// Milliseconds delay before each frame transmission

const uint8_t LEGO_RC_SPACING[LEGO_RC_CHANNELS][LEGO_RC_REPETITIONS] =
{
  { 3*16, 5*16, 5*16, (6+2*1)*16, (6+2*1)*16 },
  { 2*16, 5*16, 5*16, (6+2*2)*16, (6+2*2)*16 },
  { 1*16, 5*16, 5*16, (6+2*3)*16, (6+2*3)*16 },
  { 0*16, 5*16, 5*16, (6+2*4)*16, (6+2*4)*16 }
};

/**************************************************************************/

// This delay function determines all of the LEGO RC protocol timing

void Delay38kHz(void)
{
  volatile uint8_t i;

  for (i = 0; i < DELAY38KHZ; i++);
}

/**************************************************************************/

// Delay for the specified number of milliseconds

void msleep(uint8_t milliseconds)
{
  uint8_t i;
  uint8_t j;

  for (i = 0; i < milliseconds; i++)
    for (j = 0; j < 38; j++)
      Delay38kHz();
}

/**************************************************************************/

// Send 1 bit

void SendBit(lego_bit_t bit)
{
  uint8_t i;

// Send mark burst, 6 cycles of 38 kHz square wave

  for (i = 1; i <= 6; i++)
  {
    TURN_IRED_ON;
    Delay38kHz();

    TURN_IRED_OFF;
    Delay38kHz();
  }

// Pause n half-cycles

  for (i = 1; i <= LEGO_RC_PAUSE[bit]; i++)
    Delay38kHz();
}

/**************************************************************************/

// Send 16-bit frame

void SendFrame(uint8_t channel, uint16_t frame)
{
  uint8_t i;
  uint8_t j;

// Send the complete frame

  for (i = 0; i < LEGO_RC_REPETITIONS; i++)
  {
    msleep(LEGO_RC_SPACING[channel][i]);

    SendBit(BIT_START);

    for (j = 0; j < 16; j++)
    {
      SendBit((frame >> 15) & 0x01);
      frame <<= 1;
    }

    SendBit(BIT_STOP);
  }
}

/**************************************************************************/

// Set an individual motor speed

void SendCommand(uint8_t channel, uint8_t motor, uint8_t speed)
{
  uint16_t frame;
  uint8_t LRC;

// Build the command frame

  frame = (channel-1)*256;

  switch (motor)
  {
    case ALLSTOP :
      frame |= 0x01F;	// Combo direct, both motors, brake then float
      break;

    case MOTORA :
    case MOTORB :
      frame |= 0x040;	// Single output PWM mode
      frame |= (motor - 1) << 4;
      frame |= speed;
      break;

    case COMBODIRECT :
      frame |= 0x010;	// Combo direct mode
      frame |= speed;
      break;

    case COMBOPWM :
      frame |= 0x400;	// Combo PWM mode
      frame |= speed;
      break;

    default :		// Invalid motor ID
      return;
  }

// Calculate LRC (Longitudinal Redundancy Check)

  LRC = (0xF ^ ((frame >> 8) & 0x0F) ^ ((frame >> 4) & 0x0F) ^
    (frame & 0x0F)) & 0x0F;

// Append LRC

  frame <<= 4;
  frame &= 0xFFF0;
  frame |= LRC;

// Transmit the command frame

  TURN_LED_ON;

  SendFrame(channel, frame);

  TURN_LED_OFF;
}

#endif
