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

WITH Motor;
WITH Vehicle;

USE TYPE Motor.Velocity;
USE TYPE Vehicle.Steering;

PACKAGE BODY SkidSteer IS

  -- Skidsteer vehicle object constructor

  FUNCTION Create
   (LeftMotorDrivers    : Motors;
    RightMotorDrivers   : Motors;
    SteeringSensitivity : Vehicle.Steering := 0.2) RETURN Vehicle.Controller IS

  BEGIN
    RETURN NEW SkidSteerClass'(LeftMotorDrivers, RightMotorDrivers,
      SteeringSensitivity, 0.0);
  END Create;

  -- Skidsteer vehicle object initializer

  PROCEDURE Initialize
   (self                : OUT SkidSteerClass;
    LeftMotorDrivers    : Motors;
    RightMotorDrivers   : Motors;
    SteeringSensitivity : Vehicle.Steering := 0.2) IS

  BEGIN
    self.LeftMotors  := LeftMotorDrivers;
    self.RightMotors := RightMotorDrivers;
    self.sens  := SteeringSensitivity;
    self.velo  := Vehicle.SPEED_STOP;
  END Initialize;

  -- Start or change forward or reverse speed

  PROCEDURE Go
   (self : IN OUT SkidSteerClass;
    v    : Motor.Velocity;
    t    : DURATION := 0.0) IS

  BEGIN
    FOR m OF self.LeftMotors LOOP
      m.Put(v);
    END LOOP;

    FOR m OF self.RightMotors LOOP
      m.Put(v);
    END LOOP;

    self.velo := v;
    DELAY t;
  END Go;

  -- Stop forward or reverse motion

  PROCEDURE Stop(self : IN OUT SkidSteerClass) IS

  BEGIN
    self.Go(Vehicle.SPEED_STOP);
  END Stop;

  -- Execute a turn

  PROCEDURE Turn
   (self : IN OUT SkidSteerClass;
    s    : Vehicle.Steering;
    t    : DURATION) IS

  BEGIN
    IF s = Vehicle.STEER_NONE THEN
      -- No turn, so just keep moving
      RETURN;
    ELSIF self.velo > Vehicle.SPEED_STOP THEN
      -- Moving forward
      FOR m OF self.LeftMotors LOOP
        m.Put(self.velo*Motor.Velocity(1.0 - self.sens) +
          Motor.Velocity(s*self.sens));
      END LOOP;

      FOR m OF self.RightMotors LOOP
        m.Put(self.velo*Motor.Velocity(1.0 - self.sens) -
          Motor.Velocity(s*self.sens));
      END LOOP;
    ELSIF self.velo < Vehicle.SPEED_STOP THEN
      -- Moving reverse
      FOR m OF self.LeftMotors LOOP
        m.Put (self.velo*Motor.Velocity(1.0 - self.sens) -
          Motor.Velocity(s*self.sens));
      END LOOP;

      FOR m OF self.RightMotors LOOP
        m.Put(self.velo*Motor.Velocity(1.0 - self.sens) +
          Motor.Velocity(s*self.sens));
      END LOOP;
    ELSE
      -- Stopped, so just spin in place
      FOR m OF self.LeftMotors LOOP
        m.Put(Motor.Velocity(s));
      END LOOP;

      FOR m OF self.RightMotors LOOP
        m.Put(Motor.Velocity(-s));
      END LOOP;
    END IF;

    DELAY t;

    -- Resume forward or reverse motion
    self.Go(self.velo);
  END Turn;
END SkidSteer;
