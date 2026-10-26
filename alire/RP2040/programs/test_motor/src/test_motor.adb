-- Seeed Studio Xiao RP2040 Motor Output Test

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
WITH Motor.PWM;
WITH RP.Clock;
WITH PWM.RP2040;
WITH Seeed_Xiao_RP2040;

PROCEDURE test_motor IS

  VELOCITIES : CONSTANT Integer := 500;

  DIRA : ALIASED GPIO.RP2040.PinSubclass;
  PWMA : ALIASED PWM.RP2040.OutputSubclass;
  MOTA : Motor.Output;

BEGIN
  RP.Clock.Initialize(Seeed_Xiao_RP2040.Crystal, SYS_PLL_Config => RP.Clock.PLL_200_MHz);

  DIRA.Initialize(Seeed_Xiao_RP2040.GP1, GPIO.Output);
  PWMA.Initialize(Seeed_Xiao_RP2040.GP2, 10000);
  MOTA := Motor.PWM.Create(PWMA'Unchecked_Access, DIRA'Unchecked_Access);

  -- Sweep the motor velocity up and down

  FOR v IN Integer RANGE 0 .. VELOCITIES LOOP
    MOTA.Put(Motor.Velocity(Float(v)/Float(VELOCITIES)));
    DELAY 0.05;
  END LOOP;

  FOR v IN REVERSE Integer RANGE -VELOCITIES .. VELOCITIES LOOP
    MOTA.Put(Motor.Velocity(Float(v)/Float(VELOCITIES)));
    DELAY 0.05;
  END LOOP;

  FOR v IN Integer RANGE -VELOCITIES .. 0 LOOP
    MOTA.Put(Motor.Velocity(Float(v)/Float(VELOCITIES)));
    DELAY 0.05;
  END LOOP;
END test_motor;
