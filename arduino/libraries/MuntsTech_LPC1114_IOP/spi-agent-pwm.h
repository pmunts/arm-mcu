/* Declarations for the Raspberry Pi LPC1114 I/O Processor Expansion Board SPI Agent */

// Copyright (C)2013-2018, Philip Munts, President, Munts AM Corp.
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

#ifndef SPI_AGENT_PWM_H
#define SPI_AGENT_PWM_H

// PWM limits

#define LPC1114_PWM_CHANNELS	4

#define LPC1114_PWM_FREQ_MIN	50
#define LPC1114_PWM_FREQ_MAX	50000

#define LPC1114_PWM_DUTY_MIN	0.0
#define LPC1114_PWM_DUTY_MAX	100.0

#define LPC1114_SERVO_MIN	-1.0
#define LPC1114_SERVO_NEUTRAL	0.0
#define LPC1114_SERVO_MAX	1.0

#define LPC1114_MOTOR_SPEED_MIN	-1.0
#define LPC1114_MOTOR_SPEED_MAX	1.0

// LPC1114 I/O Processor GPIO special function pin aliases

#define LPC1114_PWM1		LPC1114_GPIO1
#define LPC1114_PWM2		LPC1114_GPIO2
#define LPC1114_PWM3		LPC1114_GPIO3
#define LPC1114_PWM4		LPC1114_GPIO7

#define IS_PWM(p) (((p >= LPC1114_PWM1) && (p <= LPC1114_PWM3)) || (p == LPC1114_PWM4))

_BEGIN_STD_C

#ifdef __unix__
// Pulse width modulated output services provided by libspiagent

extern void spiagent_pwm_set_frequency(uint32_t freq, int32_t *error);

extern void spiagent_pwm_configure(uint32_t pin, int32_t *error);

extern void spiagent_pwm_put(uint32_t pin, float dutycycle, int32_t *error);

extern void spiagent_servo_configure(uint32_t pin, int32_t *error);

extern void spiagent_servo_put(uint32_t pin, float position, int32_t *error);

extern void spiagent_motor_configure(uint32_t pwmpin, uint32_t dirpin, int32_t *error);

extern void spiagent_motor_put(uint32_t pwmpin, uint32_t dirpin, float speed, int32_t *error);
#endif

_END_STD_C

#endif
