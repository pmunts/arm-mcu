// ARM Mbed OS Tasking Test

// Copyright (C)2019, Philip Munts, President, Munts AM Corp.
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

#include <mbed.h>

Serial console(SERIAL_TX, SERIAL_RX);

// Finite duration task -- periodically display "Hello, World"

static void TaskHello(void)
{
  unsigned i;

  for (i = 0; i < 10; i++)
  {
    console.printf("Hello, World\r\n");
    ThisThread::sleep_for(2000);
  }
}

// Infinite duration task -- flash an LED

static void TaskBlink(void)
{
  DigitalOut led(LED1, false);

  for (;;)
  {
    led = !led;
    ThisThread::sleep_for(300);
  }
}

int main(void)
{
  console.baud(115200);
  console.printf("\033[H\033[2J%s Tasking Test (" __DATE__ " " __TIME__
    ")\r\n\n", BOARDNAME);
  console.printf("Project:    %s\r\n", PROJECTNAME);
  console.printf("Board:      %s\r\n", BOARDNAME);
  console.printf("OS:         ARM Mbed OS %d.%d.%d\r\n", MBED_MAJOR_VERSION,
    MBED_MINOR_VERSION, MBED_PATCH_VERSION);
  console.printf("Tool chain: %s\r\n", TOOLCHAINNAME);
  console.printf("Compiler:   %s\r\n", __VERSION__);
  console.printf("Target:     %s\r\n", TARGETNAME);
  console.printf("CPU Freq:   %1.1f MHz\r\n\n", SystemCoreClock/1000000.0);

  // Start some subtasks

  Thread hello;
  Thread blink;

  hello.start(TaskHello);
  blink.start(TaskBlink);

  // Wait for finite duration substasks to finish

  hello.join();
  console.printf("DEBUG: TaskHello() has terminated.\r\n");

  // Terminate infinite duration subtasks and wait for them to finish

  blink.terminate();
  blink.join();
  console.printf("DEBUG: TaskBlink() has terminated.\r\n");

  console.printf("END OF PROGRAM\r\n");
}
