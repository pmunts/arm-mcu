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

PACKAGE BODY GPIO.RP2040 IS

  -- Constructor returning GPIO.Pin

  FUNCTION Create
   (desg       : RP.GPIO.GPIO_Pin;
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
   (self       : IN OUT PinSubclass;
    desg       : RP.GPIO.GPIO_Pin;
    mode       : RP.GPIO.GPIO_Config_Mode;
    state      : Boolean                := False;
    pull       : RP.GPIO.GPIO_Pull_Mode := RP.GPIO.Floating;
    drive      : RP.GPIO.GPIO_Drive     := RP.GPIO.Drive_4ma;
    hysteresis : Boolean                := False;
    fast_slew  : Boolean                := False) IS

  BEGIN
    self.Initialize(RP.GPIO.GPIO_Point'(Pin => desg), mode, state, pull,
      drive, hysteresis, fast_slew);
  END Initialize;

  -- GPIO pin object instance initializer

  PROCEDURE Initialize
   (self       : IN OUT PinSubclass;
    desg       : RP.GPIO.GPIO_Point;
    mode       : RP.GPIO.GPIO_Config_Mode;
    state      : Boolean                := False;
    pull       : RP.GPIO.GPIO_Pull_Mode := RP.GPIO.Floating;
    drive      : RP.GPIO.GPIO_Drive     := RP.GPIO.Drive_4ma;
    hysteresis : Boolean                := False;
    fast_slew  : Boolean                := False) IS

  BEGIN
    self.Destroy;

    CASE mode IS
      WHEN RP.GPIO.Input  => self.kind := KindInput;
      WHEN RP.GPIO.Output => self.kind := KindOutput;
      WHEN OTHERS         => RAISE Error WITH "Illegal mode value";
    END CASE;

    self.point := desg;
    self.point.Configure(mode, pull, RP.GPIO.SIO, hysteresis, fast_slew, drive);

    IF self.kind = KindOutput THEN
      self.Put(state);
    END IF;
  END Initialize;

  -- GPIO pin object instance destroyer

  PROCEDURE Destroy(self : IN OUT PinSubclass) IS

  BEGIN
    self.kind := KindUnconfigured;
  END Destroy;

  -- Read GPIO pin state

  FUNCTION Get(self : IN OUT PinSubclass) RETURN Boolean IS

  BEGIN
    self.CheckDestroyed;

    IF self.kind = KindInput THEN
      RETURN self.point.Get;
    ELSE
      RETURN self.point.Set;
    END IF;
  END Get;

  -- Write GPIO pin state

  PROCEDURE Put(self : IN OUT PinSubclass; state : Boolean) IS

  BEGIN
    self.CheckDestroyed;

    IF self.kind = KindInput THEN
      RAISE Error WITH "Cannot write to an input pin";
    END IF;

    IF state THEN
      self.point.Set;
    ELSE
      self.point.Clear;
    END IF;
  END Put;

  -- Check whether GPIO pin object has been destroyed

  PROCEDURE CheckDestroyed(self : PinSubclass) IS

  BEGIN
    IF self.kind = KindUnconfigured THEN
      RAISE GPIO.Error WITH "GPIO pin has been destroyed";
    END IF;
  END CheckDestroyed;

END GPIO.RP2040;
