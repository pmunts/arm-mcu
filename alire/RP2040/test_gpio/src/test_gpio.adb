WITH RP.Clock;
WITH RP.GPIO;
WITH Pico;

PROCEDURE test_gpio IS

BEGIN
  RP.Clock.Initialize(Pico.XOSC_Frequency);
  RP.GPIO.Enable;

  Pico.GP2.Configure(RP.GPIO.Output);

  LOOP
    Pico.GP2.Toggle;
  END LOOP;
END test_gpio;
