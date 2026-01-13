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

WITH RP.GPIO;

PACKAGE SparkFun_Pro_Micro_RP2040 IS

  Crystal : CONSTANT := 12_000_000; -- Hz

  -- Left edge (DIP pin order)

  GP0  : RP.GPIO.GPIO_Point := (Pin => 0);
  GP1  : RP.GPIO.GPIO_Point := (Pin => 1);
  GP2  : RP.GPIO.GPIO_Point := (Pin => 2);
  GP3  : RP.GPIO.GPIO_Point := (Pin => 3);
  GP4  : RP.GPIO.GPIO_Point := (Pin => 4);
  GP5  : RP.GPIO.GPIO_Point := (Pin => 5);
  GP6  : RP.GPIO.GPIO_Point := (Pin => 6);
  GP7  : RP.GPIO.GPIO_Point := (Pin => 7);
  GP8  : RP.GPIO.GPIO_Point := (Pin => 8);
  GP9  : RP.GPIO.GPIO_Point := (Pin => 9);

  -- QWIIC connector

  GP16 : RP.GPIO.GPIO_Point := (Pin => 16);  -- aka SDA
  GP17 : RP.GPIO.GPIO_Point := (Pin => 17);  -- aka SCL

  SDA RENAMES GP16;
  SCL RENAMES GP17;

  -- Right edge (DIP pin order)

  GP21 : RP.GPIO.GPIO_Point := (Pin => 21);
  GP23 : RP.GPIO.GPIO_Point := (Pin => 23);
  GP20 : RP.GPIO.GPIO_Point := (Pin => 20);
  GP22 : RP.GPIO.GPIO_Point := (Pin => 22);
  GP26 : RP.GPIO.GPIO_Point := (Pin => 26);  -- aka ADC0
  GP27 : RP.GPIO.GPIO_Point := (Pin => 27);  -- aka ADC1
  GP28 : RP.GPIO.GPIO_Point := (Pin => 28);  -- aka ADC2
  GP29 : RP.GPIO.GPIO_Point := (Pin => 29);  -- aka ADC3

  ADC0 RENAMES GP26;
  ADC1 RENAMES GP27;
  ADC2 RENAMES GP28;
  ADC3 RENAMES GP29;

END SparkFun_Pro_Micro_RP2040;
