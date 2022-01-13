
#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG 0

//#define ADVAN2
#define ADVAN1

namespace cfg
{
  static char const* Manufacturer = "Kinesis";

#ifdef ADVAN1
  static char const* Name = "Advantage1";
  static char const* Model = "One";
  static char const* ProdDesc = "Kinesis Advantage";
  static char const* ManufacturerDesc = "BLE1";
#endif

#ifdef ADVAN2
  static char const* Name = "Advantage2";
  static char const* Model = "Two";
  static char const* ProdDesc = "Kindesis Advantage 2";
  static char const* ManufacturerDesc = "BLE2";
#endif
}

#endif
