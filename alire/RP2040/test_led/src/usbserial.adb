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

WITH HAL;
WITH RP.Clock;
WITH RP.Device;
WITH USB.Device.Serial;

USE TYPE USB.Device.Init_Result;

PACKAGE BODY USBSerial IS

  CRLF       : CONSTANT String := ASCII.CR & ASCII.LF;

  USB_Serial : aliased USB.Device.Serial.Default_Serial_Class
   (TX_Buffer_Size => 16384,
    RX_Buffer_Size => 16384);

  USB_Stack  : USB.Device.USB_Device_Stack(Max_Classes => 1);

  PROCEDURE Initialize IS

    Status : USB.Device.Init_Result;

  BEGIN
    RP.Device.Timer.Enable;

    if not USB_Stack.Register_Class (USB_Serial'Unchecked_Access) then
      raise Program_Error;
    end if;

    Status := USB_Stack.Initialize
     (Controller      => RP.Device.UDC'Access,
      Manufacturer    => USB.To_USB_String ("Munts Technologies"),
      Product         => USB.To_USB_String ("RP2040 USB Serial Port"),
      Serial_Number   => USB.To_USB_String ("00000000"),
      Max_Packet_Size => 64,
      Vendor_ID       => 16#16D0#,
      Product_ID      => 16#0AFB#);

    if Status /= USB.Device.Ok then
      raise Program_Error;
    end if;

    USB_Stack.Start;

    Delay_Milliseconds(500);
  END Initialize;

  PROCEDURE Delay_Milliseconds(t : Positive) IS

  BEGIN
    FOR i IN 1 .. t LOOP
      USB_Stack.Poll;
      RP.Device.Timer.Delay_Milliseconds(1);      
    END LOOP;
  END Delay_Milliseconds;

  PROCEDURE New_Line IS

  BEGIN
    Put(CRLF);
  END New_Line;

  PROCEDURE Put(c : Character) IS

  BEGIN
    Put("" & c);
  END Put;

  PROCEDURE Put(s : String) IS

    len : HAL.UInt32 := s'Length;

  BEGIN
    USB_Serial.Write(RP.Device.UDC, s, len);
  END Put;

  PROCEDURE Put_Line(s : String) IS

  BEGIN
    Put(s & CRLF);
  END Put_Line;

END USBSerial;
