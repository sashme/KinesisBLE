
#ifndef KEYMAP_H
#define KEYMAP_H

#include <stdint.h>

#include "Matrix.h"

class Keymap
{
public:
  // clang-format off
  enum class Key
  {
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

    Nm1, Nm2, Nm3, Nm4, Nm5, Nm6, Nm7, Nm8, Nm9, Nm0,

    Enter, Esc, BSpace, Tab, Space,
    Minus, Eq, LBrc, RBrc, SmColn,
    SQuote, Comma, Dot, Slash, Grave, BSlash, Ins,
    
    /*Tilde,*/ At, LBrckt, RBrckt, RParen, Bang, 
    DQuote, /*Hash,*/ Dollar, Perc, Caret, Amp,
    Star, LParen, Plus, Under, Pipe, Questn,

    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

    PrtSc, ScrlLk, Pause, Home, PgUp, Del, End, PgDn, Right, Left, Down, Up,

    Caps, SL1, SL2, SL3, SL4, SR1, SR2, SR3, SR4, KY, PG,

    LSh, RSh, SL5, SL6, SR5, SR6,

    Ctrl, Shift, Alt,

    Sym,
    Count,
    ____
  };
  // clang-format on

  Keymap( void );
  void update( const Matrix* matrix );
  bool pressed( const Key k ) const;

private:
  enum class Layer
  {
    Base,
    Sym,
    Count
  };

  enum class ModState
  {
    Off,
    StickLight,
    StickHeavy
  };

  enum class Mod
  {
    Ctrl,
    Shift,
    Alt,
    Sym,
    Count
  };

  Key resolveKey( const Matrix::Key k ) const;
  bool modActive( Mod m ) const;
  Mod keyToMod( Key k ) const;
  ModState nextModState( ModState modState ) const;

  bool keysPressed[ ( int ) Key::Count ];
  bool matrixPressed[ ( int ) Matrix::Dim::Row ][ ( int ) Matrix::Dim::Col ];
  ModState modStates[ ( int ) Mod::Count ];

  static const Key layout[][ ( int ) Matrix::Dim::Row ][ ( int ) Matrix::Dim::Col ];
};

#endif
