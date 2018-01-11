// LEGO(R) Power Functions Remote Control transmitter firmware

// Reference "LEGO(R) Power Functions RC Version 1.20"

// Copyright (C)2012-2018, Philip Munts, President, Munts AM Corp.
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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cpu.h>

#define DELIMITERS	" \t\r\n"

// LPC1114FN28 DIP28

#ifdef LPC1114FN28
#define DELAY38KHZ	21
#define IRED_PIN	17	// aka PIO1_5
#define TURN_IRED_ON	gpio_write(IRED_PIN, 1)
#define TURN_IRED_OFF	gpio_write(IRED_PIN, 0)
#endif

// MBED LPC1768 -- http://mbed.org/handbook/mbed-NXP-LPC1768

#ifdef MBED_LPC1768
#define DELAY38KHZ	99
#define IRED_PIN	63		// P1.31 aka DIP20
#define TURN_IRED_ON	gpio_write(IRED_PIN, 1)
#define TURN_IRED_OFF	gpio_write(IRED_PIN, 0)
#define TURN_LED_ON	LEDS_set(1)
#define TURN_LED_OFF	LEDS_set(0)
#endif

// NUCLEO-F103RB -- http://www.st.com/en/evaluation-tools/nucleo-f103rb.html

#ifdef NUCLEO_F103RB
#define DELAY38KHZ	60
#define IRED_PIN	26		// Arduino D6 aka PB10
#define TURN_IRED_ON	gpio_write(IRED_PIN, 1)
#define TURN_IRED_OFF	gpio_write(IRED_PIN, 0)
#define TURN_LED_ON	LEDS_set(1)
#define TURN_LED_OFF	LEDS_set(0)
#endif

// NUCLEO-F411RE -- http://www.st.com/en/evaluation-tools/nucleo-f411re.html

#ifdef NUCLEO_F411RE
#define DELAY38KHZ	98
#define IRED_PIN	26		// Arduino D6 aka PB10
#define TURN_IRED_ON	gpio_write(IRED_PIN, 1)
#define TURN_IRED_OFF	gpio_write(IRED_PIN, 0)
#define TURN_LED_ON	LEDS_set(1)
#define TURN_LED_OFF	LEDS_set(0)
#endif

/**************************************************************************/

#include <legorc.h>

/**************************************************************************/

// Verify input buffer--must be only numeric digits separated by spaces

int numeric(char *s)
{
  while (*s)
  {
    if (!isdigit((int) *s) && (*s != '-') && (*s != ' ') && (*s != '\n'))
      return 0;

    s++;
  }

  return 1;
}

/**************************************************************************/

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);

  // Initialize the console serial port

  serial_stdio(CONSOLE_PORT);

  // Initialize the LED and IRED outputs

  LEDS_initialize();
  gpio_configure(IRED_PIN, GPIO_DIR_OUTPUT);

  TURN_IRED_OFF;

#ifdef TURN_LED_OFF
  TURN_LED_OFF;
#endif

  // Main message handling loop

  for (;;)
  {
    char inbuf[16];
    int channel;
    int motor;
    int speed;

    // Get command string

    memset(inbuf, 0, sizeof(inbuf));
    cgets(inbuf, sizeof(inbuf));

    // Skip if we got any non-numeric characters

    if (!numeric(inbuf)) continue;

    // Convert command parameters from string to binary

    channel = atoi(strtok(inbuf, DELIMITERS));
    motor = atoi(strtok(NULL, DELIMITERS));
    speed = atoi(strtok(NULL, DELIMITERS));

    // Validate parameters

    if ((channel < 1) || (channel > LEGO_RC_CHANNELS)) continue;

    switch (motor)
    {
      case ALLSTOP :			// Panic stop command
        if (speed != 0) continue;
        break;

      case MOTORA :			// Single output mode command
      case MOTORB :
        if (speed < LEGO_RC_MINSPEED) continue;
        if (speed > LEGO_RC_MAXSPEED) continue;
        if (speed < 0) speed += 16;	// Remap reverse speeds
        break;

      case COMBODIRECT :		// Combo direct mode command
        if (speed < 0) continue;
        if (speed > 15) continue;
        break;

      case COMBOPWM :			// Combo PWM mode command
        if (speed < 0) continue;
        if (speed > 255) continue;
        break;

      default :				// Invalid motor ID
        continue;
    }

    // Dispatch the command

    SendCommand(channel, motor, speed, true, NULL);
  }
}
