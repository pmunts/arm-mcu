-- Seeed Studio Xiao RP2040 PWM Output Test

-- Copyright (C)2026, Philip Munts dba Munts Technologies.
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

WITH RP.Clock;
WITH PWM.RP2040;
WITH Seeed_Xiao_RP2040;
WITH RP2040_USB_Console; USE RP2040_USB_Console;

PROCEDURE test_pwm IS

  outp : PWM.Output;

BEGIN
  RP.Clock.Initialize(Seeed_Xiao_RP2040.Crystal, SYS_PLL_Config => RP.Clock.PLL_200_MHz);
  RP2040_USB_Console.Initialize;

  New_Line;
  Put_Line("Seeed Studio Xiao RP2040 PWM Output Test");
  New_Line;

  outp := PWM.RP2040.Create(Seeed_Xiao_RP2040.GP2, 1000);

  LOOP
    FOR d IN 0 .. 100 LOOP
      outp.Put(PWM.DutyCycle(d));
      Delay_Milliseconds(50);
    END LOOP;

    FOR d IN REVERSE 0 .. 100 LOOP
      outp.Put(PWM.DutyCycle(d));
      Delay_Milliseconds(50);
    END LOOP;
  END LOOP;
END test_pwm;
