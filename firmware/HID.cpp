
#include "HID.h"
#include "config.h"

#include "Adafruit_TinyUSB.h"
#include <Arduino.h>

// clang-format off
const uint8_t HID::scancodes[] =
{
#define _s(key) (int) Scancode::key
[_s(             A )] = 0x4,
[_s(             B )] = 0x5,
[_s(             C )] = 0x6,
[_s(             D )] = 0x7,
[_s(             E )] = 0x8,
[_s(             F )] = 0x9,
[_s(             G )] = 0xa,
[_s(             H )] = 0xb,
[_s(             I )] = 0xc,
[_s(             J )] = 0xd,
[_s(             K )] = 0xe,
[_s(             L )] = 0xf,
[_s(             M )] = 0x10,
[_s(             N )] = 0x11,
[_s(             O )] = 0x12,
[_s(             P )] = 0x13,
[_s(             Q )] = 0x14,
[_s(             R )] = 0x15,
[_s(             S )] = 0x16,
[_s(             T )] = 0x17,
[_s(             U )] = 0x18,
[_s(             V )] = 0x19,
[_s(             W )] = 0x1a,
[_s(             X )] = 0x1b,
[_s(             Y )] = 0x1c,
[_s(             Z )] = 0x1d,

[_s(          Num1 )] = 0x1e,
[_s(          Num2 )] = 0x1f,
[_s(          Num3 )] = 0x20,
[_s(          Num4 )] = 0x21,
[_s(          Num5 )] = 0x22,
[_s(          Num6 )] = 0x23,
[_s(          Num7 )] = 0x24,
[_s(          Num8 )] = 0x25,
[_s(          Num9 )] = 0x26,
[_s(          Num0 )] = 0x27,

[_s(         Enter )] = 0x28,
[_s(           Esc )] = 0x29,
[_s(        BSpace )] = 0x2a,
[_s(           Tab )] = 0x2b,
[_s(         Space )] = 0x2c,
[_s(         Minus )] = 0x2d,
[_s(         Equal )] = 0x2e,
[_s(        LBrace )] = 0x2f,
[_s(        RBrace )] = 0x30,
[_s(        BSlash )] = 0x31,
[_s(          Hash )] = 0x32,
[_s(     Semicolon )] = 0x33,
[_s(        SQuote )] = 0x34,
[_s(         Grave )] = 0x35,
[_s(         Comma )] = 0x36,
[_s(           Dot )] = 0x37,
[_s(         Slash )] = 0x38,

[_s(            F1 )] = 0x3a,
[_s(            F2 )] = 0x3b,
[_s(            F3 )] = 0x3c,
[_s(            F4 )] = 0x3d,
[_s(            F5 )] = 0x3e,
[_s(            F6 )] = 0x3f,
[_s(            F7 )] = 0x40,
[_s(            F8 )] = 0x41,
[_s(            F9 )] = 0x42,
[_s(           F10 )] = 0x43,
[_s(           F11 )] = 0x44,
[_s(           F12 )] = 0x45,
[_s(     PrintScrn )] = 0x46,
[_s(    ScrollLock )] = 0x47,
[_s(         Pause )] = 0x48,
[_s(        Insert )] = 0x49,
[_s(          Home )] = 0x4a,
[_s(          PgUp )] = 0x4b,
[_s(           Del )] = 0x4c,
[_s(           End )] = 0x4d,
[_s(          PgDn )] = 0x4e,
[_s(         Right )] = 0x4f,
[_s(          Left )] = 0x50,
[_s(          Down )] = 0x51,
[_s(            Up )] = 0x52,
[_s(          Caps )] = 0x39
//[(int)Scancode::Hyper] = 0x6D //this is f18.
#undef _s
};

#define _m(key) (int) Mod::key
const uint8_t HID::modifers[] =
{
[_m(   Ctrl )] = 1 << 0,
[_m(  Shift )] = 1 << 1,
[_m(    Alt )] = 1 << 2,
[_m(  LCtrl )] = 1 << 0,
[_m( LShift )] = 1 << 1,
[_m(   LAlt )] = 1 << 2,
[_m(   LCmd )] = 1 << 3,
[_m(  RCtrl )] = 1 << 4,
[_m( RShift )] = 1 << 5,
[_m(   RAlt )] = 1 << 6,
[_m(   RCmd )] = 1 << 7
};
#undef _m

#define _k(key) (int) Keymap::Key::key
#define _s(code) .scancode = Scancode::code
#define _______ .shift = false
#define _SHIFT_ .shift = true
const HID::KeyInfo HID::scancodeMap[] =
{
[_k(          A )] = { _______, _s( A           )},
[_k(          B )] = { _______, _s( B           )},
[_k(          C )] = { _______, _s( C           )},
[_k(          D )] = { _______, _s( D           )},
[_k(          E )] = { _______, _s( E           )},
[_k(          F )] = { _______, _s( F           )},
[_k(          G )] = { _______, _s( G           )},
[_k(          H )] = { _______, _s( H           )},
[_k(          I )] = { _______, _s( I           )},
[_k(          J )] = { _______, _s( J           )},
[_k(          K )] = { _______, _s( K           )},
[_k(          L )] = { _______, _s( L           )},
[_k(          M )] = { _______, _s( M           )},
[_k(          N )] = { _______, _s( N           )},
[_k(          O )] = { _______, _s( O           )},
[_k(          P )] = { _______, _s( P           )},
[_k(          Q )] = { _______, _s( Q           )},
[_k(          R )] = { _______, _s( R           )},
[_k(          S )] = { _______, _s( S           )},
[_k(          T )] = { _______, _s( T           )},
[_k(          U )] = { _______, _s( U           )},
[_k(          V )] = { _______, _s( V           )},
[_k(          W )] = { _______, _s( W           )},
[_k(          X )] = { _______, _s( X           )},
[_k(          Y )] = { _______, _s( Y           )},
[_k(          Z )] = { _______, _s( Z           )},

[_k(        Nm1 )] = { _______, _s( Num1        )},
[_k(        Nm2 )] = { _______, _s( Num2        )},
[_k(        Nm3 )] = { _______, _s( Num3        )},
[_k(        Nm4 )] = { _______, _s( Num4        )},
[_k(        Nm5 )] = { _______, _s( Num5        )},
[_k(        Nm6 )] = { _______, _s( Num6        )},
[_k(        Nm7 )] = { _______, _s( Num7        )},
[_k(        Nm8 )] = { _______, _s( Num8        )},
[_k(        Nm9 )] = { _______, _s( Num9        )},
[_k(        Nm0 )] = { _______, _s( Num0        )},

[_k(      Enter )] = { _______, _s( Enter       )},
[_k(        Esc )] = { _______, _s( Esc         )},
[_k(     BSpace )] = { _______, _s( BSpace      )},
[_k(        Tab )] = { _______, _s( Tab         )},
[_k(      Space )] = { _______, _s( Space       )},
[_k(      Minus )] = { _______, _s( Minus       )},
[_k(         Eq )] = { _______, _s( Equal       )},
[_k(       LBrc )] = { _______, _s( LBrace      )},
[_k(       RBrc )] = { _______, _s( RBrace      )},
[_k(     SmColn )] = { _______, _s( Semicolon   )},
[_k(     SQuote )] = { _______, _s( SQuote      )},
[_k(      Comma )] = { _______, _s( Comma       )},
[_k(        Dot )] = { _______, _s( Dot         )},
[_k(      Slash )] = { _______, _s( Slash       )},
[_k(      Grave )] = { _______, _s( Grave       )},
[_k(     BSlash )] = { _______, _s( BSlash      )},
[_k(        Ins )] = { _______, _s( Insert      )},

//[_k(      Tilde )] = { _SHIFT_, _s( Hash        )},
[_k(         At )] = { _SHIFT_, _s( SQuote      )},
[_k(     LBrckt )] = { _SHIFT_, _s( LBrace      )},
[_k(     RBrckt )] = { _SHIFT_, _s( RBrace      )},
[_k(     RParen )] = { _SHIFT_, _s( Num0        )},
[_k(       Bang )] = { _SHIFT_, _s( Num1        )},
[_k(     DQuote )] = { _SHIFT_, _s( Num2        )},
//[_k(       Hash )] = { _SHIFT_, _s( Hash        )},
[_k(     Dollar )] = { _SHIFT_, _s( Num4        )},
[_k(       Perc )] = { _SHIFT_, _s( Num5        )},
[_k(      Caret )] = { _SHIFT_, _s( Num6        )},
[_k(        Amp )] = { _SHIFT_, _s( Num7        )},
[_k(       Star )] = { _SHIFT_, _s( Num8        )},
[_k(     LParen )] = { _SHIFT_, _s( Num9        )},
[_k(       Plus )] = { _SHIFT_, _s( Equal       )},
[_k(      Under )] = { _SHIFT_, _s( Minus       )},
[_k(       Pipe )] = { _SHIFT_, _s( BSlash      )},
[_k(     Questn )] = { _SHIFT_, _s( Slash       )},

[_k(         F1 )] = { _______, _s( F1          )},
[_k(         F2 )] = { _______, _s( F2          )},
[_k(         F3 )] = { _______, _s( F3          )},
[_k(         F4 )] = { _______, _s( F4          )},
[_k(         F5 )] = { _______, _s( F5          )},
[_k(         F6 )] = { _______, _s( F6          )},
[_k(         F7 )] = { _______, _s( F7          )},
[_k(         F8 )] = { _______, _s( F8          )},
[_k(         F9 )] = { _______, _s( F9          )},
[_k(        F10 )] = { _______, _s( F10         )},
[_k(        F11 )] = { _______, _s( F11         )},
[_k(        F12 )] = { _______, _s( F12         )},

[_k(      PrtSc )] = { _______, _s( PrintScrn   )},
[_k(     ScrlLk )] = { _______, _s( ScrollLock  )},
[_k(      Pause )] = { _______, _s( Pause       )},
[_k(       Home )] = { _______, _s( Home        )},
[_k(       PgUp )] = { _______, _s( PgUp        )},
[_k(        Del )] = { _______, _s( Del         )},
[_k(        End )] = { _______, _s( End         )},
[_k(       PgDn )] = { _______, _s( PgDn        )},
[_k(      Right )] = { _______, _s( Right       )},
[_k(       Left )] = { _______, _s( Left        )},
[_k(       Down )] = { _______, _s( Down        )},
[_k(         Up )] = { _______, _s( Up          )},

[_k(       Caps )] = { _______, _s( Caps        )},
[_k(        SL1 )] = { _______, _s( End         )},
[_k(        SL2 )] = { _______, _s( Home        )},
[_k(        SL3 )] = { _______, _s( Del         )},
[_k(        SL4 )] = { _______, _s( BSpace      )},
[_k(        SR1 )] = { _______, _s( PgDn        )},
[_k(        SR2 )] = { _______, _s( PgUp        )},
[_k(        SR3 )] = { _______, _s( Enter       )},
[_k(        SR4 )] = { _______, _s( Space       )},

[_k(         KY )] = { _______, _s( None        )},
[_k(         PG )] = { _______, _s( None        )}
};
#undef _k
#undef _s
#undef _SHIFT_
#undef _______
// clang-format on

uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD(),
};

Adafruit_USBD_HID usb_hid;

HID::HID( void )
    : bleDIS()
    , bleHID()
{
  memset( &report, 0, sizeof( report ) );
}

void HID::begin( void )
{
  Bluefruit.begin();
  Bluefruit.setName( cfg::Name );
  Bluefruit.setTxPower( 0 );
  Bluefruit.autoConnLed( false );

  bleDIS.setManufacturer( cfg::Manufacturer );
  bleDIS.setModel( cfg::Model );

  bleDIS.begin();
  bleHID.begin();

  Bluefruit.Advertising.addFlags( BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE );
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance( BLE_APPEARANCE_HID_KEYBOARD );

  Bluefruit.Advertising.addService( bleHID );

  Bluefruit.Advertising.addName();

  Bluefruit.Advertising.restartOnDisconnect( true );
  Bluefruit.Advertising.setInterval( 32, 244 );
  Bluefruit.Advertising.setFastTimeout( 30 );
  Bluefruit.Advertising.start( 0 );

  usb_hid.setPollInterval( 2 );
  usb_hid.setReportDescriptor( desc_hid_report, sizeof( desc_hid_report ) );
  usb_hid.begin();
  USBDevice.setProductDescriptor( cfg::ProdDesc );
  USBDevice.setManufacturerDescriptor( cfg::ManufacturerDesc );
}

void HID::sendKeys( const Keymap* km )
{
  auto oldReport = report;
  memset( &report, 0, sizeof( report ) );

  for( int k = 0, i = 0; k < ( int ) Keymap::Key::Count && i < 6; k++ )
  {
    auto key = ( Keymap::Key ) k;

    auto pressed = km->pressed( key );
    if( ! pressed )
    {
      continue;
    }

    switch( key )
    {
      case Keymap::Key::Ctrl:
        report.modifier |= modifers[ ( int ) HID::Mod::Ctrl ];
        break;
      case Keymap::Key::Alt:
        report.modifier |= modifers[ ( int ) HID::Mod::Alt ];
        break;
      case Keymap::Key::Shift:
        report.modifier |= modifers[ ( int ) HID::Mod::Shift ];
        break;
      case Keymap::Key::Sym:
        break;

      case Keymap::Key::SL5:
        report.modifier |= modifers[ ( int ) HID::Mod::LAlt ];
        break;
      case Keymap::Key::LSh:
        report.modifier |= modifers[ ( int ) HID::Mod::LShift ];
        break;
      case Keymap::Key::SL6:
        report.modifier |= modifers[ ( int ) HID::Mod::LCmd ];
        break;
      case Keymap::Key::RSh:
        report.modifier |= modifers[ ( int ) HID::Mod::RShift ];
        break;
      case Keymap::Key::SR5:
        report.modifier |= modifers[ ( int ) HID::Mod::RCtrl ];
        break;
      case Keymap::Key::SR6:
        report.modifier |= modifers[ ( int ) HID::Mod::RCmd ];
        break;
        /*
      case Keymap::Key::KY: //Make KY disconnect bluetooth.
#ifdef DEBUG
        Serial.begin( 115200 );
        while( ! Serial )
          delay( 10 ); // for nrf52840 with native USB

        Serial.println( "----- Before -----\n" );
        bond_print_list( BLE_GAP_ROLE_PERIPH );
        bond_print_list( BLE_GAP_ROLE_CENTRAL );
#endif

        Bluefruit.disconnect();

#ifdef DEBUG
        Serial.println();
        Serial.println( "----- After  -----\n" );

        bond_print_list( BLE_GAP_ROLE_PERIPH );
        bond_print_list( BLE_GAP_ROLE_CENTRAL );
#endif
        break;
        */

      default:
      {
        auto info = scancodeMap[ ( int ) key ];

        report.keycode[ i++ ] = scancodes[ ( int ) info.scancode ];
        if( info.shift )
        {
          report.modifier |= 1 << 1;
        }
      }
    }
  }

  bool setReport = memcmp( &report, &oldReport, sizeof( report ) );
  if( not setReport )
  {
    return;
  }

  if( usb_hid.ready() )
  {
    usb_hid.sendReport( 0, &report, sizeof( report ) );
    return;
  }

  bleHID.keyboardReport( &report );
}

bool HID::isUSB( void ) const
{
  return usb_hid.ready();
}
