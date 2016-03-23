#include "Console.h"

/*
#ifdef __AVR__
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif
*/

using namespace FactUtilEmbedded;



void ConsoleMenu::handleCommand(Parameters p)
{
#ifdef DEBUG2
  cout << F("ConsoleMenu::handleCommand: ") << breadCrumbPos;
  cout.println();
  cout << F("  menu ptr = ") << (uint32_t)getActiveMenu();
  cout.println();
#endif

  getActiveMenu()->handleCommand(p);
}



void ConsoleMenu::showPrompt()
{
  for(int i = 0; i < breadCrumbPos; i++)
  {
#ifdef DEBUG2
    cout << F("ConsoleMenu::showPrompt: ") << i;
    cout.println();
#endif
    breadCrumb[i]->showPrompt();
    if(i != (breadCrumbPos - 1)) cout << ' ';
  }

  cout << F("> ");
}

#if defined(CONSOLE_FEATURE_ENHANCED_CHARPROCESSOR)
bool ConsoleMenu::processInput(Console* console, char received)
{
  return getActiveMenu()->processInput(console, received);
}
#endif