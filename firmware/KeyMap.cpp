#include "KeyMap.h"

#include <Arduino.h>

// clang-format off
// alternations:
// Key::Up <> Key::Down
const Keymap::Key Keymap::layout[][(int)Matrix::Dim::Row][(int)Matrix::Dim::Col] = {

#define k(key) Key::key
[(int)Layer::Base] = {
{k(    Eq ),k(   Nm1 ),k(   Nm2 ),k(   Nm3 ),k(   Nm4 ),k(   Nm5 ),k(   Nm6 ),k(   Nm7 ),k(   Nm8 ),k(   Nm9 ),k(   Nm0 ),k( Minus ),k(   Esc ),k(    F1 ),k(    F2 )},
{k(   Tab ),k(     Q ),k(     W ),k(     E ),k(     R ),k(     T ),k(     Y ),k(     U ),k(     I ),k(     O ),k(     P ),k(BSlash ),k(    F3 ),k(    F4 ),k(    F5 )},
{k(  Caps ),k(     A ),k(     S ),k(     D ),k(     F ),k(     G ),k(     H ),k(     J ),k(     K ),k(     L ),k(SmColn ),k(SQuote ),k(    F6 ),k(    F7 ),k(    F8 )},
{k(   LSh ),k(     Z ),k(     X ),k(     C ),k(     V ),k(     B ),k(     N ),k(     M ),k( Comma ),k(   Dot ),k( Slash ),k(   RSh ),k(    F9 ),k(   F10 ),k(   F11 )},
{k(  ____ ),k( Grave ),k(   Ins ),k(  Left ),k(  ____ ),k( Right ),k(  Down ),k(  ____ ),k(    Up ),k(  LBrc ),k(  RBrc ),k(  ____ ),k(   F12 ),k( PrtSc ),k(ScrlLk )},
{k(  ____ ),k(  ____ ),k(   SL1 ),k(   SL2 ),k(  ____ ),k(   SL5 ),k(   SR4 ),k(   SR3 ),k(   SR6 ),k(  ____ ),k(  ____ ),k(  ____ ),k( Pause ),k(    KY ),k(    PG )},
{k(  ____ ),k(  ____ ),k(  ____ ),k(   SL4 ),k(   SL3 ),k(   SL6 ),k(   SR1 ),k(  ____ ),k(   SR2 ),k(   SR5 ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )}
},

/*
[(int)Layer::Sym] = {
{k(  ____ ),k(    F9 ),k(    F7 ),k(    F5 ),k(    F3 ),k(    F1 ),k(   F10 ),k(    F2 ),k(    F4 ),k(    F6 ),k(    F8 ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )},
{k(  ____ ),k(  Perc ),k(    At ),k(BSlash ),k(  LBrc ),k(LBrckt ),k(RBrckt ),k(  RBrc ),k(  ____ ),k( Caret ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )},
{k(  ____ ),k(  Hash ),k(Dollar ),k(LParen ),k(  Star ),k(  Bang ),k( Slash ),k( Under ),k(RParen ),k(    Eq ),k(  Plus ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )},
{k(  ____ ),k(  ____ ),k(  ____ ),k(   Amp ),k(  Pipe ),k(  ____ ),k(  ____ ),k(  ____ ),k(Questn ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )},
{k(  ____ ),k(  Pipe ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )},
{k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )},
{k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )}
}
*/
[(int)Layer::Sym] = {
{k(  ____ ),k(    F9 ),k(    F7 ),k(    F5 ),k(    F3 ),k(    F1 ),k(   F10 ),k(    F2 ),k(    F4 ),k(    F6 ),k(    F8 ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )},
{k(  ____ ),k(  Perc ),k(    At ),k(BSlash ),k(  LBrc ),k(LBrckt ),k(RBrckt ),k(  RBrc ),k(  ____ ),k( Caret ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )},
{k(  ____ ),k(  ____ ),k(Dollar ),k(LParen ),k(  Star ),k(  Bang ),k( Slash ),k( Under ),k(RParen ),k(    Eq ),k(  Plus ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )},
{k(  ____ ),k(  ____ ),k(  ____ ),k(   Amp ),k(  Pipe ),k(  ____ ),k(  ____ ),k(  ____ ),k(Questn ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )},
{k(  ____ ),k(  Pipe ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )},
{k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )},
{k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ ),k(  ____ )}
}

#undef k
};
// clang-format on

Keymap::Keymap( void )
{
  memset( &keysPressed, 0, sizeof( keysPressed ) );
  memset( &matrixPressed, 0, sizeof( matrixPressed ) );

  for( int m = 0; m < ( int ) Mod::Count; m++ )
  {
    modStates[ m ] = ModState::Off;
  }
}

Keymap::Key Keymap::resolveKey( const Matrix::Key k ) const
{
  switch( modStates[ ( int ) Mod::Sym ] )
  {
    case ModState::Off:
      return layout[ ( int ) Layer::Base ][ k.r ][ k.c ];
    case ModState::StickLight:
    case ModState::StickHeavy:
      auto key = layout[ ( int ) Layer::Sym ][ k.r ][ k.c ];
      return key == Key::____ ? layout[ ( int ) Layer::Base ][ k.r ][ k.c ] : key;
  }
}

Keymap::ModState Keymap::nextModState( Keymap::ModState modState ) const
{
  switch( modState )
  {
    case ModState::Off:
      return ModState::StickLight;
    case ModState::StickLight:
      return ModState::StickHeavy;
    case ModState::StickHeavy:
      return ModState::Off;
  }
}

bool Keymap::modActive( Keymap::Mod m ) const
{
  switch( modStates[ ( int ) m ] )
  {
    case ModState::Off:
      return false;
    case ModState::StickLight:
      return true;
    case ModState::StickHeavy:
      return true;
  }
}

Keymap::Mod Keymap::keyToMod( Keymap::Key k ) const
{
  switch( k )
  {
    case Key::Ctrl:
      return Mod::Ctrl;
    case Key::Alt:
      return Mod::Alt;
    case Key::Shift:
      return Mod::Shift;
    case Key::Sym:
      return Mod::Sym;
  }
}

void Keymap::update( const Matrix* matrix )
{
  auto oldKeysPressed = keysPressed;
  auto oldMatrixPressed = matrixPressed;

  bool nonModifierPressed = false;
  for( auto r = 0; r < ( int ) Matrix::Dim::Row; r++ )
  {
    for( auto c = 0; c < ( int ) Matrix::Dim::Col; c++ )
    {
      Matrix::Key matrixKey = { .r = r, .c = c };
      auto key = resolveKey( matrixKey );
      auto wasPressed = oldMatrixPressed[ r ][ c ];
      bool isPressed = matrix->pressed( matrixKey );
      matrixPressed[ r ][ c ] = isPressed;

      switch( key )
      {
        case Key::____:
          break;
        case Key::Ctrl:
        case Key::Alt:
        case Key::Shift:
        case Key::Sym:
        {
          auto m = keyToMod( key );
          if( isPressed && ! wasPressed )
          {
            modStates[ ( int ) m ] = nextModState( modStates[ ( int ) m ] );
          }
          keysPressed[ ( int ) key ] = modActive( m );
          break;
        }
        default:
          nonModifierPressed = nonModifierPressed || isPressed;
          keysPressed[ ( int ) key ] = isPressed;
          break;
      }
    }
  }

  if( nonModifierPressed )
  {
    for( int m = 0; m < ( int ) Mod::Count; m++ )
    {
      if( modStates[ m ] == ModState::StickLight )
      {
        modStates[ m ] = ModState::Off;
      }
    }
  }
}

bool Keymap::pressed( const Keymap::Key k ) const
{
  return keysPressed[ ( int ) k ];
}
