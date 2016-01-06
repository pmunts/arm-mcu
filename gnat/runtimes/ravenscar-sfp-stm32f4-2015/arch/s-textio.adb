------------------------------------------------------------------------------
--                                                                          --
--                         GNAT RUN-TIME COMPONENTS                         --
--                                                                          --
--                       S Y S T E M . T E X T _ I O                        --
--                                                                          --
--                                 B o d y                                  --
--                                                                          --
--          Copyright (C) 1992-2015, Free Software Foundation, Inc.         --
--                                                                          --
-- GNAT is free software;  you can  redistribute it  and/or modify it under --
-- terms of the  GNU General Public License as published  by the Free Soft- --
-- ware  Foundation;  either version 3,  or (at your option) any later ver- --
-- sion.  GNAT is distributed in the hope that it will be useful, but WITH- --
-- OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY --
-- or FITNESS FOR A PARTICULAR PURPOSE.                                     --
--                                                                          --
--                                                                          --
--                                                                          --
--                                                                          --
--                                                                          --
-- You should have received a copy of the GNU General Public License and    --
-- a copy of the GCC Runtime Library Exception along with this program;     --
-- see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see    --
-- <http://www.gnu.org/licenses/>.                                          --
--                                                                          --
-- GNAT was originally developed  by the GNAT team at  New York University. --
-- Extensive contributions were provided by Ada Core Technologies Inc.      --
--                                                                          --
------------------------------------------------------------------------------

--  Minimal version of Text_IO body for use on STM32F4xxx, using USART2

with Interfaces; use Interfaces;

with System.STM32F4;       use System.STM32F4;
with System.STM32F4.RCC;   use System.STM32F4.RCC;
with System.BB.Parameters;

package body System.Text_IO is

   Baudrate : constant := 115_200;
   --  Bitrate to use

   TX_Ready : constant := 2**6;
   RX_Ready : constant := 2**5;
   --  SR bits definition

   ---------
   -- Get --
   ---------

   function Get return Character is (Character'Val (USART2.DR and 16#FF#));

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize is
      use GPIO;
      use System.BB.Parameters;

      APB_Clock    : constant Positive := Positive (RCC.System_Clocks.PCLK1);
      Int_Divider  : constant Positive := (25 * APB_Clock) / (4 * Baudrate);
      Frac_Divider : constant Natural := Int_Divider rem 100;
      BRR          : Bits_16;

   begin
      Initialized := True;

      RCC.Registers.APB1ENR := RCC.Registers.APB1ENR or RCC_APB1ENR_USART2;
      RCC.Registers.AHB1ENR := RCC.Registers.AHB1ENR or RCC_AHB1ENR_GPIOA;

      GPIOA.MODER   (2 .. 3) := (Mode_AF,     Mode_AF);
      GPIOA.OSPEEDR (2 .. 3) := (Speed_50MHz, Speed_50MHz);
      GPIOA.OTYPER  (2 .. 3) := (Type_PP,     Type_PP);
      GPIOA.PUPDR   (2 .. 3) := (Pull_Up,     Pull_Up);
      GPIOA.AFRL    (2 .. 3) := (AF_USART2,   AF_USART2);

      BRR := (Bits_16 (Frac_Divider * 16) + 50) / 100 mod 16
               or Bits_16 (Int_Divider / 100 * 16);

      USART2.BRR := BRR;
      USART2.CR1 := USART.CR1_UE or USART.CR1_RE or USART.CR1_TE;
      USART2.CR2 := 0;
      USART2.CR3 := 0;
   end Initialize;

   -----------------
   -- Is_Tx_Ready --
   -----------------

   function Is_Tx_Ready return Boolean is ((USART2.SR and TX_Ready) /= 0);

   -----------------
   -- Is_Rx_Ready --
   -----------------

   function Is_Rx_Ready return Boolean is ((USART2.SR and RX_Ready) /= 0);

   ---------
   -- Put --
   ---------

   procedure Put (C : Character) is
   begin
      USART2.DR := Character'Pos (C);
   end Put;

   ----------------------------
   -- Use_Cr_Lf_For_New_Line --
   ----------------------------

   function Use_Cr_Lf_For_New_Line return Boolean is (True);
end System.Text_IO;
