
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "HID.h"
#include "KeyMap.h"
#include "LED.h"
#include "Matrix.h"
#include "Power.h"

class Keyboard
{
public:
  Keyboard( void );
  void begin( void );
  void update( void );
  void sleepCheck( void );

private:
  Matrix matrix;
  Keymap keymap;
  HID hid;
  LED led;
  Power power;
  unsigned long idleTime;
  void indicateBatteryLevel( void );
  unsigned long batteryLEDOnDuration;

  static const uint8_t sleepMinutes = 10;
};

#endif

