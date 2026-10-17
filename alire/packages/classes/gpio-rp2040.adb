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

USE TYPE RP.GPIO.GPIO_Config_Mode;

PACKAGE BODY GPIO.RP2040 IS

  HardwareIsInitialized : Boolean := False;

  -- Constructor returning GPIO.Pin

  FUNCTION Create
   (desg       : RP.GPIO.GPIO_Point;
    mode       : RP.GPIO.GPIO_Config_Mode;
    state      : Boolean                := False;
    pull       : RP.GPIO.GPIO_Pull_Mode := RP.GPIO.Floating;
    drive      : RP.GPIO.GPIO_Drive     := RP.GPIO.Drive_4ma;
    hysteresis : Boolean                := False;
    fast_slew  : Boolean                := False) RETURN Pin IS

    self : PinSubclass;

  BEGIN
    self.Initialize(desg, mode, state, pull, drive, hysteresis, fast_slew);
    RETURN NEW PinSubclass'(self);
  END Create;

  -- GPIO pin object instance initializer

  PROCEDURE Initialize
   (self       : OUT PinSubclass;
    desg       : RP.GPIO.GPIO_Point;
    mode       : RP.GPIO.GPIO_Config_Mode;
    state      : Boolean                := False;
    pull       : RP.GPIO.GPIO_Pull_Mode := RP.GPIO.Floating;
    drive      : RP.GPIO.GPIO_Drive     := RP.GPIO.Drive_4ma;
    hysteresis : Boolean                := False;
    fast_slew  : Boolean                := False) IS

  BEGIN
    CASE mode IS
      WHEN RP.GPIO.Input  => self.dir := GPIO.Input;
      WHEN RP.GPIO.Output => self.dir := GPIO.Output;
      WHEN OTHERS         => RAISE Error WITH "Illegal mode value";
    END CASE;

    -- Initialize GPIO hardware subsystem, if necessary

    IF NOT HardwareIsInitialized THEN
      RP.GPIO.Enable;
      HardwareIsInitialized := True;
    END IF;

    -- Configure the GPIO pin

    self.point      := desg;
    self.point.Configure(mode, pull, RP.GPIO.SIO, hysteresis, fast_slew, drive);
    self.configured := True;

    IF self.dir = GPIO.Output THEN
      self.Put(state);
    END IF;
  END Initialize;

  -- Read state from GPIO input pin

  FUNCTION Get(self : IN OUT PinSubclass) RETURN Boolean IS

  BEGIN
    IF NOT self.configured THEN
      RAISE Error WITH "Cannot read from unconfigured GPIO pin";
    END IF;

    CASE self.dir IS
      WHEN GPIO.Input =>
        RETURN self.point.Get;

      WHEN GPIO.Output =>
        RETURN self.point.Set;
    END CASE;
  END Get;

  -- Write state to GPIO output pin

  PROCEDURE Put(self : IN OUT PinSubclass; state : Boolean) IS

  BEGIN
    IF NOT self.configured THEN
      RAISE Error WITH "Cannot read from unconfigured GPIO pin";
    END IF;

    CASE self.dir IS
      WHEN GPIO.Input =>
        RAISE Error WITH "Cannot write to GPIO input pin";

      WHEN GPIO.Output =>
        IF state THEN
          self.point.Set;
        ELSE
          self.point.Clear;
        END IF;
    END CASE;
  END Put;

  -- Convert GPIO_Pin (number) to GPIO_Point (record)

  FUNCTION To_Point(desg: RP.GPIO.GPIO_Pin) RETURN RP.GPIO.GPIO_Point IS

  BEGIN
    RETURN RP.GPIO.GPIO_Point'(Pin => desg);
  END To_Point;

END GPIO.RP2040;
