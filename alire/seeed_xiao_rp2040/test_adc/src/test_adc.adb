-- Seeed Studio Xiao RP2040 ADC Test

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

WITH RP.ADC;
WITH RP.Clock;
WITH RP.GPIO;
WITH Seeed_Xiao_RP2040;
WITH USB_Console; USE USB_Console;

PROCEDURE test_adc IS

  A0 : CONSTANT RP.ADC.ADC_Channel :=
    RP.ADC.To_ADC_Channel(Seeed_Xiao_RP2040.A0);

BEGIN
  RP.Clock.Initialize(Seeed_Xiao_RP2040.Crystal);
  RP.GPIO.Enable;
  USB_Console.Initialize;

  New_Line;
  Put_Line("Seeed Studio Xiao RP2040 ADC Test");
  New_Line;

  RP.ADC.Enable;
  RP.ADC.Configure(A0);

  LOOP
    Put_Line(RP.ADC.Read_Microvolts(A0)'Image & " uV");
    Delay_Milliseconds(1000);
  END LOOP;
END test_adc;
