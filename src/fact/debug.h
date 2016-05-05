#pragma once

#ifdef DEBUG3
#define DEBUG2
#endif

#ifdef DEBUG2
#define DEBUG
#endif

#if !defined(DEBUG_STREAM) && defined(DEBUG)

#if defined(__AVR_ATmega32U4__)
#define DEBUG_STREAM Serial
#else
#if defined(SAML_SERIES)
#define DEBUG_STREAM SerialUSB
#endif
#endif

#endif
