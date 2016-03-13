/* ARM microcontroller device specific definitions and header files */

// Copyright (C)2012-2016, Philip Munts, President, Munts AM Corp.
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

#ifndef _CPU_H
#define _CPU_H

#include <arm.h>
#include <buttons.h>
#include <device.h>
#include <gpiopins.h>
#include <leds.h>
#include <serial.h>
#include <systick.h>

#include <em_acmp.h>
#include <em_adc.h>
#include <em_aes.h>
#include <em_assert.h>
#include <em_bitband.h>
#include <em_burtc.h>
#include <em_chip.h>
#include <em_cmu.h>
#include <em_common.h>
#include <em_dac.h>
#include <em_dbg.h>
#include <em_dma.h>
#include <em_ebi.h>
#include <em_emu.h>
#include <em_gpio.h>
#include <em_i2c.h>
#include <em_idac.h>
#include <em_int.h>
#include <em_lcd.h>
#include <em_lesense.h>
#include <em_letimer.h>
#include <em_leuart.h>
#include <em_mpu.h>
#include <em_msc.h>
#include <em_opamp.h>
#include <em_part.h>
#include <em_pcnt.h>
#include <em_prs.h>
#include <em_rmu.h>
#include <em_rtc.h>
#include <em_system.h>
#include <em_timer.h>
#include <em_usart.h>
#include <em_vcmp.h>
#include <em_version.h>
#include <em_wdog.h>

#define DEFAULT_CPU_FREQ	0

_BEGIN_STD_C

extern void cpu_init(unsigned long int frequency);

_END_STD_C
#endif
