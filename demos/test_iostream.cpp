/* Simple C++ iostream test program */

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
#include <string>
#include <cctype>

using namespace std;

#include <assert.h>
#include <cpu.h>

#define CLEARSCREEN "\033[H\033[2J"

int main(void)
{
  string inbuf;
  int x, y;

  cpu_init(DEFAULT_CPU_FREQ);
  serial_stdio((char *) CONSOLE_PORT);

  cout << CLEARSCREEN; 
  cout << MCUFAMILYNAME;
  cout << " C++ iostream Test ";
  cout << "(" << __DATE__ << " " <<  __TIME__ << ")";
  cout << "\n\n";

  cout << revision;
  cout << "\n\n";

  cout << "Board:    " << BOARDNAME << "\n";
  cout << "CPU Freq: " << SystemCoreClock/1000000 << " MHz\n";
  cout << "Compiler: " << __COMPILER__ << " " << __VERSION__ << " " << __ABI__ << "\n\n";

  for (;;)
  {
    cout << "Enter a line of text:  " << flush;
    getline(cin, inbuf);

    cout << "You entered:           " << inbuf << " (" << inbuf.length() << " bytes)\n";

    if (!inbuf.compare("next")) break;
  }

  cout << "Enter some more text:  " << flush;

  for (;;)
  {
    cin >> inbuf;

    cout << "You entered:           " << inbuf << " (" << inbuf.length() << " bytes)\n";

    if (!inbuf.compare("next")) break;
  }

  for (;;)
  {
    cout << "Enter two numbers:     " << flush;

    cin >> x;
    cin >> y;

    cout << "You entered:           " << x << " and " << y << endl;

    if ((x == 0) && (y == 0)) break;    
  }

  assert(false);
}
