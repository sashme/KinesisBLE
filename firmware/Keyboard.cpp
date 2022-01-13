
#include "Keyboard.h"
#include "config.h"

Keyboard::Keyboard( void )
    : matrix()
    , keymap()
    , hid()
    , power()
    , led()
{
  idleTime = 0;
  int batteryLEDOnSeconds = 5;
  batteryLEDOnDuration = batteryLEDOnSeconds * 1000;
  batteryIndicationPause = batteryIndicationFrequencyHours * 3600 * 1000;
}

void Keyboard::begin( void )
{
  led.begin();
  hid.begin();
  matrix.begin();
  indicateBatteryLevel();
}

void Keyboard::update( void )
{
  auto update = matrix.scan();
  if( update )
  {
    idleTime = millis();
    keymap.update( &matrix );
    hid.sendKeys( &keymap );
  }

  led.process();
  sleepCheck();
}

void Keyboard::batteryIndicationCheck( void )
{
  auto now = millis();
  if( now - lastBatteryIndicationTime > batteryIndicationPause )
  {
    indicateBatteryLevel();
  }
}

void Keyboard::indicateBatteryLevel( void )
{

  uint8_t percentage = power.batteryRemainingPercentage();

  if( percentage > 75 )
  {
    led.numLEDsOnForDuration( 4, batteryLEDOnDuration );
  }
  else if( percentage > 50 )
  {
    led.numLEDsOnForDuration( 3, batteryLEDOnDuration );
  }
  else if( percentage > 25 )
  {
    led.numLEDsOnForDuration( 2, batteryLEDOnDuration );
  }
  else
  {
    led.numLEDsOnForDuration( 1, batteryLEDOnDuration );
  }

  lastBatteryIndicationTime = millis();
}

void Keyboard::sleepCheck( void )
{
  if( hid.isUSB() )
  {
    return;
  }

  if( ( millis() - idleTime ) > ( sleepMinutes * 60 * 1000 ) )
  {
    led.offAll();
    matrix.sleep();

    uint8_t sd_en;
    sd_softdevice_is_enabled( &sd_en );

    if( sd_en )
    {
      sd_power_system_off();
    }
    else
    {
      NRF_POWER->SYSTEMOFF = 1;
    }
  }
  else
  {
    batteryIndicationCheck();
  }
}
