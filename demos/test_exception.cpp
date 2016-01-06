/* Simple C++ exception test program */

// $Id$

// Copyright (C)2015, Philip Munts, President, Munts AM Corp.
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

static const char revision[] = "$Id$";

#include <iostream>
#include <exception>

using namespace std;

#include <cpu.h>

#define CLEARSCREEN	"\033[H\033[2J"

// Define an exception object

class finger_exception: public exception
{
  virtual const char* what() const throw()
  {
    return "You ran out of fingers!";
  }
} finger_error;

int main(void)
{
  int counter;

  cpu_init(DEFAULT_CPU_FREQ);
  systick_init(100, NULL);
  serial_stdio((char *) CONSOLE_PORT);

// Display startup banner

  cout << CLEARSCREEN; 
  cout << MCUFAMILYNAME;
  cout << " C++ Exception Test ";
  cout << "(" << __DATE__ << " " <<  __TIME__ << ")";
  cout << "\n\n";

  cout << revision;
  cout << "\n\n";

  cout << "Board:    " << BOARDNAME << "\n";
  cout << "CPU Freq: " << SystemCoreClock/1000000 << " MHz\n";
  cout << "Compiler: " << __COMPILER__ << " " << __VERSION__ << " " << __ABI__ << "\n\n";

// Trivial main program

  counter = 1;

  for (;;)
  {
    try
    {
      cout << "Hello, world " << counter << "\n";
      sleep(1);

      counter += 1;
      if (counter > 10) throw finger_error;
    }
    catch(exception& e)
    {
      cout << e.what() << "\n";
      counter = 1;
    }
  }
}
