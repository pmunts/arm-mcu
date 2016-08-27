// NUCLEO-F103RB Thermometer, using Mikrolektronika Click Boards

// The board stack (bottom to top) consists of:

// * STMicroelectronics NUCLEO-F103RB development board
// * Mikroelektronika Arduino Uno click shield, P/N MIKROE-1581
// * Mikroelektronika Thermo 3 click, P/N MIKROE-1885, in slot 1
// * Mikroelektronika 7seg click, P/N MIKROE-1201, in slot 2

// Copyright (C)2016, Philip Munts, President, Munts AM Corp.
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

#include "mbed.h"

// TMP102 temperature sensor constants

#define TMP102_ADDR         0x48 << 1
#define TMP102_REG_TEMP     0
#define TMP102_REG_CONFIG   1
#define TMP102_REG_TLOW     2
#define TMP102_REG_THIGH    3
#define TMP102_SCALE_FACTOR 0.00390625

// TMP102 temperature sensor class

class TMP102
{
    I2C *i2c;
    uint8_t address;

public:

    // TMP102 object constructor

    TMP102(I2C *i2c, uint8_t address)
    {
        uint8_t buf[3];

        this->i2c = i2c;
        this->address = address;

        buf[0] = TMP102_REG_CONFIG;
        buf[1] = 0x00;
        buf[2] = 0x40;

        if (this->i2c->write(this->address, (char *) buf, 3))
        {
            printf("ERROR: i2c.write() failed");
            exit(1);
        }
    }

    // Get current temperature

    double get(void)
    {
        uint8_t buf[2];

        buf[0] = TMP102_REG_TEMP;

        if (this->i2c->write(this->address, (char *) buf, 1))
        {
            printf("ERROR: i2c.write() failed");
            exit(1);
        }

        if (this->i2c->read(this->address, (char *) buf, 2))
        {
            printf("ERROR: i2c.read() failed");
            exit(1);
        }

        int16_t rawtemp = buf[0]*256 + buf[1];
        return rawtemp*TMP102_SCALE_FACTOR;
    }
};

// Mikroelektronika 7seg click constants

// The following table permutes the segments of a single digit
// from standard form (A is LSB, DP is MSB) to match the wiring
// of the 7seg ClickBoard

static const uint8_t PermuteSegments[256] =
{
  0x00,0x04,0x02,0x06,0x08,0x0C,0x0A,0x0E,
  0x10,0x14,0x12,0x16,0x18,0x1C,0x1A,0x1E,
  0x20,0x24,0x22,0x26,0x28,0x2C,0x2A,0x2E,
  0x30,0x34,0x32,0x36,0x38,0x3C,0x3A,0x3E,
  0x40,0x44,0x42,0x46,0x48,0x4C,0x4A,0x4E,
  0x50,0x54,0x52,0x56,0x58,0x5C,0x5A,0x5E,
  0x60,0x64,0x62,0x66,0x68,0x6C,0x6A,0x6E,
  0x70,0x74,0x72,0x76,0x78,0x7C,0x7A,0x7E,
  0x80,0x84,0x82,0x86,0x88,0x8C,0x8A,0x8E,
  0x90,0x94,0x92,0x96,0x98,0x9C,0x9A,0x9E,
  0xA0,0xA4,0xA2,0xA6,0xA8,0xAC,0xAA,0xAE,
  0xB0,0xB4,0xB2,0xB6,0xB8,0xBC,0xBA,0xBE,
  0xC0,0xC4,0xC2,0xC6,0xC8,0xCC,0xCA,0xCE,
  0xD0,0xD4,0xD2,0xD6,0xD8,0xDC,0xDA,0xDE,
  0xE0,0xE4,0xE2,0xE6,0xE8,0xEC,0xEA,0xEE,
  0xF0,0xF4,0xF2,0xF6,0xF8,0xFC,0xFA,0xFE,
  0x01,0x05,0x03,0x07,0x09,0x0D,0x0B,0x0F,
  0x11,0x15,0x13,0x17,0x19,0x1D,0x1B,0x1F,
  0x21,0x25,0x23,0x27,0x29,0x2D,0x2B,0x2F,
  0x31,0x35,0x33,0x37,0x39,0x3D,0x3B,0x3F,
  0x41,0x45,0x43,0x47,0x49,0x4D,0x4B,0x4F,
  0x51,0x55,0x53,0x57,0x59,0x5D,0x5B,0x5F,
  0x61,0x65,0x63,0x67,0x69,0x6D,0x6B,0x6F,
  0x71,0x75,0x73,0x77,0x79,0x7D,0x7B,0x7F,
  0x81,0x85,0x83,0x87,0x89,0x8D,0x8B,0x8F,
  0x91,0x95,0x93,0x97,0x99,0x9D,0x9B,0x9F,
  0xA1,0xA5,0xA3,0xA7,0xA9,0xAD,0xAB,0xAF,
  0xB1,0xB5,0xB3,0xB7,0xB9,0xBD,0xBB,0xBF,
  0xC1,0xC5,0xC3,0xC7,0xC9,0xCD,0xCB,0xCF,
  0xD1,0xD5,0xD3,0xD7,0xD9,0xDD,0xDB,0xDF,
  0xE1,0xE5,0xE3,0xE7,0xE9,0xED,0xEB,0xEF,
  0xF1,0xF5,0xF3,0xF7,0xF9,0xFD,0xFB,0xFF,
};

// The following values came from https://en.wikipedia.org/wiki/Seven-segment_display

static const uint8_t GlyphTable[16] =
{ 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71 };

// Mikroelektronika 7seg click class

class Display
{
    SPI *spi;
    DigitalOut *pwm;
    DigitalOut *reset;
    DigitalOut *latch;

public:

    Display(SPI *spi, DigitalOut *pwm, DigitalOut *reset, DigitalOut *latch)
    {
        this->spi = spi;
        this->pwm = pwm;
        this->reset = reset;
        this->latch = latch;

        this->pwm->write(1);
        this->reset->write(1);
        this->latch->write(1);

        this->spi->format(16, 0);
        this->spi->frequency(4000000);

        this->write_segments(0x0000);
    }

    void write_segments(uint16_t segments)
    {
        this->latch->write(0);
        this->spi->write(segments);
        this->latch->write(1);
    }

    void write(uint8_t n)
    {
        if (n > 99) n = 99;
        this->write_segments(PermuteSegments[GlyphTable[n % 10]]*256 + PermuteSegments[GlyphTable[n / 10]]);
    }

    void writehex(uint8_t n)
    {
        this->write_segments(PermuteSegments[GlyphTable[n % 16]]*256 + PermuteSegments[GlyphTable[n / 16]]);
    }
};

int main()
{
    // Configure console

    Serial console(USBTX, USBRX);
    console.baud(115200);

    // Configure serial port to ESP8266 (optional)

    Serial network(PC_10, PC_11);
    network.baud(115200);

    console.printf("\033[H\033[2JNUCLEO-F103RB Thermometer (compiled " __DATE__ " " __TIME__ ")\r\n\n");

    // Configure hardware subsystems

    DigitalOut pwm(PB_4);
    DigitalOut reset(PA_4);
    DigitalOut latch(PC_7);
    I2C i2c(PB_9, PB_8);
    SPI spi(PA_7, PA_6, PA_5);

    // Configure temperature sensor

    TMP102 sensor(&i2c, TMP102_ADDR);

    // Configure display

    Display display(&spi, &pwm, &reset, &latch);

    // Wait for temperature sensor to stabilize

    console.printf("Waiting for sensor to stabilize...");
    wait(5.0);

    // Main loop: Read temperature and display it

    for (;;)
    {
        double temp = sensor.get();

        // Print temperature to console
        console.printf("\rTemperature is %1.1f deg Celsius   ", temp);

        // Print temperature to ESP8266
        network.printf("Temperature is %1.1f\r\n", temp);

        // No sign indicator available, so only display positive values
        if (temp >= 0.0) display.write((int)(temp + 0.5));

        wait(1.0);
    }
}
