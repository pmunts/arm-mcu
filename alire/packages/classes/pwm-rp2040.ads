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

-- The following specifications are for an RP2040 clocked at 200 MHz.
--
-- This implementation maintains maximum hardware PWM resolution (16 bits,
-- 65536 discrete PWM pulse widths) for frequencies up to 3051 Hz.  PWM pulse
-- frequencies above 3051 Hz are still achievable by reducing the resolution.
--
-- At the PWM pulse frequency of 48,828 Hz, resolution has dropped to 12 bits,
-- 4096 discrete PWM pulse widths.

WITH RP.GPIO;
WITH RP.PWM;

PACKAGE PWM.RP2040 IS

  TYPE OutputSubclass IS NEW PWM.OutputInterface WITH PRIVATE;

  -- Constructor returning PWM.Output

  FUNCTION Create
   (desg      : RP.GPIO.GPIO_Pin;
    frequency : Positive;
    dutycycle : PWM.DutyCycle := PWM.MinimumDutyCycle) RETURN Output;

  -- PWM output object instance initializer

  PROCEDURE Initialize
   (Self      : OUT OutputSubclass;
    desg      : RP.GPIO.GPIO_Pin;
    frequency : Positive;
    dutycycle : PWM.DutyCycle := PWM.MinimumDutyCycle);

  -- Write PWM output duty cycle

  PROCEDURE Put
   (Self      : IN OUT OutputSubclass;
    dutycycle : PWM.DutyCycle);

  -- Convert GPIO_Pin to PWM_Point

  FUNCTION To_Point(desg : RP.GPIO.GPIO_Pin) RETURN RP.PWM.PWM_Point;

PRIVATE

  TYPE OutputSubclass IS NEW PWM.OutputInterface WITH RECORD
    point      : RP.PWM.PWM_Point;
    period     : RP.PWM.Period; -- aka TOP
    configured : Boolean := False;
  END RECORD;

END PWM.RP2040;
