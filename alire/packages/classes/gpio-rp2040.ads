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

PACKAGE GPIO.RP2040 IS

  TYPE PinSubclass IS NEW GPIO.PinInterface WITH PRIVATE;

  -- Constructor returning GPIO.Pin

  FUNCTION Create
   (desg       : RP.GPIO.GPIO_Pin;
    mode       : RP.GPIO.GPIO_Config_Mode;
    state      : Boolean                := False;
    pull       : RP.GPIO.GPIO_Pull_Mode := RP.GPIO.Floating;
    drive      : RP.GPIO.GPIO_Drive     := RP.GPIO.Drive_4ma;
    hysteresis : Boolean                := False;
    fast_slew  : Boolean                := False) RETURN Pin;

  -- Constructor returning GPIO.Pin

  FUNCTION Create
   (desg       : RP.GPIO.GPIO_Point;
    mode       : RP.GPIO.GPIO_Config_Mode;
    state      : Boolean                := False;
    pull       : RP.GPIO.GPIO_Pull_Mode := RP.GPIO.Floating;
    drive      : RP.GPIO.GPIO_Drive     := RP.GPIO.Drive_4ma;
    hysteresis : Boolean                := False;
    fast_slew  : Boolean                := False) RETURN Pin;

  -- GPIO pin object instance initializer

  PROCEDURE Initialize
   (self       : IN OUT PinSubclass;
    desg       : RP.GPIO.GPIO_Pin;
    mode       : RP.GPIO.GPIO_Config_Mode;
    state      : Boolean                := False;
    pull       : RP.GPIO.GPIO_Pull_Mode := RP.GPIO.Floating;
    drive      : RP.GPIO.GPIO_Drive     := RP.GPIO.Drive_4ma;
    hysteresis : Boolean                := False;
    fast_slew  : Boolean                := False);

  -- GPIO pin object instance initializer

  PROCEDURE Initialize
   (self       : IN OUT PinSubclass;
    desg       : RP.GPIO.GPIO_Point;
    mode       : RP.GPIO.GPIO_Config_Mode;
    state      : Boolean                := False;
    pull       : RP.GPIO.GPIO_Pull_Mode := RP.GPIO.Floating;
    drive      : RP.GPIO.GPIO_Drive     := RP.GPIO.Drive_4ma;
    hysteresis : Boolean                := False;
    fast_slew  : Boolean                := False);

  -- GPIO pin object instance destroyer

  PROCEDURE Destroy(self : IN OUT PinSubclass);

  -- Read GPIO pin state

  FUNCTION Get(Self : IN OUT PinSubclass) RETURN Boolean;

  -- Write GPIO pin state

  PROCEDURE Put(Self : IN OUT PinSubclass; state : Boolean);

PRIVATE

  -- Check whether GPIO pin object has been destroyed

  PROCEDURE CheckDestroyed(Self : PinSubclass);

  TYPE Kinds IS (input, output, unconfigured);

  TYPE PinSubclass IS NEW GPIO.PinInterface WITH RECORD
    point : RP.GPIO.GPIO_Point := (Pin => 0);
    kind  : Kinds              := unconfigured;
  END RECORD;

END GPIO.RP2040;
