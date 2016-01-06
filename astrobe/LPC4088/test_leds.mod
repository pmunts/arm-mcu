(* LED test program for the Embedded Artists LPC4088 Quick Start board *)

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
  LED2_mask = GPIO.Mask13;
  LED3_mask = GPIO.Mask45;
  LED4_mask = GPIO.Mask83;
  SW2_mask  = GPIO.Mask74;

  LED1_dir  = GPIO.Dir50;
  LED2_dir  = GPIO.Dir13;
  LED3_dir  = GPIO.Dir45;
  LED4_dir  = GPIO.Dir83;
  SW2_dir   = GPIO.Dir74;
  
  LED1      = GPIO.Pin50;
  LED2      = GPIO.Pin13;
  LED3      = GPIO.Pin45;
  LED4      = GPIO.Pin83;
  SW2       = GPIO.Pin74;
  
VAR
  d1 : BOOLEAN;
  d2 : BOOLEAN;
  d3 : BOOLEAN;
  d4 : BOOLEAN;
  s2 : BOOLEAN;
  
BEGIN
  SYSTEM.PUT(LED1_mask, GPIO.UNMASKED);
  SYSTEM.PUT(LED2_mask, GPIO.UNMASKED);
  SYSTEM.PUT(LED3_mask, GPIO.UNMASKED);
  SYSTEM.PUT(LED4_mask, GPIO.UNMASKED);
  SYSTEM.PUT(SW2_mask, GPIO.UNMASKED);
  
  SYSTEM.PUT(LED1_dir, GPIO.OUTPUT);
  SYSTEM.PUT(LED2_dir, GPIO.OUTPUT);
  SYSTEM.PUT(LED3_dir, GPIO.OUTPUT);
  SYSTEM.PUT(LED4_dir, GPIO.OUTPUT);
  SYSTEM.PUT(SW2_dir, GPIO.INPUT);
  
  SYSTEM.PUT(LED1, GPIO.LOW);  (* Active low *)
  SYSTEM.PUT(LED2, GPIO.HIGH); (* Active low *)
  SYSTEM.PUT(LED3, GPIO.LOW);  (* Active high *)
  SYSTEM.PUT(LED4, GPIO.LOW);  (* Active high *)

  WHILE TRUE DO
    SYSTEM.GET(LED1, d1);
    SYSTEM.GET(LED2, d2);
    SYSTEM.GET(LED3, d3);
    SYSTEM.GET(LED4, d4);
    SYSTEM.GET(SW2, s2);
    
    SYSTEM.PUT(LED1, ~d3);
    SYSTEM.PUT(LED2, d1);
    SYSTEM.PUT(LED4, ~d2);
    SYSTEM.PUT(LED3, d4);
    
    IF s2 THEN
      Timer.MSecDelay(100)
    ELSE
      Timer.MSecDelay(50);
    END  
  END
END test_leds.
