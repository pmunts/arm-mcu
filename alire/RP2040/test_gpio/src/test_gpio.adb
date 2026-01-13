WITH Ada.Text_IO; USE Ada.Text_IO;

WITH RP.Clock;
WITH RP.Device;
WITH RP.GPIO;
WITH SparkFun_Pro_Micro_RP2040;

PROCEDURE test_gpio IS

  LED RENAMES SparkFun_Pro_Micro_RP2040.GP2;

BEGIN
  RP.Clock.Initialize(SparkFun_Pro_Micro_RP2040.Crystal);
  RP.Device.Timer.Enable;

  LED.Configure(RP.GPIO.Output);

  LOOP
    LED.Toggle;
    RP.Device.Timer.Delay_Milliseconds(500); 
  END LOOP;
END test_gpio;
