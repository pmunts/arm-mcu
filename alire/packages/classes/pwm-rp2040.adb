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

WITH GPIO.RP2040;
WITH HAL;
WITH RP.Clock;
WITH RP.GPIO;

USE TYPE HAL.UInt16;

PACKAGE BODY PWM.RP2040 IS

  HardwareIsInitialized : Boolean := False;

  -- Constructor returning PWM.Output

  FUNCTION Create
   (desg      : RP.GPIO.GPIO_Pin;
    frequency : Positive;
    dutycycle : PWM.DutyCycle := PWM.MinimumDutyCycle) RETURN Output IS

    self : OutputSubclass;

  BEGIN
    self.Initialize(desg, frequency, dutycycle);
    RETURN NEW OutputSubclass'(self);
  END Create;

  -- PWM output object instance initializer

  PROCEDURE Initialize
   (self      : OUT OutputSubclass;
    desg      : RP.GPIO.GPIO_Pin;
    frequency : Positive;
    dutycycle : PWM.DutyCycle := PWM.MinimumDutyCycle) IS

    gpoint : RP.GPIO.GPIO_Point := GPIO.RP2040.To_Point(desg);

    myDIV : RP.PWM.Divider;
    myTOP : RP.PWM.Period  := 65535;

  BEGIN

    -- Initialize GPIO hardware subsystem, if necessary

    IF NOT HardwareIsInitialized THEN
      RP.GPIO.Enable;
      RP.PWM.Initialize;
      HardwareIsInitialized := True;
    END IF;

    myDIV := RP.PWM.Divider(Float(RP.Clock.Frequency(RP.Clock.SYS))/Float(frequency)/65536.0);

    gpoint.Configure(RP.GPIO.Output, RP.GPIO.Pull_Up, RP.GPIO.PWM);

    self.point  := To_Point(desg);
    RP.PWM.Set_Mode(self.point.Slice, RP.PWM.Free_Running);
    RP.PWM.Set_Phase_Correction(self.point.Slice, False);
    RP.PWM.Set_Divider(self.point.Slice, myDIV);  -- DIV register
    RP.PWM.Set_Interval(self.point.Slice, myTOP); -- TOP register
    RP.PWM.Enable(self.point.Slice);
    self.period     := myTOP;
    self.configured := True;

    self.Put(dutycycle);
  END Initialize;

  -- Write PWM output duty cycle

  PROCEDURE Put
   (self      : IN OUT OutputSubclass;
    dutycycle : PWM.DutyCycle) IS

  BEGIN
    RP.PWM.Set_Duty_Cycle(self.point.Slice, self.point.Channel,
      RP.PWM.Period(Float(dutycycle/100.0)*Float(self.period)));
  END Put;

  -- Convert GPIO_Pin to PWM_Point

  FUNCTION To_Point(desg : RP.GPIO.GPIO_Pin) RETURN RP.PWM.PWM_Point IS

  BEGIN
    RETURN RP.PWM.To_PWM(GPIO.RP2040.To_Point(desg));
  END To_Point;

END PWM.RP2040;
