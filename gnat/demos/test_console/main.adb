-- Serial console test

-- $Id$

-- Copyright (C)2015, Philip Munts, President, Munts AM Corp.
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions are met:
--
-- * Redistributions of source code must retain the above copyright notice,
--   this list of conditions and the following disclaimer.
--
-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
-- AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
-- IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
-- ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
-- LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
-- CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
-- SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
-- INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
-- CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
-- ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
-- POSSIBILITY OF SUCH DAMAGE.

with Ada.Real_Time;
use Ada.Real_Time;

with Ada.Text_IO;
use Ada.Text_IO;

with BSP;

procedure Main is

  ClearScreen : constant String := ASCII.ESC & "[H" & ASCII.ESC & "[J";  -- VT100 clear screen
  fingers : constant Natural := 10;
  counter : Natural range 1 .. fingers;

begin
  put(ClearScreen);
  put("Serial console test for " & BSP.boardname);
  new_line;
  new_line;

  counter := 1;

  loop
    begin
      put("Hello, world");
      put_line(Natural'image(counter));

      delay until Clock + Milliseconds(1000);
      counter := counter + 1;

    exception
      when CONSTRAINT_ERROR =>
        put_line("You ran out of fingers!");
        counter := 1;
    end;
  end loop;
end Main;
