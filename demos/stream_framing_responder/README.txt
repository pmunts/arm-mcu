                   Byte Stream Framing Responder Demo Program

   This program demonstrates how to write a [1]FreeRTOS program that
   accepts and responds to stream framed commands on a serial port.

Supported Targets

     * [2]Nucleo-F103RB using USART3. If you wire wrap CN7 pin 1 to CN10
       pin 35 and CN7 pin 2 to CN10 pin 37 on the bottom of the board,
       then USART3 will be connected to the Arduino expansion header pins
       D0 and D1.
     * [3]Nucleo-F411RE using USART6. If you wire wrap CN10 pin 14 to CN10
       pin 35 and CN10 pin 12 to CN10 pin 37 on the bottom of the board,
       then USART6 will be connected to the Arduino expansion header pins
       D0 and D1.

   Other targets can be supported by defining the macros CONTROLPORT and
   CONTROLPORTNAME to select the serial port to receive commands on.

WiFi Test Setup

    1. Wire wrap the Arduino expansion serial port pins as described
       above.
    2. Install an [4]ESP8266 Shield flashed with [5]ESP-LINK firmware into
       the Arduino expansion headers.
    3. Configure the ESP-LINK firmware, following these [6]instructions.
       The bridged serial port should be configured for 115200 baud.
    4. Compile the client test program with make client.
    5. Run the client test program with ./client <hostname<>.

Copyright:

   Original works herein are copyrighted as follows:

Copyright (C)2016, Philip Munts, President, Munts AM Corp.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

   Redistributed works herein are copyrighted and/or licensed by their
   respective authors.
   ___________________________________________________________________

   Questions or comments to Philip Munts [7]phil@munts.net

   I am available for custom system development (hardware and software) of
   products using ARM or other microcontrollers.

References

   1. http://www.freertos.org/
   2. http://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-mcu-nucleo/nucleo-f103rb.html
   3. http://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-mcu-nucleo/nucleo-f411re.html
   4. https://www.sparkfun.com/products/13287
   5. https://github.com/jeelabs/esp-link
   6. https://github.com/jeelabs/esp-link#configuration-details
   7. mailto:phil@munts.net
