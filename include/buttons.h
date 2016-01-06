/* Abstract services for reading buttons (momentary switches) */

// $Id: leds.h 8475 2015-02-26 11:40:48Z svn $

// Copyright (C)2013-2015, Philip Munts, President, Munts AM Corp.
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

#ifndef _BUTTONS_H
#define _BUTTONS_H

_BEGIN_STD_C

// Button masks (not all are necessarily implemented)

#define BUTTON1_MASK	0x01
#define BUTTON2_MASK	0x02
#define BUTTON3_MASK	0x04
#define BUTTON4_MASK	0x08
#define BUTTON5_MASK	0x10
#define BUTTON6_MASK	0x20
#define BUTTON7_MASK	0x40
#define BUTTON8_MASK	0x80

// Configure the button input pins

void buttons_initialize(void);

// Get button states.  A 1 bit in the result indicates the button is pushed.
// A 0 bit in the result indicates the button is not pushed.

unsigned long int buttons_get(void);

_END_STD_C
#endif
