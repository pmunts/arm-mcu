/* Initialize CPU core */

// $Id$

// Copyright (C)2013-2015, Philip Munts, President, Munts AM Corp.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

static const char revision[] = "$Id$";

#include <cpu.h>

static void ConfigurePLL(void)
{
// Each board will require a highly specific PLL configuration

#ifdef NUCLEO_F103RB
// STM32F103RB with 8 MHz external clock
//   CPU  clock is 72 MHz
//   AHB  clock is 72 MHz
//   APB1 clock is 36 MHz
//   APB2 clock is 72 MHz
//   ADC  clock is 12 MHz

  // Configure flash latency for full speed CPU clock

  do
  {
    FLASH->ACR = 2;		// 2 wait states, prefetch disabled
  }
  while (FLASH->ACR != 2);	// 2 wait states, prefetch disabled

  // Start the HSE

  RCC->CR |= RCC_CR_HSEON|RCC_CR_HSEBYP;
  while (!(RCC->CR & RCC_CR_HSERDY));

  // Configure bus clock dividers

  RCC->CFGR = RCC_CFGR_HPRE_DIV1|RCC_CFGR_PPRE1_DIV2|RCC_CFGR_PPRE2_DIV1|RCC_CFGR_ADCPRE_DIV6;

  // Configure the PLL

  RCC->CFGR |= RCC_CFGR_PLLSRC|RCC_CFGR_PLLXTPRE_HSE|RCC_CFGR_PLLMULL9;

  // Start the PLL

  RCC->CR |= RCC_CR_PLLON;
  while (!(RCC->CR & RCC_CR_PLLRDY));

  // Switch to the PLL

  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // Enable flash prefetch

  do
  {
    FLASH->ACR |= FLASH_ACR_PRFTBE;
  }
  while (!(FLASH->ACR & FLASH_ACR_PRFTBS));
#endif

#ifdef OLIMEX_STM32_P103
// STM32F103RB with 8 MHz crystal
//   CPU  clock is 72 MHz
//   AHB  clock is 72 MHz
//   APB1 clock is 36 MHz
//   APB2 clock is 72 MHz
//   ADC  clock is 12 MHz

  // Configure flash latency for full speed CPU clock

  do
  {
    FLASH->ACR = 2;		// 2 wait states, prefetch disabled
  }
  while (FLASH->ACR != 2);	// 2 wait states, prefetch disabled

  // Start the HSE

  RCC->CR |= RCC_CR_HSEON;
  while (!(RCC->CR & RCC_CR_HSERDY));

  // Configure bus clock dividers

  RCC->CFGR = RCC_CFGR_HPRE_DIV1|RCC_CFGR_PPRE1_DIV2|RCC_CFGR_PPRE2_DIV1|RCC_CFGR_ADCPRE_DIV6;

  // Configure the PLL

  RCC->CFGR |= RCC_CFGR_PLLSRC|RCC_CFGR_PLLXTPRE_HSE|RCC_CFGR_PLLMULL9;

  // Start the PLL

  RCC->CR |= RCC_CR_PLLON;
  while (!(RCC->CR & RCC_CR_PLLRDY));

  // Switch to the PLL

  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // Enable flash prefetch

  do
  {
    FLASH->ACR |= FLASH_ACR_PRFTBE;
  }
  while (!(FLASH->ACR & FLASH_ACR_PRFTBS));
#endif


#ifdef OLIMEX_STM32_P107
// STM32F107RB with 25 MHz crystal
//   CPU  clock is 72 MHz
//   AHB  clock is 72 MHz
//   APB1 clock is 36 MHz
//   APB2 clock is 72 MHz
//   ADC  clock is 12 MHz

  // Configure flash latency for full speed CPU clock

  do
  {
    FLASH->ACR = 2;		// 2 wait states, prefetch disabled
  }
  while (FLASH->ACR != 2);	// 2 wait states, prefetch disabled

  // Start the HSE

  RCC->CR |= RCC_CR_HSEON;
  while (!(RCC->CR & RCC_CR_HSERDY));

  // Configure bus clock dividers

  RCC->CFGR = RCC_CFGR_HPRE_DIV1|RCC_CFGR_PPRE1_DIV2|RCC_CFGR_PPRE2_DIV1|RCC_CFGR_ADCPRE_DIV6;

  // Configure PLL2

  RCC->CFGR2 = RCC_CFGR2_PREDIV1SRC_PLL2|RCC_CFGR2_PLL2MUL8|RCC_CFGR2_PREDIV2_DIV5|RCC_CFGR2_PREDIV1_DIV5;

  // Start PLL2

  RCC->CR |= RCC_CR_PLL2ON;
  while (!(RCC->CR & RCC_CR_PLL2RDY));

  // Configure the PLL

  RCC->CFGR |= RCC_CFGR_PLLMULL9|RCC_CFGR_PLLSRC;

  // Start the PLL

  RCC->CR |= RCC_CR_PLLON;
  while (!(RCC->CR & RCC_CR_PLLRDY));

  // Switch to the PLL

  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // Enable flash prefetch

  do
  {
    FLASH->ACR |= FLASH_ACR_PRFTBE;
  }
  while (!(FLASH->ACR & FLASH_ACR_PRFTBS));
#endif
}

void cpu_init(unsigned long int frequency)
{
  SystemInit();
  ConfigurePLL();
  SystemCoreClockUpdate();
}
