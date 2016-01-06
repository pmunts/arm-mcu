(* LED test program for the mbed LPC1768 board *)

(* $Id$ *)

(* Copyright (C)2014-2015, Philip Munts, President, Munts AM Corp.             *)
(*                                                                             *)
(* Redistribution and use in source and binary forms, with or without          *)
(* modification, are permitted provided that the following conditions are met: *)
(*                                                                             *)
(* * Redistributions of source code must retain the above copyright notice,    *)
(*   this list of conditions and the following disclaimer.                     *)
(*                                                                             *)
(* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" *)
(* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   *)
(* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  *)
(* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   *)
(* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         *)
(* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        *)
(* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    *)
(* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     *)
(* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     *)
(* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  *)
(* POSSIBILITY OF SUCH DAMAGE.                                                 *)

MODULE test_leds;

IMPORT
  Main, SYSTEM, Timer, GPIO;

CONST
  LED1_mask = GPIO.Mask50;
  LED2_mask = GPIO.Mask52;
  LED3_mask = GPIO.Mask53;
  LED4_mask = GPIO.Mask55;
  
  LED1_dir  = GPIO.Dir50;
  LED2_dir  = GPIO.Dir52;
  LED3_dir  = GPIO.Dir53;
  LED4_dir  = GPIO.Dir55;

  LED1      = GPIO.Pin50;
  LED2      = GPIO.Pin52;
  LED3      = GPIO.Pin53;
  LED4      = GPIO.Pin55;
  
VAR
  d1 : BOOLEAN;
  d2 : BOOLEAN;
  d3 : BOOLEAN;
  d4 : BOOLEAN;
  
BEGIN

  (* Configure GPIO pins for LED's *)

  SYSTEM.PUT(LED1_mask, GPIO.UNMASKED);
  SYSTEM.PUT(LED2_mask, GPIO.UNMASKED);
  SYSTEM.PUT(LED3_mask, GPIO.UNMASKED);
  SYSTEM.PUT(LED4_mask, GPIO.UNMASKED);
  
  SYSTEM.PUT(LED1_dir, GPIO.OUTPUT);
  SYSTEM.PUT(LED2_dir, GPIO.OUTPUT);
  SYSTEM.PUT(LED3_dir, GPIO.OUTPUT);
  SYSTEM.PUT(LED4_dir, GPIO.OUTPUT);
  
  SYSTEM.PUT(LED1, GPIO.HIGH);
  SYSTEM.PUT(LED2, GPIO.LOW);
  SYSTEM.PUT(LED3, GPIO.LOW);
  SYSTEM.PUT(LED4, GPIO.LOW);

  (* Flash LED's *)

  WHILE TRUE DO
    SYSTEM.GET(LED1, d1);
    SYSTEM.GET(LED2, d2);
    SYSTEM.GET(LED3, d3);
    SYSTEM.GET(LED4, d4);
    
    SYSTEM.PUT(LED1, d4);
    SYSTEM.PUT(LED2, d1);
    SYSTEM.PUT(LED3, d2);
    SYSTEM.PUT(LED4, d3);
    
    Timer.MSecDelay(300);
  END
END test_leds.
