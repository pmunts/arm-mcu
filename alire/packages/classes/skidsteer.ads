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

GENERIC

  MotorsPerSide : Positive;

PACKAGE SkidSteer IS

  TYPE Motors IS ARRAY (1 .. MotorsPerSide) OF Motor.Output;

  TYPE SkidSteerClass IS NEW Vehicle.ControllerInterface WITH PRIVATE;

  -- Skidsteer vehicle object constructor

  FUNCTION Create
   (LeftMotorDrivers    : Motors;
    RightMotorDrivers   : Motors;
    SteeringSensitivity : Vehicle.Steering := 0.2) RETURN Vehicle.Controller;

  -- Skidsteer vehicle object initializer

  PROCEDURE Initialize
   (self                : OUT SkidSteerClass;
    LeftMotorDrivers    : Motors;
    RightMotorDrivers   : Motors;
    SteeringSensitivity : Vehicle.Steering := 0.2);

  -- Start or change forward or reverse speed

  PROCEDURE Go
   (self : IN OUT SkidSteerClass;
    v    : Motor.Velocity;
    t    : DURATION := 0.0);

  -- Stop forward or reverse motion

  PROCEDURE Stop(self : IN OUT SkidSteerClass);

  -- Execute a turn

  PROCEDURE Turn
   (self : IN OUT SkidSteerClass;
    s    : Vehicle.Steering;
    t    : DURATION);

PRIVATE

  TYPE SkidSteerClass IS NEW Vehicle.ControllerInterface WITH RECORD
    leftmotors  : Motors;
    rightmotors : Motors;
    sens        : Vehicle.Steering;
    velo        : Motor.Velocity;
  END RECORD;

END SkidSteer;
