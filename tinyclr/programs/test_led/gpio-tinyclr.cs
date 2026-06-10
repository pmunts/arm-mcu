// GPIO pin services using IO.Objects.SimpleIO

// Copyright (C)2017-2023, Philip Munts dba Munts Technologies.
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

using GHIElectronics.TinyCLR.Devices.Gpio;
using GHIElectronics.TinyCLR.Pins;
using System;

namespace IO.Objects.TinyCLR.GPIO
{
  /// <summary>
  /// Encapsulates Linux GPIO pins using <c>TinyCLR</c> libraries.
  /// </summary>
  public class Pin : IO.Interfaces.GPIO.Pin
  {
    private readonly GpioPinDriveMode mymode;
    private readonly GpioPin mypin;
    private bool mypolarity;

    /// <summary>
    /// Constructor for a single GPIO pin.
    /// </summary>
    /// <param name="desg">GPIO pin designator.</param>
    /// <param name="mode">GPIO pin mode.</param>
    /// <param name="state">Initial GPIO output state.</param>
    /// <param name="activelow">Polarity setting.</param>
    public Pin(uint desg, GpioPinDriveMode mode, bool state = false, bool activelow = false)
    {
      this.mymode = mode;
      this.mypin = GpioController.GetDefault().OpenPin((int)desg);
      this.mypin.SetDriveMode(mode);
      this.mypolarity = activelow;
      this.state = state;
    }

    /// <summary>
    /// Read/Write GPIO state property.
    /// </summary>
    public bool state
    {
      get
      {
        return (this.mypin.Read() == GpioPinValue.High) ^ this.mypolarity;
      }

      set
      {
        if ((this.mymode == GpioPinDriveMode.Output) ||
            (this.mymode == GpioPinDriveMode.OutputOpenDrain))
          if (value ^ this.mypolarity)
            this.mypin.Write(GpioPinValue.High);
          else
            this.mypin.Write(GpioPinValue.Low);
      }
    }
  }
}
