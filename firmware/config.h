
#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG 0

#define ADVAN2
//#define ADVAN1

namespace cfg
{
  static char const* Manufacturer = "Kinesis";
  static char const* Name = "Advantage";

#ifdef ADVAN1
  static char const* Model = "One";
  static char const* ProdDesc = "KinAdvan1";
  static char const* ManufacturerDesc = "BLE1";
#endif

#ifdef ADVAN2
  static char const* Model = "Two";
  static char const* ProdDesc = "KinAdvan2";
  static char const* ManufacturerDesc = "BLE2";
#endif
}

#endif
