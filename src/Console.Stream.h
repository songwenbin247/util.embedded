#pragma once

#include "fact/c_types.h"
#include "fact/iostream_arduino.h"

#if defined(ARDUINO) && defined(__UNUSED)
inline Print& operator<<(Print& out, Print& (*__pf)(Print&))
{
    return __pf(out);
}

inline Print& endl(Print& out)
{
    out.println();
    return out;
}


// using Arduino-style streams

typedef Print fact_ostream;
typedef Stream fact_istream;

#ifdef CONSOLE_STREAM
#define clog CONSOLE_STREAM
#define cout CONSOLE_STREAM
#define cin CONSOLE_STREAM
#else
// temporary until we fully enable this inside Console class itself
#ifdef SAML_SERIES
#define clog SerialUSB
#define cout SerialUSB
#define cin SerialUSB
#elif not defined(__AVR_ATtiny85__)
#define clog Serial
#define cout Serial
#define cin Serial
#endif
#endif

#ifdef CONSOLE_STREAM_EXTERN
// FIX: pretty kludgey
#if CONSOLE_STREAM_EXTERN == SoftwareSerial
#include <SoftwareSerial.h>
#endif
extern CONSOLE_STREAM_EXTERN cout;
#endif

// NOTE: kinda kludgey, this discovers if no cout exists
// and if so makes a dummy one so that at least the menu
// stuff will compile (and be optimized out)
// Beware not to actually use Console/Menu stuff with this DummyStream
#if !defined(cout) and !defined(CONSOLE_STREAM_EXTERN)
#define USE_DUMMY_STREAM
class DummyStream : public Stream
{
public:
  virtual size_t write(uint8_t) override { return 1; }
  virtual int available() override { return 0; }
  virtual int read() override { return ' '; }
  virtual int peek() override { return -1; }
  virtual void flush() override {}

  void begin(uint32_t bps) {}
};

extern DummyStream _dummyStream;

#define cin _dummyStream
#define cout _dummyStream
#endif

#endif // FEATURE_IOSTREAM_SHIM


#ifdef CONSOLE_FEATURE_COUT
#define MENU_DECLARE_COUT fact_ostream& out = p.console->getOut();
#else
#if defined(FEATURE_IOSTREAM_SHIM)
#define MENU_DECLARE_COUT fact_ostream& out = FactUtilEmbedded::std::cout;
#elif defined(FEATURE_IOSTREAM)
#define MENU_DECLARE_COUT fact_ostream& out = std::cout;
#else
#define MENU_DECLARE_COUT fact_ostream& out = cout;
#endif
#endif
