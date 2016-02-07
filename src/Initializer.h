#pragma once

#include <Arduino.h>

class Initializer
{
  enum State : uint8_t
  {
    Unstarted = 0,
    Initializing = 1,
    Initialized = 2,
    Error = 3
  };

  State state;
  const __FlashStringHelper* statusMessage;

public:
  bool init(const __FlashStringHelper* (*initFunc)(void));
  // FIX: figure out overloading better so that we can have a better name than 'init2'
  bool init2(const __FlashStringHelper* (*initFunc)(const __FlashStringHelper** subStatus));

  const __FlashStringHelper* getStatus();
  const __FlashStringHelper* getStatusMessage()
  { return statusMessage != NULL ? statusMessage : F(""); }
};
